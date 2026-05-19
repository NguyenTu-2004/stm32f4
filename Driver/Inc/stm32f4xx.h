#ifndef _STM32F4XX_H
#define _STM32F4XX_H

#include <stdint.h>
#include <stddef.h>

//NVIC ISERx register addresses
#define NVIC_ISER0           ((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1           ((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2           ((volatile uint32_t*)0xE000E108)
//NVIC ICERx register addresses
#define NVIC_ICER0           ((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1           ((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2           ((volatile uint32_t*)0xE000E188)
//NVIC IPRx register addresses
#define NVIC_IPR_BASE        ((volatile uint32_t*)0xE000E400)

//Base addresses of Flash and SRAM memories
#define FLASH_BASE            0x08000000UL
#define SRAM1_BASE            0x20000000UL
#define SRAM2_BASE            0x2001C000UL
#define ROM_BASE              0x1FFF0000UL
#define SRAM_BASE              SRAM1_BASE

/* ============ Peripheral memory map ============ */
#define PERIPH_BASE            0x40000000UL
#define APB1PERIPH_BASE        PERIPH_BASE
#define APB2PERIPH_BASE        (PERIPH_BASE + 0x00010000UL) //  0x40010000UL
#define AHB1PERIPH_BASE        (PERIPH_BASE + 0x00020000UL) //  0x40020000UL
#define AHB2PERIPH_BASE        (PERIPH_BASE + 0x10000000UL) //  0x50000000UL

/* ============ AHB1 peripherals ============ */
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL) // 0x40020000UL
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400UL) // 0x40020400UL
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800UL) // 0x40020800UL
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00UL) // 0x40020C00UL
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000UL) // 0x40021000UL
#define GPIOF_BASE            (AHB1PERIPH_BASE + 0x1400UL) // 0x40021400UL
#define GPIOG_BASE            (AHB1PERIPH_BASE + 0x1800UL) // 0x40021800UL
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00UL) // 0x40021C00UL
#define GPIOI_BASE            (AHB1PERIPH_BASE + 0x2000UL) // 0x40022000UL

#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800UL) // 0x40023800UL

/* ============ APB1 peripherals ============ */
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL) // 0x40005400UL
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800UL) // 0x40005800UL
#define I2C3_BASE             (APB1PERIPH_BASE + 0x5C00UL) // 0x40005C00UL

#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL) // 0x40003800UL
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL) // 0x40003C00UL

#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL) // 0x40004400UL
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800UL) // 0x40004800UL
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00UL) // 0x40004C00UL
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000UL) // 0x40005000UL

/* ============ APB2 peripherals ============ */
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00UL) // 0x40013C00UL
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000UL) // 0x40013000UL
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800UL) // 0x40013800UL
#define USART1_BASE           (APB2PERIPH_BASE + 0x1000UL) // 0x40011000UL
#define USART6_BASE           (APB2PERIPH_BASE + 0x1400UL) // 0x40011400UL

/* ============= Register Structures ============ */

// GPIO
typedef struct 
{
    volatile uint32_t MODER;       /* GPIO port mode register,               Address offset: 0x00      */
    volatile uint32_t OTYPER;      /* GPIO port output type register,        Address offset: 0x04      */
    volatile uint32_t OSPEEDR;     /* GPIO port output speed register,       Address offset: 0x08      */
    volatile uint32_t PUPDR;       /* GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    volatile uint32_t IDR;         /* GPIO port input data register,         Address offset: 0x10      */
    volatile uint32_t ODR;         /* GPIO port output data register,        Address offset: 0x14      */
    volatile uint32_t BSRR;        /* GPIO port bit set/reset register,      Address offset: 0x18      */
    volatile uint32_t LCKR;        /* GPIO port configuration lock register, Address offset: 0x1C      */
    volatile uint32_t AFR[2];      /* GPIO alternate function registers,     Address offset: 0x20-0x24 */
}GPIO_RegDef_t;

#define GPIOA               ((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB               ((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC               ((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD               ((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOE               ((GPIO_RegDef_t*)GPIOE_BASE)
#define GPIOF               ((GPIO_RegDef_t*)GPIOF_BASE)
#define GPIOG               ((GPIO_RegDef_t*)GPIOG_BASE)
#define GPIOH               ((GPIO_RegDef_t*)GPIOH_BASE)
#define GPIOI               ((GPIO_RegDef_t*)GPIOI_BASE)

