// Includes ---------------------------------------------------------------------------------------
#include <string.h>
#include "constants.h"
#include "stm32f407vgt6/usart.h"
#include "drivers/gpio_driver.h"
#include "drivers/rcc_driver.h"
#include "drivers/nvic_driver.h"
#include "drivers/usart_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
typedef struct
{
   UCHAR* pucDataBuffer;
   UINT uiDataBufferSize; // The size of the data to write or read.
   UINT uiDataBytes; // The current number of bytes received/transmitted.
} USARTBufferStruct;

typedef struct
{
   USARTRegistersStruct* pstRegisters;
   USARTConfigurationStruct stConfiguration;
   USARTBufferStruct stTxBuffer;
   USARTBufferStruct stRxBuffer;
   UCHAR ucTransferStates;
} USARTDeviceStruct;

// Statics, Externs & Globals ---------------------------------------------------------------------
static const GPIOConfigurationStruct stTheUSARTPinConfig = {
   GPIOMODE_ALT_FUNC,
   GPIOTYPE_PUSHPULL,
   GPIOSPEED_HI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF7
};
static USARTDeviceStruct astTheUSARTDevices[USART_MAX] = {0};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum USARTEnumToSTM32Enum(
   USARTControllerEnum eController_)
{
   switch(eController_)
   {
      case USART1:
      {
         return PERIPHERAL_USART1;
      }
      case USART2:
      {
         return PERIPHERAL_USART2;
      }
      case USART3:
      {
         return PERIPHERAL_USART3;
      }
      case USART4:
      {
         return PERIPHERAL_UART4;
      }
      case USART5:
      {
         return PERIPHERAL_UART5;
      }
      case USART6:
      {
         return PERIPHERAL_USART6;
      }
      default:
      {
         return PERIPHERAL_INVALID;
      }
   }
}

// -------------------------------------------------------------
static void USART_IRQHandler(
   USARTControllerEnum eController_)
{
   if(astTheUSARTDevices[eController_].pstRegisters->SR & SR_TXE)
   {
      astTheUSARTDevices[eController_].pstRegisters->DR = *(astTheUSARTDevices[eController_].stTxBuffer.pucDataBuffer);
      astTheUSARTDevices[eController_].stTxBuffer.pucDataBuffer++;
      astTheUSARTDevices[eController_].stTxBuffer.uiDataBytes++;

      if(astTheUSARTDevices[eController_].stTxBuffer.uiDataBytes == astTheUSARTDevices[eController_].stTxBuffer.uiDataBufferSize)
      {
         astTheUSARTDevices[eController_].pstRegisters->CR1 &= ~CR1_TXEIE;
         astTheUSARTDevices[eController_].ucTransferStates &= ~USARTSTATE_TX_IN_PROGRESS;
      }
   }

   if(astTheUSARTDevices[eController_].pstRegisters->SR & SR_RXNE)
   {
      *(astTheUSARTDevices[eController_].stRxBuffer.pucDataBuffer) = astTheUSARTDevices[eController_].pstRegisters->DR;
      astTheUSARTDevices[eController_].stRxBuffer.pucDataBuffer++;
      astTheUSARTDevices[eController_].stRxBuffer.uiDataBytes++;

      if(astTheUSARTDevices[eController_].stRxBuffer.uiDataBytes == astTheUSARTDevices[eController_].stRxBuffer.uiDataBufferSize)
      {
         astTheUSARTDevices[eController_].pstRegisters->CR1 &= ~CR1_RXNEIE;
         astTheUSARTDevices[eController_].ucTransferStates &= ~USARTSTATE_RX_IN_PROGRESS;
      }
   }
}

// -------------------------------------------------------------
// USART EV IRQ Vector Callbacks
// -------------------------------------------------------------
void USART1_IRQHandler(void)
{
   USART_IRQHandler(USART1);
}

void USART2_IRQHandler(void)
{
   USART_IRQHandler(USART2);
}

void USART3_IRQHandler(void)
{
   USART_IRQHandler(USART3);
}

// -------------------------------------------------------------
BOOL USART_Initialize(
   USARTControllerEnum eController_)
{
   BOOL bSuccess = FALSE;
   astTheUSARTDevices[eController_].pstRegisters = GetUSARTController(eController_);
   if(astTheUSARTDevices[eController_].pstRegisters != NULL)
   {
      bSuccess = RCC_EnablePeripheralClock(USARTEnumToSTM32Enum(eController_));
   }

   if(bSuccess)
   {
      switch(eController_)
      {
         case USART1:
         {
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_8, &stTheUSARTPinConfig); // CK
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_9, &stTheUSARTPinConfig); // TX
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_10, &stTheUSARTPinConfig); // RX
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_11, &stTheUSARTPinConfig); // CTS
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_12, &stTheUSARTPinConfig); // RTS
            break;
         }
         case USART2:
         {
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_0, &stTheUSARTPinConfig); // CTS
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_1, &stTheUSARTPinConfig); // RTS
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_2, &stTheUSARTPinConfig); // TX
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_3, &stTheUSARTPinConfig); // RX
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_4, &stTheUSARTPinConfig); // CK
            break;
         }
         case USART3: // TODO: Fall-through for now
         case USART4: // TODO: Fall-through for now
         case USART5: // TODO: Fall-through for now
         case USART6: // TODO: Fall-through for now
         default:
         {
            return FALSE;
         }
      }
   }

   return bSuccess;
}

