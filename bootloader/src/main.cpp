#include "../../base/include/types.hpp"
#include "../../base/include/clock.hpp"
#include "../../base/include/gpio.hpp"
#include "../../base/include/uartConsole.hpp"

using namespace types;


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
{
    // Enable clock on gpio ports a
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    // Enable usart2 clock
    RCC_APB1ENR |= RCC_APB1ENR_USART2EN;
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


static void  __attribute__((naked)) start_application(uint32_t pc, uint32_t sp)
{
    __asm("                                             \n\
            msr msp, r1 /* load main stack pointer */   \n\
            bx r0 /* load program counter */            \n\
    ");

    (void)pc;
    (void)sp;
}

::services::UartConsole logger = ::services::UartConsole(115200U,2U,3U);


int main()
{
    char buf[] = "\r\nEntering main function in Bootloader";
    logger.send(buf, sizeof(buf));

    //(void)start_application;
    uint32_t *app_code = (uint32_t *)0x08002000;
    uint32_t app_sp = app_code[0];
    uint32_t app_pc = app_code[1];
    start_application(app_pc, app_sp);

    while(1) {}

    return 0;
}