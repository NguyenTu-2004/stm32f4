#include "stm32f4xx.h"
#include "stm32_gpio.h"

void delay(void)
{
    for(uint32_t i = 0; i < 500000/2; i++);
}

int main(void)
{
    GPIO_Handle_t gpiobtn, gpioled;
    gpioled.pGPIOX = GPIOC;
    gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&gpioled);

    gpiobtn.pGPIOX = GPIOA;
    gpiobtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    gpiobtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    gpiobtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    gpiobtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_Init(&gpiobtn);
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, 15);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

    while(1)
    {

    }
    
    return 0;
}

void EXTI0_IRQHandler(void)
{
    delay();
    GPIO_IRQHandling(GPIO_PIN_NO_0);
    GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
}
