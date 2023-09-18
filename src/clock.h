typedef unsigned int uint32_t;


// Reset Clock Control - RCC
#define RCC_BASE 0x40021000

#define RCC_CR (*(volatile uint32_t *)(RCC_BASE + 0x0))

#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPCEN (1 << 4)


// General Purpose IO C - GPIOC
#define GPIOC_BASE 0x40011000 

#define GPIOC_CRL (*(volatile uint32_t *)(GPIOC_BASE + 0x0))
#define GPIOC_CRH (*(volatile uint32_t *)(GPIOC_BASE + 0x4))

#define GPIOC_CRH_MODE_MSK(x) (0x3 << ((x-8) * 4))
#define GPIOC_CRH_MODE_OUTPUT(x) (0x1 << ((x-8) * 4))
#define GPIOC_CRL_MODE_MSK(x) (0x3 << ((x) * 4))
#define GPIOC_CRL_MODE_OUTPUT(x) (0x1 << ((x) * 4))

#define GPIOC_ODR (*(volatile uint32_t *)(GPIOC_BASE + 0xC))
#define GPIOC_ODR_PIN(x) (0x1 << x)