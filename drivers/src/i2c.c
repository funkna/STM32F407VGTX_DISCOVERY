//------------------------------------------------------------------------------
//! \file i2c.c
//! \brief Inter-Integrated Circuit driver implementation.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include <string.h>
#include "constants.h"
#include "i2c.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define I2C_FREQ_100KHZ (100000)
#define I2C_FREQ_200KHZ (200000)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief Transfer buffers description
//------------------------------------------------------------------------------
typedef struct
{
   UCHAR ucAddress;
   I2CTransferTypeEnum eTransferType;
   UCHAR* pucDataBuffer;
   UINT uiDataBufferSize; // The size of the data to write or read.
   UINT uiDataBytes; // The current number of bytes received/transmitted.
} I2CBuffersStruct;

//------------------------------------------------------------------------------
//! \brief I2C Device description
//------------------------------------------------------------------------------
typedef struct
{
   I2CRegistersStruct* pstRegisters;
   I2CConfigurationStruct stConfiguration;
   I2CBuffersStruct stBuffers;
   I2CTransferStateEnum eTransferState;
} I2CDeviceStruct;

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static I2CDeviceStruct astTheI2CDevices[I2C_MAX] = {NULL};

static GPIOConfigurationStruct stTheI2CPinConfig = {
   GPIOMODE_ALT_FUNC,
   GPIOTYPE_OPENDRAIN,
   GPIOSPEED_HI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF4
};

//------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum
I2CEnumToSTM32Enum(
   I2CControllerEnum eController_)
{
   switch(eController_)
   {
      case I2C1:
      {
         return PERIPHERAL_I2C1;
      }
      case I2C2:
      {
         return PERIPHERAL_I2C2;
      }
      case I2C3:
      {
         return PERIPHERAL_I2C3;
      }
      default:
      {
         return PERIPHERAL_INVALID;
      }
   }
}

//------------------------------------------------------------------------------
static I2CRegistersStruct*
GetI2CController(
   I2CControllerEnum eController_)
{
   switch(eController_)
   {
      case I2C1:
         return (I2CRegistersStruct*)PERIPHERAL_ADDRESS_I2C1;
      case I2C2:
         return (I2CRegistersStruct*)PERIPHERAL_ADDRESS_I2C2;
      case I2C3:
         return (I2CRegistersStruct*)PERIPHERAL_ADDRESS_I2C3;
      default:
         return NULL;
   }
}

//------------------------------------------------------------------------------
//! \brief IRQ Handler
//------------------------------------------------------------------------------
static void
I2C_IRQHandler(
   I2CControllerEnum eController_)
{
   switch(astTheI2CDevices[eController_].eTransferState)
   {
      case I2CSTATE_BEGIN:
      {
         if(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_SB)
         {
            if(astTheI2CDevices[eController_].stBuffers.eTransferType == I2CTRANSFER_READ)
            {
               astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_ACK;
            }

            UCHAR ucSendAddr = (astTheI2CDevices[eController_].stBuffers.ucAddress << 1) | astTheI2CDevices[eController_].stBuffers.eTransferType;
            astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

            astTheI2CDevices[eController_].eTransferState = I2CSTATE_START_SENT;
         }
         break;
      }
      case I2CSTATE_START_SENT:
      {
         if(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR)
         {
            // UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
            // uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;
            astTheI2CDevices[eController_].pstRegisters->SR1;
            astTheI2CDevices[eController_].pstRegisters->SR2;

            astTheI2CDevices[eController_].eTransferState = I2CSTATE_IN_PROGRESS;
         }
      } // Intentional fall-through
      case I2CSTATE_IN_PROGRESS:
      {
         // Transfer data as long as the current number of transferred bytes is not what we have expected.
         if(astTheI2CDevices[eController_].stBuffers.uiDataBytes < astTheI2CDevices[eController_].stBuffers.uiDataBufferSize)
         {
            if((astTheI2CDevices[eController_].stBuffers.eTransferType == I2CTRANSFER_WRITE) &&
               (astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_TXE))
            {
               // Write another byte
               astTheI2CDevices[eController_].pstRegisters->DR = *(astTheI2CDevices[eController_].stBuffers.pucDataBuffer);

               astTheI2CDevices[eController_].stBuffers.pucDataBuffer++;
               astTheI2CDevices[eController_].stBuffers.uiDataBytes++;

               // Transfer is complete - send the STOP and shut down the interrupts
               if(astTheI2CDevices[eController_].stBuffers.uiDataBytes == astTheI2CDevices[eController_].stBuffers.uiDataBufferSize)
               {
                  astTheI2CDevices[eController_].eTransferState = I2CSTATE_DATA_SENT;
               }
            }
            else if((astTheI2CDevices[eController_].stBuffers.eTransferType == I2CTRANSFER_READ) &&
                    (astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_RXNE))
            {
               // Transfer is about to be completed - send the STOP and shut down the interrupts
               if(1 == (astTheI2CDevices[eController_].stBuffers.uiDataBytes - astTheI2CDevices[eController_].stBuffers.uiDataBufferSize))
               {
                  astTheI2CDevices[eController_].pstRegisters->CR1 &= ~CR1_ACK;
                  astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_STOP;

                  astTheI2CDevices[eController_].eTransferState = I2CSTATE_IDLE;
                  astTheI2CDevices[eController_].pstRegisters->CR2 &= ~CR2_ITBUFEN;
                  astTheI2CDevices[eController_].pstRegisters->CR2 &= ~CR2_ITEVTEN;
               }

               // Read another byte
               *astTheI2CDevices[eController_].stBuffers.pucDataBuffer = astTheI2CDevices[eController_].pstRegisters->DR;

               astTheI2CDevices[eController_].stBuffers.pucDataBuffer++;
               astTheI2CDevices[eController_].stBuffers.uiDataBytes++;
            }
         }

         break;
      }
      case I2CSTATE_DATA_SENT:
      {
         astTheI2CDevices[eController_].eTransferState = I2CSTATE_IDLE;

         astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_STOP;
         astTheI2CDevices[eController_].pstRegisters->CR2 &= ~CR2_ITBUFEN;
         astTheI2CDevices[eController_].pstRegisters->CR2 &= ~CR2_ITEVTEN;
         break;
      }
      default:
      {
         astTheI2CDevices[eController_].eTransferState = I2CSTATE_ERROR;
         break;
      }
   }
}

