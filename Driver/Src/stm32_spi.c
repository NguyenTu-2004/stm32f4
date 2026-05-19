#include "stm32_spi.h"

static void SPI_TXE_INTERRUPT_HANDLE(SPI_Handle_t *pSPIHandle);
static void SPI_RXNE_INTERRUPT_HANDLE(SPI_Handle_t *pSPIHandle);
static void SPI_OVR_INTERRUPT_HANDLE(SPI_Handle_t *pSPIHandle);

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
    }
    else
    {
        
    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    uint32_t temp = 0; 

    //1. Configure the device mode
    temp |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
    //2. Configure the bus config
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE);
        temp &= ~(1 << SPI_CR1_RXONLY);
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        temp |= (1 << SPI_CR1_BIDIMODE);
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        temp &= ~(1 << SPI_CR1_BIDIMODE);
        temp |= (1 << SPI_CR1_RXONLY);
    }
    //3. Configure baud rate
    temp |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
    //4. Configure data frame format
    temp |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;
    //5. Configure CPOL
    temp |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
    //6. Configure CPHA
    temp |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
    //7. Configure SSM
    temp |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

    pSPIHandle->pSPIx->CR1 = temp;
}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    //todo
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
    if(pSPIx->SR & FlagName)
    {
        return FlagName;
    }
    return FLAG_RESET;
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len) 
{
    while(Len > 0)
    {
        while(SPI_GetFlagStatus(pSPIx, SPI_TXEN_FLAG) == FLAG_RESET );
        if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            //16 bit DFF
            pSPIx->DR= *((uint16_t *)pTxBuffer);
            Len -= 2;
            pTxBuffer += 2;
        }else{
            //8 bit DFF
            pSPIx->DR= *pTxBuffer;
            Len--;
            pTxBuffer++;
        }
    }
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == (uint8_t)FLAG_RESET);

        if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            *((uint16_t*)pRxBuffer) = pSPIx->DR;
            Len -= 2;
            pRxBuffer += 2;
        }else{
            *(pRxBuffer) = pSPIx->DR;
            Len--;
            pRxBuffer++;
        }
    }
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    }else{
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
    }
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }else{
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }else{
        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->TxState;

    if(state != SPI_BUSY_IN_TX)
    {
        pSPIHandle->pTxBufferHandle = pTxBuffer;
        pSPIHandle->TxLen = Len;

        pSPIHandle->TxState = SPI_BUSY_IN_TX;

        pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
    }

    return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->RxState;

    if(state != SPI_BUSY_IN_RX)
    {
        pSPIHandle->pRxBufferHandle = pRxBuffer;
        pSPIHandle->RxLen = Len;

        pSPIHandle->RxState = SPI_BUSY_IN_RX;

        pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
    }

    return state;
}

void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
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

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_ip = IRQNumber % 4;
    *(NVIC_IPR_BASE + iprx) |= (IRQPriority << (8 * iprx_ip + 4));
}

void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
    uint8_t temp1, temp2;
    //TXE
    temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_TXE);
    temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);
    if(temp1 && temp2)
    {
        SPI_TXE_INTERRUPT_HANDLE(pHandle);
    } 

    //RXNE
    temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
    temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);
    if(temp1 && temp2)
    {
        SPI_RNXE_INTERRUPT_HANDLE(pHandle);
    } 

    //OVR
    temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);
    temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);
    if(temp1 && temp2)
    {
        SPI_OVR_INTERRUPT_HANDLE(pHandle);
    } 
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
    pSPIHandle->pTxBufferHandle = NULL;
    pSPIHandle->TxLen = 0;
    pSPIHandle->TxState = SPI_READY;
}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
    pSPIHandle->pRxBufferHandle = NULL;
    pSPIHandle->RxLen = 0;
    pSPIHandle->RxState = SPI_READY;
}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
    uint8_t temp;
    temp = pSPIx->DR;
    temp = pSPIx->SR;
    (void)temp;
}

static void SPI_TXE_INTERRUPT_HANDLE(SPI_Handle_t *pSPIHandle)
{
    if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            //16 bit DFF
            pSPIHandle->pSPIx->DR= *((uint16_t *)pSPIHandle->pTxBufferHandle);
            pSPIHandle->TxLen--;
            pSPIHandle->TxLen--;
            (uint16_t *)pSPIHandle->pTxBufferHandle++;
        }else{
            //8 bit DFF
            pSPIHandle->pSPIx->DR= *(pSPIHandle->pTxBufferHandle);
            pSPIHandle->TxLen--;
            pSPIHandle->pTxBufferHandle++;
        }
    if(!pSPIHandle->TxLen)
    {
        SPI_CloseTransmission(pSPIHandle);
        SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_TX_CMPLT);
    }
}


static void SPI_RXNE_INTERRUPT_HANDLE(SPI_Handle_t *pSPIHandle)
{
    if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            //16 bit DFF
            *((uint16_t *)pSPIHandle->pRxBufferHandle) = (uint16_t)pSPIHandle->pSPIx->DR;
            pSPIHandle->RxLen -= 2;
            pSPIHandle->pRxBufferHandle++;
            pSPIHandle->pRxBufferHandle++;
        }else{
            //8 bit DFF
            *(pSPIHandle->pRxBufferHandle) = (uint8_t)pSPIHandle->pSPIx->DR;
            pSPIHandle->RxLen--;
            pSPIHandle->pRxBufferHandle++;
        }
    if(!pSPIHandle->RxLen)
    {
        SPI_CloseReception(pSPIHandle);
        SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_RX_CMPLT);
    }
}

static void SPI_OVR_INTERRUPT_HANDLE(SPI_Handle_t *pSPIHandle)
{
    uint8_t temp;
    //1. clear ovr flag
    if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
    {
        temp = pSPIHandle->pSPIx->DR;
        temp = pSPIHandle->pSPIx->SR;
    }
    (void)temp;
    //2. inform the application
    SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_OVR_CMPLT);
}

__attribute__((weak)) void SPI_ApplicationEventCallBack(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{

}