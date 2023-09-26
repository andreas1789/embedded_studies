#include "uart.hpp"

namespace peripherals
{

    Uart::Uart(uint16_t baudrate,
               uint8_t pinTx,
               uint8_t pinRx) : _baudrate(baudrate),
                                _pinTx(pinTx),
                                _pinRx(pinRx)
    {
        // Enable clocks - already in clock init
        // Enable usart on gpio a
        GPIOA_CRL &= ~GPIO_CRL_MODE_MSK(2);
        GPIOA_CRL &= ~GPIO_CRL_MODE_MSK(3);
        GPIOA_CRL |= GPIO_CRL_MODE_OUTPUT(2);
        GPIOA_CRL |= GPIO_CRL_MODE_INPUT(3);

        GPIOA_CRL &= ~GPIO_CRL_CNF_MSK(2);
        GPIOA_CRL &= ~GPIO_CRL_CNF_MSK(3);
        GPIOA_CRL |= GPIO_CRL_CNF_ALT_PUSH_PULL(2);
        GPIOA_CRL |= GPIO_CRL_CNF_FLOAT_INPUT(3);

        // Select baudrate
        uint32_t SystemCoreClock = 72000000U;
        uint16_t uartdiv = SystemCoreClock / _baudrate;

        USART2_BRR = (((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
                      ((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos));

        // Enable USART
        USART2_CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE);
    }

    Uart::~Uart()
    {
    }

    void Uart::send(char b)
    {
        // wait until register is empty
        while (!(USART2_SR & USART_SR_TXE))
        {
        };
        USART2_DR = b;
    }

    void Uart::receive(char &b)
    {
        // wait until register is filled
        while (!(USART2_SR & USART_SR_RXNE))
        {
        };
        b = USART2_DR;
    }

}