// -------------------------------------------------------------
BOOL USART_Reset(
   USARTControllerEnum eController_)
{
   return RCC_ResetPeripheralClock(USARTEnumToSTM32Enum(eController_));
}

// -------------------------------------------------------------
BOOL USART_Enable(
   USARTControllerEnum eController_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheUSARTDevices[eController_].pstRegisters->CR1 |= CR1_UE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL USART_Disable(
   USARTControllerEnum eController_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheUSARTDevices[eController_].pstRegisters->CR1 &= ~CR1_UE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL USART_SetConfig(
   USARTControllerEnum eController_,
   const USARTConfigurationStruct* pstConfiguration_)
{
   if((astTheUSARTDevices[eController_].pstRegisters == NULL) ||
      (pstConfiguration_ == NULL) ||
      // TODO: Check PCLK2 for USART1 & 6.
      ((HSI_RC_CLK_FREQ_MHZ * MHZ_TO_HZ) != RCC_GetClockFrequency(CLKTYPE_PCLK1)))
   {
      return FALSE;
   }

   UINT uiMantissaBRR = 0;
   UCHAR ucFractionBRR = 0;
   UINT uiBRRValue = 0;
   UINT uiCR1Value = astTheUSARTDevices[eController_].pstRegisters->CR1;
   UINT uiCR2Value = astTheUSARTDevices[eController_].pstRegisters->CR2;
   UINT uiCR3Value = astTheUSARTDevices[eController_].pstRegisters->CR3;

   // Enable Tx & Rx
   uiCR1Value |= CR1_TE;
   uiCR1Value |= CR1_RE;

   // Baud Rate
   switch(pstConfiguration_->eBaudRate)
   {
      case USARTBAUD_1200:
      {
         uiMantissaBRR = 833;
         ucFractionBRR = 5;
         break;
      }
      case USARTBAUD_2400:
      {
         uiMantissaBRR = 416;
         ucFractionBRR = 11;
         break;
      }
      case USARTBAUD_9600:
      {
         uiMantissaBRR = 104;
         ucFractionBRR = 3;
         break;
      }
      case USARTBAUD_19200:
      {
         uiMantissaBRR = 52;
         ucFractionBRR = 1;
         break;
      }
      case USARTBAUD_38400:
      {
         uiMantissaBRR = 26;
         ucFractionBRR = 1;
         break;
      }
      case USARTBAUD_57600:
      {
         uiMantissaBRR = 13;
         ucFractionBRR = 0;
         break;
      }
      case USARTBAUD_115200:
      {
         uiMantissaBRR = 8;
         ucFractionBRR = 11;
         break;
      }
      case USARTBAUD_230400:
      {
         uiMantissaBRR = 4;
         ucFractionBRR = 5;
         break;
      }
      case USARTBAUD_460800:
      {
         uiMantissaBRR = 2;
         ucFractionBRR = 3;
         break;
      }
      default:
      {
         return FALSE;
      }
   }

   uiBRRValue = ((uiMantissaBRR << BRR_DIVMANT_OFFSET) & BRR_DIVMANT) |
                ((ucFractionBRR << BRR_DIVFRAC_OFFSET) & BRR_DIVFRAC);

   // Word length
   if(pstConfiguration_->eWordLength == USARTWORD_8BIT)
   {
      uiCR1Value &= ~CR1_M;
   }

   // Parity bits
   if(pstConfiguration_->ePartiy == USARTPARITY_NONE)
   {
      uiCR1Value &= ~CR1_PCE;
   }
   else
   {
      uiCR1Value |= CR1_PCE;

      if(pstConfiguration_->ePartiy == USARTPARITY_ODD)
      {
         uiCR1Value |= CR1_PS;
      }
      else
      {
         uiCR1Value &= ~CR1_PS;
      }
   }

   // Stop bits
   switch(pstConfiguration_->eStopBits)
   {
      case USARTSTOP_1BIT:
      {
         uiCR2Value |= (CR2_STOP_BITS_1 << CR2_STOP_OFFSET);
         break;
      }
      case USARTSTOP_0_5BIT:
      {
         uiCR2Value |= (CR2_STOP_BITS_0_5 << CR2_STOP_OFFSET);
         break;
      }
      case USARTSTOP_2BIT:
      {
         uiCR2Value |= (CR2_STOP_BITS_2 << CR2_STOP_OFFSET);
         break;
      }
      case USARTSTOP_1_5BIT:
      {
         uiCR2Value |= (CR2_STOP_BITS_1_5 << CR2_STOP_OFFSET);
         break;
      }
      default:
      {
         return FALSE;
      }
   }

   // Flow control
   switch(pstConfiguration_->eFlowControl)
   {
      case USARTFLOWCTL_CTS:
      {
         uiCR3Value |= CR3_CTSE;
         uiCR3Value &= ~CR3_RTSE;
         break;
      }
      case USARTFLOWCTL_RTS:
      {
         uiCR3Value &= ~CR3_CTSE;
         uiCR3Value |= CR3_RTSE;
         break;
      }
      case USARTFLOWCTL_CTS_RTS:
      {
         uiCR3Value |= CR3_CTSE;
         uiCR3Value |= CR3_RTSE;
         break;
      }
      default:
      {
         uiCR3Value &= ~CR3_CTSE;
         uiCR3Value &= ~CR3_RTSE;
         break;
      }
   }

   // Write the register values.
   astTheUSARTDevices[eController_].pstRegisters->BRR = uiBRRValue;
   astTheUSARTDevices[eController_].pstRegisters->CR1 = uiCR1Value;
   astTheUSARTDevices[eController_].pstRegisters->CR2 = uiCR2Value;
   astTheUSARTDevices[eController_].pstRegisters->CR3 = uiCR3Value;

   memcpy(&(astTheUSARTDevices[eController_].stConfiguration), pstConfiguration_, sizeof(USARTConfigurationStruct));

   return TRUE;
}

// -------------------------------------------------------------
USARTConfigurationStruct* USART_GetConfig(
   USARTControllerEnum eController_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return NULL;
   }

   return &(astTheUSARTDevices[eController_].stConfiguration);
}

// -------------------------------------------------------------
BOOL USART_ReadData(
   USARTControllerEnum eController_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   for(UINT uiIndex = 0; uiIndex < uiDataLength_; uiIndex++)
   {
      while(!(astTheUSARTDevices[eController_].pstRegisters->SR & SR_RXNE));

      *pucData_ = astTheUSARTDevices[eController_].pstRegisters->DR;

      pucData_++;
   }

	return FALSE;
}

// -------------------------------------------------------------
BOOL USART_WriteData(
   USARTControllerEnum eController_,
   const UCHAR* pucData_,
   UINT uiDataLength_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   for(UINT uiIndex = 0; uiIndex < uiDataLength_; uiIndex++)
   {
      while(!(astTheUSARTDevices[eController_].pstRegisters->SR & SR_TXE));

      astTheUSARTDevices[eController_].pstRegisters->DR = *pucData_;
      pucData_++;
   }

   while(!(astTheUSARTDevices[eController_].pstRegisters->SR & SR_TC));

   return TRUE;
}

// -------------------------------------------------------------
BOOL USART_Transfer(
   USARTControllerEnum eController_,
   USARTTransferTypeEnum eTransferType_,
   UCHAR* pucBuffer_,
   UINT uiSize_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   if(eTransferType_ == USARTTRANSFER_READ)
   {
      if(!(astTheUSARTDevices[eController_].ucTransferStates & USARTSTATE_RX_IN_PROGRESS))
      {
         astTheUSARTDevices[eController_].stRxBuffer.pucDataBuffer = pucBuffer_;
         astTheUSARTDevices[eController_].stRxBuffer.uiDataBufferSize = uiSize_;
         astTheUSARTDevices[eController_].stRxBuffer.uiDataBytes = 0;

         astTheUSARTDevices[eController_].pstRegisters->CR1 |= CR1_RXNEIE;
         astTheUSARTDevices[eController_].ucTransferStates |= USARTSTATE_RX_IN_PROGRESS;
      }
      else
      {
         return FALSE;
      }
   }

   if(eTransferType_ == USARTTRANSFER_WRITE)
   {
      if(!(astTheUSARTDevices[eController_].ucTransferStates & USARTSTATE_TX_IN_PROGRESS))
      {
         astTheUSARTDevices[eController_].stRxBuffer.pucDataBuffer = pucBuffer_;
         astTheUSARTDevices[eController_].stRxBuffer.uiDataBufferSize = uiSize_;
         astTheUSARTDevices[eController_].stRxBuffer.uiDataBytes = 0;

         astTheUSARTDevices[eController_].pstRegisters->CR1 |= CR1_TXEIE;
         astTheUSARTDevices[eController_].ucTransferStates |= USARTSTATE_TX_IN_PROGRESS;
      }
      else
      {
         return FALSE;
      }
   }

   return FALSE;
}

// -------------------------------------------------------------
USARTTransferStateEnum USART_GetStates(
   USARTControllerEnum eController_)
{
   return astTheUSARTDevices[eController_].ucTransferStates;
}

// -------------------------------------------------------------
BOOL USART_ConfigureAsInterrupt(
   USARTControllerEnum eController_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   IRQVectorEnum eIRQVector = IRQ_VECTOR_MAX;
   switch(eController_)
   {
      case USART1:
      {
         eIRQVector = IRQ_VECTOR_USART1;
         break;
      }
      case USART2:
      {
         eIRQVector = IRQ_VECTOR_USART2;
         break;
      }
      case USART3:
      {
         eIRQVector = IRQ_VECTOR_USART3;
         break;
      }
      default:
         return FALSE;
   }

   astTheUSARTDevices[eController_].ucTransferStates = USARTSTATE_IDLE;

   return NVIC_ConfigureInterrupt(eIRQVector, IRQ_PRIORITY_0, IRQ_ENABLE);
}

