#include "uart.hpp"
#include "clock.hpp"
#include "uartConsole.hpp"

namespace peripherals
{

    static uint8_t rxBuffer[256];
    static uint8_t rxHead = 0;
    static uint8_t rxTail = 0;
    static uint8_t txBuffer[256];
    static uint8_t txHead = 0;
    static uint8_t txTail = 0;

    Uart::Uart(uint32_t baudrate,
               uint8_t pinTx,
               uint8_t pinRx) : _baudrate(baudrate),
                                _pinTx(pinTx),
                                _pinRx(pinRx)
    {
        // Enable clocks - already in clock init
        // Enable usart on gpio a
        GPIOA_CRL &= ~GPIO_CRL_MODE_MSK(pinTx);
        GPIOA_CRL &= ~GPIO_CRL_MODE_MSK(pinRx);
        GPIOA_CRL |= GPIO_CRL_MODE_OUTPUT(pinTx);
        GPIOA_CRL |= GPIO_CRL_MODE_INPUT(pinRx);

        GPIOA_CRL &= ~GPIO_CRL_CNF_MSK(pinTx);
        GPIOA_CRL &= ~GPIO_CRL_CNF_MSK(pinRx);
        GPIOA_CRL |= GPIO_CRL_CNF_ALT_PUSH_PULL(pinTx);
        GPIOA_CRL |= GPIO_CRL_CNF_FLOAT_INPUT(pinRx);

        // Select baudrate
        uint16_t uartdiv = PCLK1 / _baudrate;

        USART2_BRR = (((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
                      ((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos));

        // Enable USART
        USART2_CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE);
    }

    Uart::~Uart()
    {
    }

    // put single char into ringbuffer
    void Uart::_putC(char c)
    {
        uint8_t nxt = (txHead + 1) % 256;
        if (nxt == txTail)
        {
            services::logger.send("uart.cpp: txBuffer full");
        }
        else
        {
            txBuffer[txHead] = (uint8_t)c;
            txHead = nxt;
            // Enable TXE interrupt
            USART2_CR1 |= USART_CR1_TXEIE;
        }
    }

    // receive single char from ringbuffer
    uint8_t Uart::_getC()
    {
        uint8_t c = 255; // Buffer empty state 255
        if (rxHead != rxTail)
        {
            c = rxBuffer[rxTail];
            rxTail = (rxTail + 1) % 256;
        }
        return c;
    }

    // write into ringbuffer
    void Uart::write(const char *s)
    {
        while (*s)
        {
            if (*s == '\n')
                _putC('\r');
            _putC(*s++);
        }
    }

    // read from ringbuffer (pop)
    bool Uart::read(char& c)
    {
        return ((c = _getC()) != 255);
    }

    void Uart::sendByte(char b)
    {
        // wait until register is empty
        while (!(USART2_SR & USART_SR_TXE))
        {
        };
        USART2_DR = b;
    }

    Uart::Status Uart::receiveByte(char &b)
    {
        // wait until register is filled
        if (!(USART2_SR & USART_SR_RXNE))
        {
            return Uart::Status::rx_empty;
        }
        else
        {
            b = USART2_DR;
            return Uart::Status::rx_available;
        }
    }

    void Usart1Handler(void)
    {
        if (USART2_SR & USART_SR_RXNE)
        {
            uint8_t b = (uint8_t)USART2_DR;
            uint8_t nxt = (rxHead + 1) % 256;
            if (nxt != rxTail)
            {
                rxBuffer[rxHead] = b;
                rxHead = nxt;
            }
            else
            {
                services::logger.send("uart.cpp: buffer overflow in uart rx ringbuffer");
            }
        }

        if (USART2_SR & USART_SR_TXE)
        {
            if (txTail == txHead)
            {
                // everything is send, buf empty, disable irq
                USART2_CR1 &= ~USART_CR1_TXEIE; // Disable TXE interrupt
            }
            else
            {
                uint8_t b = txBuffer[txTail];
                txTail = (txTail + 1) % 256;
                USART2_DR = b;
            }
        }
    }

}