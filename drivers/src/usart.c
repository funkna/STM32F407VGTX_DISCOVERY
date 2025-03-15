//------------------------------------------------------------------------------
//! \file usart.c
//! \brief Universal Synchronous Asynchronous Receiver Transmitter driver implementation.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include <string.h>
#include "constants.h"
#include "gpio.h"
#include "rcc.h"
#include "ringbuffer.h"
#include "nvic.h"
#include "usart.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define USART_BUFFER_SIZE (256)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief USART Device description
//------------------------------------------------------------------------------
typedef struct
{
   USARTRegistersStruct* pstRegisters;
   USARTConfigurationStruct stConfiguration;
   RingBufferStruct stTx;
   RingBufferStruct stRx;
} USARTDeviceStruct;

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static USARTDeviceStruct astTheUSARTDevices[USART_MAX] = {0};

static const GPIOConfigurationStruct stTheUSARTPinConfig = {
   GPIOMODE_ALT_FUNC,
   GPIOTYPE_PUSHPULL,
   GPIOSPEED_HI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF7
};

static STM32F407VGT6_PeriperalEnum aeUSARTPeripherals[USART_MAX] = {
   PERIPHERAL_USART1,
   PERIPHERAL_USART2,
   PERIPHERAL_USART3,
   PERIPHERAL_UART4,
   PERIPHERAL_UART5,
   PERIPHERAL_USART6
};

static USARTRegistersStruct* apstUSARTControllers[USART_MAX] = {
   (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART1,
   (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART2,
   (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART3,
   (USARTRegistersStruct*)PERIPHERAL_ADDRESS_UART4,
   (USARTRegistersStruct*)PERIPHERAL_ADDRESS_UART5,
   (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART6
};

//------------------------------------------------------------------------------
//! \brief IRQ Handler
//------------------------------------------------------------------------------
static void
USART_IRQHandler(
   USARTControllerEnum eController_)
{
   UCHAR ucDataByte = 0;
   if(astTheUSARTDevices[eController_].pstRegisters->SR & SR_TXE)
   {
      if(RingBuffer_Dequeue(&(astTheUSARTDevices[eController_].stTx), &ucDataByte, 1))
      {
         astTheUSARTDevices[eController_].pstRegisters->DR = ucDataByte;
      }

      if(RingBuffer_IsEmpty(&(astTheUSARTDevices[eController_].stTx)))
      {
         astTheUSARTDevices[eController_].pstRegisters->CR1 &= ~CR1_TXEIE;
      }
   }

   if(astTheUSARTDevices[eController_].pstRegisters->SR & SR_RXNE)
   {
      ucDataByte = astTheUSARTDevices[eController_].pstRegisters->DR;
      (void)RingBuffer_Enqueue(&(astTheUSARTDevices[eController_].stRx), &ucDataByte, 1);

      if(RingBuffer_IsFull(&(astTheUSARTDevices[eController_].stRx)))
      {
         astTheUSARTDevices[eController_].pstRegisters->CR1 &= ~CR1_RXNEIE;
      }
   }
}

//------------------------------------------------------------------------------
void USART1_IRQHandler(void) { USART_IRQHandler(USART1); }
void USART2_IRQHandler(void) { USART_IRQHandler(USART2); }
void USART3_IRQHandler(void) { USART_IRQHandler(USART3); }

//------------------------------------------------------------------------------
BOOL
USART_Initialize(
   USARTControllerEnum eController_,
   const USARTConfigurationStruct* pstConfiguration_)
{
   BOOL bSuccess = FALSE;
   astTheUSARTDevices[eController_].pstRegisters = apstUSARTControllers[eController_];
   if(astTheUSARTDevices[eController_].pstRegisters != NULL)
   {
      bSuccess = RCC_EnablePeripheralClock(aeUSARTPeripherals[eController_]);
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
            NVIC_ConfigureInterrupt(IRQ_VECTOR_USART1, IRQ_PRIORITY_0, IRQ_ENABLE);
            break;
         }
         case USART2:
         {
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_0, &stTheUSARTPinConfig); // CTS
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_1, &stTheUSARTPinConfig); // RTS
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_2, &stTheUSARTPinConfig); // TX
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_3, &stTheUSARTPinConfig); // RX
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_4, &stTheUSARTPinConfig); // CK
            NVIC_ConfigureInterrupt(IRQ_VECTOR_USART2, IRQ_PRIORITY_0, IRQ_ENABLE);
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

      USART_SetConfig(eController_, pstConfiguration_);

      astTheUSARTDevices[eController_].pstRegisters->CR1 |= CR1_UE;
      astTheUSARTDevices[eController_].pstRegisters->CR1 |= CR1_RXNEIE;
   }

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
USART_Reset(
   USARTControllerEnum eController_)
{
   if(astTheUSARTDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   switch(eController_)
   {
      case USART1:
      {
         NVIC_ConfigureInterrupt(IRQ_VECTOR_USART1, IRQ_PRIORITY_0, IRQ_CLEAR);
         break;
      }
      case USART2:
      {
         NVIC_ConfigureInterrupt(IRQ_VECTOR_USART2, IRQ_PRIORITY_0, IRQ_CLEAR);
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

   astTheUSARTDevices[eController_].pstRegisters->CR1 &= ~CR1_UE;

   return RCC_ResetPeripheralClock(aeUSARTPeripherals[eController_]);
}

//------------------------------------------------------------------------------
BOOL
USART_SetConfig(
   USARTControllerEnum eController_,
   const USARTConfigurationStruct* pstConfiguration_)
{
   if((astTheUSARTDevices[eController_].pstRegisters == NULL) ||
      (pstConfiguration_ == NULL) ||
      // TODO: Check PCLK2 for USART1 & 6.
      ((HSI_RC_CLK_FREQ_MHZ * HZ_TO_MHZ) != RCC_GetClockFrequency(CLKTYPE_PCLK1)))
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

//------------------------------------------------------------------------------
UINT
USART_ReadData(
   USARTControllerEnum eController_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   if((astTheUSARTDevices[eController_].pstRegisters == NULL) ||
      (uiDataLength_ > (USART_BUFFER_SIZE - astTheUSARTDevices[eController_].stRx.uiCount)))
   {
      return 0;
   }

   return RingBuffer_Dequeue(&(astTheUSARTDevices[eController_].stRx), pucData_, uiDataLength_);
}

//------------------------------------------------------------------------------
UINT
USART_WriteData(
   USARTControllerEnum eController_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   if((astTheUSARTDevices[eController_].pstRegisters == NULL) ||
      (uiDataLength_ > (USART_BUFFER_SIZE - astTheUSARTDevices[eController_].stTx.uiCount)))
   {
      return 0;
   }

   UINT uiBytesAdded = RingBuffer_Enqueue(&(astTheUSARTDevices[eController_].stTx), pucData_, uiDataLength_);
   if(uiBytesAdded)
   {
      astTheUSARTDevices[eController_].pstRegisters->CR1 |= CR1_TXEIE;
   }

   return uiBytesAdded;
}
