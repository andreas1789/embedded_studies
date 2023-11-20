#ifndef C57F8165_841F_4FF8_9CDD_A6A500747FCE
#define C57F8165_841F_4FF8_9CDD_A6A500747FCE
#include "types.hpp"

namespace bsp
{
// General Purpose I/O - GPIOx
#define GPIOA_BASE 0x40010800
#define GPIOC_BASE 0x40011000 

#define GPIOx_CRL(x) (*(volatile uint32_t *)(x + 0x0))
#define GPIOx_CRH(x) (*(volatile uint32_t *)(x + 0x4))
#define GPIOA_CRL GPIOx_CRL(GPIOA_BASE)
#define GPIOA_CRH GPIOx_CRH(GPIOA_BASE)
#define GPIOC_CRL GPIOx_CRL(GPIOC_BASE)
#define GPIOC_CRH GPIOx_CRH(GPIOC_BASE)

#define GPIO_CRH_MODE_MSK(x) (0x3 << ((x-8) * 4))
#define GPIO_CRH_MODE_OUTPUT(x) (0x1 << ((x-8) * 4))
#define GPIO_CRH_MODE_INPUT(x) (0x0 << ((x-8) * 4))
#define GPIO_CRL_MODE_MSK(x) (0x3 << ((x) * 4))
#define GPIO_CRL_MODE_OUTPUT(x) (0x1 << ((x) * 4))
#define GPIO_CRL_MODE_INPUT(x) (0x0 << ((x) * 4))

#define GPIO_CRH_CNF_MSK(x) (0x3 << ((x-8) * 4 + 2))
#define GPIO_CRH_CNF_ALT_PUSH_PULL(x) (0x2 << ((x-8) * 4 + 2))
#define GPIO_CRH_CNF_FLOAT_INPUT(x) (0x1 << ((x-8) * 4 + 2))
#define GPIO_CRL_CNF_MSK(x) (0x3 << ((x) * 4 + 2))
#define GPIO_CRL_CNF_ALT_PUSH_PULL(x) (0x2 << ((x) * 4 + 2))
#define GPIO_CRL_CNF_FLOAT_INPUT(x) (0x1 << ((x) * 4 + 2))

#define GPIO_ODR (*(volatile uint32_t *)(GPIOC_BASE + 0xC))
#define GPIO_ODR_PIN(x) (0x1 << x)
}


#endif /* C57F8165_841F_4FF8_9CDD_A6A500747FCE */
