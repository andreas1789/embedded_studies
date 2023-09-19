#include "clock.h"

void init_pll();
void init_peripheral_clock();

void SystemInit()
{
    init_pll();
    init_peripheral_clock();
}

void init_peripheral_clock()
{    // Enable clock on gpio ports
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    // configure gpio port c as output
    GPIOC_CRH &= ~GPIOC_CRH_MODE_MSK(13);
    GPIOC_CRH |= GPIOC_CRH_MODE_OUTPUT(13);
}

void init_pll()
{
    // Set Flash wait state
    FLASH_ACR |= FLASH_ACR_LATENCY_TWO;

    // Set APB divisor to 2
    RCC_CFGR &= ~RCC_CFGR_PPRE1_MSK;
    RCC_CFGR |= RCC_CFGR_PPRE1_2;

    // Set divisor before PLL to no division
    RCC_CFGR &= ~RCC_CFGR_PLLXTPRE_MSK;
    RCC_CFGR |= RCC_CFGR_PLLXTPRE_HSE;

    // Activate HSE and set as source for PLL
    RCC_CR |= RCC_CR_HSE_ON;
    while (!(RCC_CR & RCC_CR_HSE_RDY))
    {}

    RCC_CFGR &= ~RCC_CFGR_PLLSRC_MSK;
    RCC_CFGR |= RCC_CFGR_PLLSRC_HSE;

    // Set PLL multiplication
    RCC_CFGR &= ~RCC_CFGR_PLLMUL_MSK;
    RCC_CFGR |= RCC_CFGR_PLLMUL_9;

    // Activate PLL
    RCC_CR |= RCC_CR_PLLON;
    while (!(RCC_CR & RCC_CR_PLLRDY))
    {}

    // Set clock to PLL
    RCC_CFGR &= ~RCC_CFGR_SW_MSK;
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    while (!(RCC_CFGR & RCC_CFGR_SWS_PLL))
    {}

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