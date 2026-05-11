#include "stm32_gpio.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
        else if(pGPIOx == GPIOI)
        {
            GPIOI_PCLK_EN();
        }
    }
    else
    {

    }
}
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{       
    uint32_t temp = 0;
    GPIO_PeriClockControl(pGPIOHandle->pGPIOX, ENABLE);
    //1. Configure the mode of GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)        
    {
        //Non-interrupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOX->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing
        pGPIOHandle->pGPIOX->MODER |= temp; //Setting
    }
    else
    {
        //Interrupt mode
        //1. Configure Rising/Falling edge
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            //Configure the FTSR
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear RTSR bit
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            //Configure the RTSR
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear FTSR bit
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            //Configure both FTSR and RTSR
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        //2. Configure SYSCFG_EXTICR
        uint8_t temp1 , temp2;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4; //register number
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4; //bit position
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOX);
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4)); //Clearing
        SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4)); //Setting
        //3. Enable the EXTI interrupt delivery using IMR
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }
    //2. Configure the speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); 
    pGPIOHandle->pGPIOX->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing
    pGPIOHandle->pGPIOX->OSPEEDR |= temp; //Setting
    //3. Configure the pull-up/pull-down settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOX->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing
    pGPIOHandle->pGPIOX->PUPDR |= temp; //Setting
    //4. Configure the output type
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOX->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clearing
    pGPIOHandle->pGPIOX->OTYPER |= temp; //Setting
    //5. Configure the alternate functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; 
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOX->AFR[temp1] &= ~(0xF << (4 * temp2)); //Clearing
        pGPIOHandle->pGPIOX->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2)); //Setting
    }
}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if(pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
    else if(pGPIOx == GPIOI)
    {
        GPIOI_REG_RESET();
    }
}

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) 
{
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;
    value = (uint16_t)(pGPIOx->IDR);
    return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->BSRR |= (1 << PinNumber); 
    }
    else
    {
        pGPIOx->BSRR |= (1 << PinNumber) << 16; 
    }
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->BSRR = ((pGPIOx->ODR & PinNumber) << 16) | (~(pGPIOx->ODR) & PinNumber);
}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(IRQNumber <= 31) // 0 - 31: ISER0
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 63) // 32 - 63: ISER1
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96) // 64 - 95: ISER2
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
       if(IRQNumber <= 31) // 0 - 31: ICER0
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 63) // 32 - 63: ICER1
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96) // 64 - 95: ICER2
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_ip = IRQNumber & 4;
    *(NVIC_IPR_BASE + iprx) |= (IRQPriority << (8 * iprx_ip + 4));
}
void GPIO_IRQHandling(uint8_t PinNumber)
{
    if(EXTI->PR & (1 << PinNumber))
    {
        EXTI->PR |= (1 << PinNumber);
    }
}