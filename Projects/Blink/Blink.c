#include "stm32f4xx.h"
#include "stm32_gpio.h"

static void delay(volatile uint32_t t)
{
    while(t--)
    {
        _asm_("nop");
    }
}

int main(void)
{
    GPIO_Handle_t GpioLed;
    GpioLed.pGPIOX = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GpioLed);
    while(1)
    {
        GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
        delay(800000);
    }
    return 0;
}