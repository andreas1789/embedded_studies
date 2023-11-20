#ifndef AE1B5660_6C76_4B4D_93F4_58C4A45298A8
#define AE1B5660_6C76_4B4D_93F4_58C4A45298A8
#include "types.hpp"

using namespace types;
namespace bios
{
// Reset Clock Control - RCC
#define RCC_BASE 0x40021000

#define RCC_CR (*(volatile uint32_t *)(RCC_BASE + 0x0))
#define RCC_CR_HSE_ON (0x1 << 16)
#define RCC_CR_HSE_RDY (0x1 << 17)
#define RCC_CR_PLLON (0x1 << 24)
#define RCC_CR_PLLRDY (0x1 << 25)

#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPCEN (1 << 4)
#define RCC_APB2ENR_IOPAEN (1 << 2)

#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))
#define RCC_APB1ENR_USART2EN (1 << 17)

#define RCC_CFGR (*(volatile uint32_t *)(RCC_BASE + 0x4))
#define RCC_CFGR_PPRE1_MSK (0x7 << 8)
#define RCC_CFGR_PPRE1_2 (0x4)
#define RCC_CFGR_PLLXTPRE_MSK (0x1 << 17)
#define RCC_CFGR_PLLXTPRE_HSE 0
#define RCC_CFGR_PLLSRC_MSK (0x1 << 16) 
#define RCC_CFGR_PLLSRC_HSE 0 
#define RCC_CFGR_PLLMUL_MSK (0xf << 18)
#define RCC_CFGR_PLLMUL_9 (0x7 << 18)
#define RCC_CFGR_PLLMUL_4 (0x2 << 18)
#define RCC_CFGR_SW_MSK 0x3
#define RCC_CFGR_SW_PLL 0x2
#define RCC_CFGR_SWS_PLL (0x2 << 2)

// Flash ACR
#define FLASH_ACR_BASE 0x40022000

#define FLASH_ACR (*(volatile uint32_t *)(FLASH_ACR_BASE + 0x0))
#define FLASH_ACR_LATENCY_TWO 0x2


// System constants
#define PCLK1 36000000 // SystemCoreClock /2
}


#endif /* AE1B5660_6C76_4B4D_93F4_58C4A45298A8 */
