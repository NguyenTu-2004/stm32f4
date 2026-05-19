#include "stm32_gpio.h"
#include "stm32_spi.h"
#include "string.h"

/*
SPI1
PA4 - NSS
PA5 - SCK
PA6 - MISO
PA7 - MOSI
ALternate Function AF5
*/

void SPI_GPIOinit()
{
    // Config GPIOA as AF
    GPIO_Handle_t SPIPins;
    SPIPins.pGPIOX = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCLK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&SPIPins);
    
    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&SPIPins);

    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&SPIPins);

    //NSS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
    GPIO_Init(&SPIPins);
}

// Procedure
// 1. Select the BR[2:0] bits to define the serial clock baud rate (see SPI_CR1 register).
// 2. Select the CPOL and CPHA bits to define one of the four relationships between the
// data transfer and the serial clock (see Figure 248). This step is not required when the
// TI mode is selected.
// 3. Set the DFF bit to define 8- or 16-bit data frame format
// 4. Configure the LSBFIRST bit in the SPI_CR1 register to define the frame format. This
// step is not required when the TI mode is selected.
// 5. If the NSS pin is required in input mode, in hardware mode, connect the NSS pin to a
// high-level signal during the complete byte transmit sequence. In NSS software mode,
// set the SSM and SSI bits in the SPI_CR1 register. If the NSS pin is required in output
// mode, the SSOE bit only should be set. This step is not required when the TI mode is
// selected.
// 6. Set the FRF bit in SPI_CR2 to select the TI protocol for serial communications.
// 7. The MSTR and SPE bits must be set (they remain set only if the NSS pin is connected
// to a high-level signal).
// In this configuration the MOSI pin is a data output and the MISO pin is a data input.

void SPI1_Init()
{
    SPI_Handle_t SPI1_Handle;
    SPI1_Handle.pSPIx = SPI1;
    SPI1_Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI1_Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI1_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; //2MHz
    SPI1_Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI1_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI1_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI1_Handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

    SPI_Init(&SPI1_Handle);
}

int main(void)
{
    char buffer_data[] = "Hello";
    SPI_GPIOinit();
    SPI1_Init();

    SPI_SSOEConfig(SPI1, ENABLE);

    SPI_PeripheralControl(SPI1, ENABLE);

    SPI_SendData(SPI1, (uint8_t *)buffer_data, strle(buffer_data));

    while(SPI_GetFlagStatus(SPI1, SPI_BSY_FLAG));

    SPI_PeripheralControl(SPI1, DISABLE);

    while(1)
    {
        //todo
    }
    return 0;
}

