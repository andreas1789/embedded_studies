#include "clock.h"

void SystemInit()
{
    // Enable clock on gpio ports
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    // configure gpio port c as output
    GPIOC_CRH &= ~GPIOC_CRH_MODE_MSK(13);
    GPIOC_CRH |= GPIOC_CRH_MODE_OUTPUT(13);
}

int main()
{
    while(1)
    {
        // switch on led
        GPIOC_ODR |= GPIOC_ODR_PIN(13);

        for (uint32_t i = 0; i < 400000; ++i) 
        {
            __asm__ volatile("nop");
        }

        // switch off led
        GPIOC_ODR &= ~GPIOC_ODR_PIN(13);

        for (uint32_t i = 0; i < 100000; ++i) 
        {
            __asm__ volatile("nop");
        }
    }
    return 0;
}