//------------------------------------------------------------------------------
void I2C1_EV_IRQHandler(void) { I2C_IRQHandler(I2C1); }
void I2C2_EV_IRQHandler(void) { I2C_IRQHandler(I2C2); }
void I2C3_EV_IRQHandler(void) { I2C_IRQHandler(I2C3); }

//------------------------------------------------------------------------------
BOOL
I2C_Initialize(
   I2CControllerEnum eController_)
{
   BOOL bSuccess = FALSE;
   astTheI2CDevices[eController_].pstRegisters = GetI2CController(eController_);
   if(astTheI2CDevices[eController_].pstRegisters != NULL)
   {
      bSuccess = RCC_EnablePeripheralClock(I2CEnumToSTM32Enum(eController_));
   }

   if(bSuccess)
   {
      switch(eController_)
      {
         case I2C1:
         {
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_8, &stTheI2CPinConfig); // SCL
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_7, &stTheI2CPinConfig); // SDA
            break;
         }
         case I2C2:
         {
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_10, &stTheI2CPinConfig); // SCL
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_11, &stTheI2CPinConfig); // SDA
            break;
         }
         case I2C3: // TODO
         default:
         {
            return FALSE;
         }
      }
   }

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
I2C_Reset(
   I2CControllerEnum eController_)
{
   return RCC_ResetPeripheralClock(I2CEnumToSTM32Enum(eController_));
}

//------------------------------------------------------------------------------
BOOL
I2C_Enable(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_PE;
   return TRUE;
}

//------------------------------------------------------------------------------
BOOL
I2C_Disable(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheI2CDevices[eController_].pstRegisters->CR1 &= ~CR1_PE;
   return TRUE;
}

