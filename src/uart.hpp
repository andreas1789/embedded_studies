#include "types.hpp"
#include "gpio.hpp"

using namespace types;

namespace peripherals
{

    #define USART2_BASE 0x40004400
    #define USART2_BRR (*(volatile uint32_t *)(USART2_BASE + 0x8))
    #define USART2_CR1 (*(volatile uint32_t *)(USART2_BASE + 0xC))
    #define USART2_SR (*(volatile uint32_t *)(USART2_BASE + 0x0))
    #define USART2_DR (*(volatile uint32_t *)(USART2_BASE + 0x4))

    #define USART_BRR_DIV_Mantissa_Pos 4
    #define USART_BRR_DIV_Fraction_Pos 0

    #define USART_CR1_RE (0x1 << 2)
    #define USART_CR1_TE (0x1 << 3)
    #define USART_CR1_UE (0x1 << 13)

    #define USART_SR_TXE (0x1 << 7)
    #define USART_SR_RXNE (0x1 << 5)


    class Uart
    {
    private:
        uint32_t _baudrate;
        uint8_t _pinTx;
        uint8_t _pinRx;
        char rxb = '\0';
    public:
        Uart(uint32_t baudrate, uint8_t pinTx, uint8_t pinRx);
        ~Uart();
        void send(char b);
        void receive(char& b);
    };

}