//RCC
typedef struct
{
    volatile uint32_t CR;           /* RCC clock control register,                                  Address offset: 0x00 */
    volatile uint32_t PLLCFGR;      /* RCC PLL configuration register,                                Address offset: 0x04 */
    volatile uint32_t CFGR;         /* RCC clock configuration register,                                Address offset: 0x08 */
    volatile uint32_t CIR;          /* RCC clock interrupt register,                                  Address offset: 0x0C */
    volatile uint32_t AHB1RSTR;     /* RCC AHB1 peripheral reset register,                                 Address offset: 0x10 */
    volatile uint32_t AHB2RSTR;     /* RCC AHB2 peripheral reset register,                                 Address offset: 0x14 */
    volatile uint32_t AHB3RSTR;     /* RCC AHB3 peripheral reset register,                                 Address offset: 0x18 */
             uint32_t RESERVED0;   /* Reserved, 0x1C                                                                    */
    volatile uint32_t APB1RSTR;     /* RCC APB1 peripheral reset register,                                 Address offset: 0x20 */
    volatile uint32_t APB2RSTR;     /* RCC APB2 peripheral reset register,                                 Address offset: 0x24 */
             uint32_t RESERVED1[2];/* Reserved, 0x28-0x2C                                                               */
    volatile uint32_t AHB1ENR;      /* RCC AHB1 peripheral clock enable register,                          Address offset: 0x30 */
    volatile uint32_t AHB2ENR;      /* RCC AHB2 peripheral clock enable register,                          Address offset: 0x34 */
    volatile uint32_t AHB3ENR;      /* RCC AHB3 peripheral clock enable register,                          Address offset: 0x38 */
             uint32_t RESERVED2[2]; /* Reserved, 0x3C                                                                    */
    volatile uint32_t APB1ENR;      /* RCC APB1 peripheral clock enable register,                          Address offset: 0x40 */
    volatile uint32_t APB2ENR;      /* RCC APB2 peripheral clock enable register,                          Address offset: 0x44 */
             uint32_t RESERVED3[2];/* Reserved, 0x48-0x4C                                                               */
    volatile uint32_t AHB1LPENR;    /* RCC AHB1 peripheral clock enable in low power mode register,           Address offset: 0x50 */
    volatile uint32_t AHB2LPENR;    /* RCC AHB2 peripheral clock enable in low power mode register,           Address offset: 0x54 */
    volatile uint32_t AHB3LPENR;    /* RCC AHB3 peripheral clock enable in low power mode register,           Address offset: 0x58 */
             uint32_t RESERVED4[2];/* Reserved, 0x5C                                                                    */
    volatile uint32_t APB1LPENR;    /* RCC APB1 peripheral clock enable in low power mode register,           Address offset: 0x60 */
    volatile uint32_t APB2LPENR;    /* RCC APB2 peripheral clock enable in low power mode register,           Address offset: 0x64 */
             uint32_t RESERVED5[2];/* Reserved, 0x68-0x6C                                                               */
    volatile uint32_t BDCR;         /* RCC Backup domain control register,                                 Address offset: 0x70 */
    volatile uint32_t CSR;          /* RCC clock control & status register,                                 Address offset: 0x74 */
             uint32_t RESERVED6[2];/* Reserved, 0x78-0x7C                                                               */
    volatile uint32_t SSCGR;        /* RCC spread spectrum clock generation register,                                 Address offset: 0x80 */
    volatile uint32_t PLLI2SCFGR;  /* RCC PLLI2S configuration register,                                 Address offset: 0x84 */
    volatile uint32_t PLLSAICFGR;  /* RCC PLLSAI configuration register,                                 Address offset: 0x88 */
    volatile uint32_t DCKCFGR;      /* RCC Dedicated Clocks configuration register,                                 Address offset: 0x8C */
    volatile uint32_t CKGATENR;     /* RCC Clocks Gated ENable Register,                                 Address offset: 0x90 */
    volatile uint32_t DCKCFGR2;     /* RCC Dedicated Clocks configuration register 2,                                 Address offset: 0x94 */
}RCC_RegDef_t;

#define RCC                 ((RCC_RegDef_t*)RCC_BASE)

