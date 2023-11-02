#include "../../base/include/types.hpp"
#include "../../base/include/clock.hpp"
#include "../../base/include/gpio.hpp"
#include "../../base/include/uartConsole.hpp"

using namespace types;
using namespace peripherals;
using namespace services;

void init_core_clocks();
void init_peripheral_clocks();
void init_array();
void init_hw();

extern void (*_spreinit_array []) (void) __attribute__((weak));
extern void (*_sinit_array []) (void) __attribute__((weak));
extern void (*_epreinit_array []) (void) __attribute__((weak));
extern void (*_einit_array []) (void) __attribute__((weak));

void SystemInit()
{
    init_core_clocks();
    init_peripheral_clocks();
    init_array();
}

void init_peripheral_clocks()
{    // Enable clock on gpio ports c and a
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Enable usart2 clock
    RCC_APB1ENR |= RCC_APB1ENR_USART2EN;

    // configure gpio port c as output
    GPIOC_CRH &= ~GPIO_CRH_MODE_MSK(13);
    GPIOC_CRH |= GPIO_CRH_MODE_OUTPUT(13);
}

void init_core_clocks()
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

void init_array()
{
    uint32_t size;
    size = &(_einit_array[0]) - &(_sinit_array[0]);
    for(uint32_t i=0U; i<size; ++i)
    {
        _sinit_array[i]();
    }
    
    size = &(_epreinit_array[0]) - &(_spreinit_array[0]);
    for(uint32_t i=0U; i<size; ++i)
    {
        _spreinit_array[i]();
    }
}

void init_hw()
{
    // Setup I/O
    // Setup ADC
    // Setup DMA
}

UartConsole logger = UartConsole(115200U,2U,3U);

int main()
{

    init_hw();

    while(1)
    {

        // play uart
        //char b;
        //logger.receiveByte(b);
        //logger.sendByte('b');
        char buf[] = "\r\nHello World!";
        logger.send(buf, sizeof(buf));

        // switch on led
        GPIO_ODR |= GPIO_ODR_PIN(13);

        for (uint32_t i = 0; i < 4000000; ++i) 
        {
            __asm__ volatile("nop");
        }

        // switch off led
        GPIO_ODR &= ~GPIO_ODR_PIN(13);

        for (uint32_t i = 0; i < 1000000; ++i) 
        {
            __asm__ volatile("nop");
        }
    }
    return 0;
}