//------------------------------------------------------------------------------
BOOL
I2C_SetConfig(
   I2CControllerEnum eController_,
   const I2CConfigurationStruct* pstConfiguration_)
{
   if((astTheI2CDevices[eController_].pstRegisters == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   UINT uiPCLK1Frequency = RCC_GetClockFrequency(CLKTYPE_PCLK1);
   UINT uiCR1Value = astTheI2CDevices[eController_].pstRegisters->CR1;
   UINT uiCR2Value = astTheI2CDevices[eController_].pstRegisters->CR2;
   UINT uiCCRValue = astTheI2CDevices[eController_].pstRegisters->CCR;
   UINT uiOAR1Value = astTheI2CDevices[eController_].pstRegisters->OAR1;
   UINT uiTRISEValue = 0;

   // TODO: Support 10-bit addresses and dual addresses.
   uiOAR1Value |= pstConfiguration_->ucAddress << OAR1_ADD_7_1_OFFSET;

   if(pstConfiguration_->eAckMode == I2CACK_ENABLE)
   {
      uiCR1Value |= CR1_ACK;
   }
   else
   {
      uiCR1Value &= ~CR1_ACK;
   }

   uiCR2Value |= (CR2_FREQ & HSI_RC_CLK_FREQ_MHZ);

   switch(pstConfiguration_->eClockSpeed)
   {
      case I2CCLK_SM_100KHZ:
      {
         uiTRISEValue = (uiPCLK1Frequency/SEC_TO_MSEC) + 1;
         // For Standard Mode:
         // T_high = T_low = CCR * T_PCLK1
         // T_high = (1/100kHz)/2 = 5us
         // T_PCLK1 = (1/16MHz) = 0.0625us
         // 5us/0.0625us = 80
         // CCR = 80
         uiCCRValue |= (CCR_CCR & ((uiPCLK1Frequency/I2C_FREQ_100KHZ)));
         uiCCRValue &= ~CCR_FS;
         break;
      }
      case I2CCLK_FM_200KHZ:
      {

         uiTRISEValue = ((uiPCLK1Frequency * 300)/SEC_TO_NSEC) + 1;

         if(pstConfiguration_->eDutyCycle == I2CDUTY_2)
         {
            // For Fast Mode and Duty Cycle 2:1:
            // T_high = CCR * T_PCLK1
            // T_low = 2 * CCR * T_PCLK1
            // T_high + T_low = 3 * CCR * T_PCLK1
            // T_high + T_low = (1/200kHz) = 5us
            // T_PCLK1 = (1/16MHz) = 0.0625us
            // 5us/0.0625us = 3 * CCR = 80 = 3 * 26
            // CCR = 26
            uiCCRValue |= (CCR_CCR & (((uiPCLK1Frequency/I2C_FREQ_200KHZ)/3)));
            uiCCRValue |= CCR_FS;
            uiCCRValue &= ~CCR_DUTY;
         }
         else if(pstConfiguration_->eDutyCycle == I2CDUTY_16_9)
         {
            // For Fast Mode and Duty Cycle 16:9:
            // T_high = 9 * CCR * T_PCLK1
            // T_low = 16 * CCR * T_PCLK1
            // T_high + T_low = 25 * CCR * T_PCLK1
            // T_high + T_low = (1/200kHz) = 5us
            // T_PCLK1 = (1/16MHz) = 0.0625us
            // 5us/0.0625us = 25 * CCR = calc = 25 * 3
            // CCR = 3
            uiCCRValue |= (CCR_CCR & (((uiPCLK1Frequency/I2C_FREQ_200KHZ)/25)));
            uiCCRValue |= CCR_FS;
            uiCCRValue &= ~CCR_DUTY;

         }
         uiCCRValue |= CCR_FS;
         uiCCRValue |= (CCR_CCR & pstConfiguration_->eClockSpeed);
         break;
      }
      default:
      {
         return FALSE;
      }
   }

   astTheI2CDevices[eController_].pstRegisters->CR1 = uiCR1Value;
   astTheI2CDevices[eController_].pstRegisters->CR2 = uiCR2Value;
   astTheI2CDevices[eController_].pstRegisters->CCR = uiCCRValue;
   astTheI2CDevices[eController_].pstRegisters->OAR1 = uiOAR1Value;
   astTheI2CDevices[eController_].pstRegisters->TRISE = uiTRISEValue;

   memcpy(&(astTheI2CDevices[eController_].stConfiguration), pstConfiguration_, sizeof(I2CConfigurationStruct));

   return TRUE;
}

//------------------------------------------------------------------------------
I2CConfigurationStruct*
I2C_GetConfig(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return NULL;
   }

   return &(astTheI2CDevices[eController_].stConfiguration);
}

//------------------------------------------------------------------------------
BOOL
I2C_WriteData(
   I2CControllerEnum eController_,
   I2CModeEnum eMode_,
   UCHAR ucAddress_,
   UCHAR* pucData_,
   UINT uiLength_)
{
   if((astTheI2CDevices[eController_].pstRegisters == NULL) ||
      (pucData_ == NULL))
   {
      return FALSE;
   }

   if(eMode_ == I2CMODE_MASTER)
   {
      // Generate the START condition
      astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_START;

      // Ensure the START condition has been sent
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_SB));

      // Send the slave address
      UCHAR ucSendAddr = (ucAddress_ << 1) | I2CTRANSFER_WRITE;
      astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

      // Ensure the address has been sent and clear the bit
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR));
      // UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
      // uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;
      astTheI2CDevices[eController_].pstRegisters->SR1;
      astTheI2CDevices[eController_].pstRegisters->SR2;

      // Write data
      while(uiLength_)
      {
         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_TXE));

         astTheI2CDevices[eController_].pstRegisters->DR = *pucData_;

         pucData_++;
         uiLength_--;
      }

      // Check that byte transfer is complete
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_TXE));
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_BTF));

      // Generate the STOP condition
      astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_STOP;

      return TRUE;
   }

   return FALSE;
}