//EXTI
typedef struct
{
    volatile uint32_t IMR;          /* EXTI Interrupt mask register,                                 Address offset: 0x00 */
    volatile uint32_t EMR;          /* EXTI Event mask register,                                     Address offset: 0x04 */
    volatile uint32_t RTSR;         /* EXTI Rising trigger selection register,                          Address offset: 0x08 */
    volatile uint32_t FTSR;         /* EXTI Falling trigger selection register,                         Address offset: 0x0C */
    volatile uint32_t SWIER;        /* EXTI Software interrupt event register,                         Address offset: 0x10 */
    volatile uint32_t PR;           /* EXTI Pending register,                                 Address offset: 0x14 */
}EXTI_RegDef_t;

#define EXTI                ((EXTI_RegDef_t*)EXTI_BASE)

//SPI
typedef struct 
{
    volatile uint32_t CR1;         /* SPI control register 1,                                 Address offset: 0x00 */
    volatile uint32_t CR2;         /* SPI control register 2,                                 Address offset*/
    volatile uint32_t SR;          /* SPI status register,                                 Address offset: 0x08 */
    volatile uint32_t DR;          /* SPI data register,                                 Address offset: 0x0C */
    volatile uint32_t CRCPR;       /* SPI CRC polynomial register,                                 Address offset: 0x10 */
    volatile uint32_t RXCRCR;      /* SPI RX CRC register,                                 Address offset: 0x14 */
    volatile uint32_t TXCRCR;      /* SPI TX CRC register,                                 Address offset: 0x18 */
    volatile uint32_t I2SCFGR;     /* SPI_I2S configuration register,                                 Address offset: 0x1C */
    volatile uint32_t I2SPR;       /* SPI_I2S prescaler register,                                 Address offset: 0x20 */
}SPI_RegDef_t;

#define SPI1                ((SPI_RegDef_t*)SPI1_BASE)
#define SPI2                ((SPI_RegDef_t*)SPI2_BASE)
#define SPI3                ((SPI_RegDef_t*)SPI3_BASE)

//SYSCFG
typedef struct
{
    volatile uint32_t MEMRMP;      /* SYSCFG memory remap register,                                 Address offset: 0x00 */
    volatile uint32_t PMC;         /* SYSCFG peripheral mode configuration register,                                 Address offset: 0x04 */
    volatile uint32_t EXTICR[4];   /* SYSCFG external interrupt configuration registers,                                 Address offset: 0x08-0x14 */
             uint32_t RESERVED[2]; /* Reserved, 0x18-0x1C                                                               */
    volatile uint32_t CMPCR;       /* SYSCFG Compensation cell control register,                                 Address offset: 0x20 */
}SYSCFG_RegDef_t;

#define SYSCFG              ((SYSCFG_RegDef_t*)SYSCFG_BASE)

//I2C
typedef struct
{
    volatile uint32_t CR1;         /* I2C control register 1,                                 Address offset: 0x00 */
    volatile uint32_t CR2;         /* I2C control register 2,                                 Address offset: 0x04 */
    volatile uint32_t OAR1;        /* I2C own address register 1,                                 Address offset: 0x08 */
    volatile uint32_t OAR2;        /* I2C own address register 2,                                 Address offset: 0x0C */
    volatile uint32_t DR;          /* I2C data register,                                 Address offset: 0x10 */
    volatile uint32_t SR1;         /* I2C status register 1,                                 Address offset: 0x14 */
    volatile uint32_t SR2;         /* I2C status register 2,                                 Address offset: 0x18 */
    volatile uint32_t CCR;         /* I2C clock control register,                                 Address offset: 0x1C */
    volatile uint32_t TRISE;       /* I2C TRISE register,                                 Address offset: 0x20 */
    volatile uint32_t FLTR;        /* I2C FLTR register,                                 Address offset: 0x24 */
}I2C_RegDef_t;

#define I2C1                ((I2C_RegDef_t*)I2C1_BASE)
#define I2C2                ((I2C_RegDef_t*)I2C2_BASE)
#define I2C3                ((I2C_RegDef_t*)I2C3_BASE)