//------------------------------------------------------------------------------
BOOL
I2C_ReadData(
   I2CControllerEnum eController_,
   I2CModeEnum eMode_,
   UCHAR ucAddress_,
   UCHAR* pucCommand_,
   UINT uiCommandLength_,
   UCHAR* pucData_,
   UINT uiLength_)
{
   if((astTheI2CDevices[eController_].pstRegisters == NULL) ||
      (pucData_ == NULL))
   {
      return FALSE;
   }

   if(eMode_ == I2CMODE_MASTER)
   {
      // If a command is required to perform a read from an I2C slave,
      // this block of code will run and force a repeated START condition
      // after the command is sent.
      if(pucCommand_ != NULL)
      {
         // Generate the START condition
         astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_START;

         // Ensure the START condition has been sent
         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_SB));

         // Send the slave address
         UCHAR ucSendAddr = (ucAddress_ << 1) | I2CTRANSFER_WRITE;
         astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

         // Ensure the address has been sent and clear the bit
         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR));
         // UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
         // uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;
         astTheI2CDevices[eController_].pstRegisters->SR1;
         astTheI2CDevices[eController_].pstRegisters->SR2;

         // Write data
         while(uiCommandLength_)
         {
            while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_TXE));

            astTheI2CDevices[eController_].pstRegisters->DR = *pucCommand_;

            pucCommand_++;
            uiCommandLength_--;
         }

         // Check that byte transfer is complete
         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_TXE));
         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_BTF));
      }

      // Generate the START condition
      astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_START;

      // Ensure the START condition has been sent
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_SB));

      // Send the slave address
      UCHAR ucSendAddr = (ucAddress_ << 1) | I2CTRANSFER_READ;
      astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

      // Ensure the address has been sent and clear the bit
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR));
      // UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
      // uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;
      astTheI2CDevices[eController_].pstRegisters->SR1;
      astTheI2CDevices[eController_].pstRegisters->SR2;

      // Enable ACK for received bytes
      astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_ACK;

      // Read data
      while(uiLength_)
      {
         if(uiLength_ == 1)
         {
            astTheI2CDevices[eController_].pstRegisters->CR1 &= ~CR1_ACK;
            astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_STOP;
         }

         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_RXNE));

         *pucData_ = astTheI2CDevices[eController_].pstRegisters->DR;

         pucData_++;
         uiLength_--;
      }

      // Generate the STOP condition
      astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_STOP;

      return TRUE;
   }

   return FALSE;
}

//------------------------------------------------------------------------------
BOOL
I2C_MasterTransfer(
   I2CControllerEnum eController_,
   I2CTransferTypeEnum eTransferType_,
   UCHAR ucAddress_,
   UCHAR* pucBuffer_,
   UINT uiSize_)
{
   // Verify arguments & callback
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   if(astTheI2CDevices[eController_].eTransferState == I2CSTATE_IDLE)
   {
      // Set the buffers
      astTheI2CDevices[eController_].stBuffers.pucDataBuffer = pucBuffer_;
      astTheI2CDevices[eController_].stBuffers.uiDataBufferSize = uiSize_;
      astTheI2CDevices[eController_].stBuffers.uiDataBytes = 0;

      astTheI2CDevices[eController_].stBuffers.eTransferType = eTransferType_;
      astTheI2CDevices[eController_].stBuffers.ucAddress = ucAddress_;

      // Enable the buffer interrupt and event interrupt
      astTheI2CDevices[eController_].pstRegisters->CR2 |= CR2_ITBUFEN;
      astTheI2CDevices[eController_].pstRegisters->CR2 |= CR2_ITEVTEN;

      // Send the start condition
      astTheI2CDevices[eController_].eTransferState = I2CSTATE_BEGIN;
      astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_START;

      return TRUE;
   }

   return FALSE;
}

//------------------------------------------------------------------------------
I2CTransferStateEnum
I2C_GetState(
   I2CControllerEnum eController_)
{
   return astTheI2CDevices[eController_].eTransferState;
}

//------------------------------------------------------------------------------
BOOL
I2C_ConfigureAsInterrupt(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   IRQVectorEnum eIRQVector = IRQ_VECTOR_MAX;
   switch(eController_)
   {
      case I2C1:
      {
         eIRQVector = IRQ_VECTOR_I2C1_EV;
         break;
      }
      case I2C2:
      {
         eIRQVector = IRQ_VECTOR_I2C2_EV;
         break;
      }
      case I2C3:
      default:
         return FALSE;
   }

   astTheI2CDevices[eController_].eTransferState = I2CSTATE_IDLE;

   return NVIC_ConfigureInterrupt(eIRQVector, IRQ_PRIORITY_0, IRQ_ENABLE);
}