//USART
typedef struct
{
    volatile uint32_t SR;          /* USART Status register,                                 Address offset: 0x00 */
    volatile uint32_t DR;          /* USART Data register,                                 Address offset: 0x04 */
    volatile uint32_t BRR;         /* USART Baud rate register,                                 Address offset: 0x08 */
    volatile uint32_t CR1;         /* USART Control register 1,                                 Address offset: 0x0C */
    volatile uint32_t CR2;         /* USART Control register 2,                                 Address offset: 0x10 */
    volatile uint32_t CR3;         /* USART Control register 3,                                 Address offset: 0x14 */
    volatile uint32_t GTPR;        /* USART Guard time and prescaler register,                                 Address offset: 0x18 */
}USART_RegDef_t;

#define USART1              ((USART_RegDef_t*)USART1_BASE)
#define USART2              ((USART_RegDef_t*)USART2_BASE)
#define USART3              ((USART_RegDef_t*)USART3_BASE)
#define UART4               ((USART_RegDef_t*)UART4_BASE)
#define UART5               ((USART_RegDef_t*)UART5_BASE)
#define USART6              ((USART_RegDef_t*)USART6_BASE)

/* ============= Peripheral Macros ============ */
/*
    * Clock Enable/Disable Macros for GPIOx peripherals
    * Note: x can be (A-H) depending on the device used
*/
#define GPIOA_PCLK_EN()    (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()    (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()    (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()    (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()    (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()    (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()    (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()    (RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()    (RCC->AHB1ENR |= (1 << 8))
#define GPIOA_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 8))

/*
    * Clock Enable/Disable Macros for I2Cx peripherals
    * Note: x can be (1-3) depending on the device used
*/
#define I2C1_PCLK_EN()     (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()     (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()     (RCC->APB1ENR |= (1 << 23))
#define I2C1_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 23))

/*
    * Clock Enable/Disable Macros for SPIx peripherals
    * Note: x can be (1-3) depending on the device used
*/
#define SPI1_PCLK_EN()     (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()     (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()     (RCC->APB1ENR |= (1 << 15))
#define SPI1_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 15))

/*
    * Clock Enable/Disable Macros for USARTx peripherals
    * Note: x can be (1-6) depending on the device used
*/
#define USART1_PCLK_EN()   (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()   (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()   (RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()    (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()    (RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()   (RCC->APB2ENR |= (1 << 5))
#define USART1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 5))

/*
    * Clock Enable/Disable Macros for SYSCFG peripherals
*/
#define SYSCFG_PCLK_EN()   (RCC->APB2ENR |= (1 << 14))
#define SYSCFG_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 14))

#define GPIOA_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)
#define GPIOI_REG_RESET()  do {(RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8));}while(0)

#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define FLAG_RESET          RESET
#define FLAG_SET            SET

#define GPIO_BASEADDR_TO_CODE(x)  ((x == GPIOA) ? 0 : \
                                    (x == GPIOB) ? 1 : \
                                    (x == GPIOC) ? 2 : \
                                    (x == GPIOD) ? 3 : \
                                    (x == GPIOE) ? 4 : \
                                    (x == GPIOF) ? 5 : \
                                    (x == GPIOG) ? 6 : \
                                    (x == GPIOH) ? 7 : \
                                    (x == GPIOI) ? 8 : 0)

#define IRQ_NO_EXTI0       6
#define IRQ_NO_EXTI1       7
#define IRQ_NO_EXTI2       8
#define IRQ_NO_EXTI3       9
#define IRQ_NO_EXTI4       10
#define IRQ_NO_EXTI9_5     23
#define IRQ_NO_EXTI15_10   40

//SPI CR1
#define SPI_CR1_CPHA       0
#define SPI_CR1_CPOL       1
#define SPI_CR1_MSTR       2
#define SPI_CR1_BR         3
#define SPI_CR1_SPE        6
#define SPI_CR1_LSBFIRST   7
#define SPI_CR1_SSI        8
#define SPI_CR1_SSM        9
#define SPI_CR1_RXONLY     10
#define SPI_CR1_DFF        11
#define SPI_CR1_CRCNEXT    12
#define SPI_CR1_CRCEN      13
#define SPI_CR1_BIDIOE     14
#define SPI_CR1_BIDIMODE   15

//SPI CR2
#define SPI_CR2_RXDMAEN    0
#define SPI_CR2_TXDMAEN    1
#define SPI_CR2_SSOE       2
#define SPI_CR2_FRF        4
#define SPI_CR2_ERRIE      5
#define SPI_CR2_RXNEIE     6
#define SPI_CR2_TXEIE      7

//SPI SR
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8

#endif /* _STM32F4XX_H */