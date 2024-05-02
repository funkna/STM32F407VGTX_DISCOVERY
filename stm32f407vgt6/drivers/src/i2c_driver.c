// Includes ---------------------------------------------------------------------------------------
#include "constants.h"
#include "devices/i2c.h"
#include "drivers/gpio_driver.h"
#include "drivers/rcc_driver.h"
#include "drivers/i2c_driver.h"

// Defines ----------------------------------------------------------------------------------------
#define I2C_FREQ_100KHZ (100000)
#define I2C_FREQ_200KHZ (200000)
#define I2C_RWBIT_WRITE (0)
#define I2C_RWBIT_READ  (1)


// Typedefs ---------------------------------------------------------------------------------------
typedef struct
{
   I2CRegistersStruct* pstRegisters;
   I2CConfigurationStruct stConfiguration;
} I2CDeviceStruct;

// Statics, Externs & Globals ---------------------------------------------------------------------
GPIOConfigurationStruct stTheI2CPinConfig = {
   GPIOMODE_ALT_FUNC,
   GPIOTYPE_OPENDRAIN,
   GPIOSPEED_HI,
   GPIOPUPD_PU,
   GPIOALTFUNC_AF4
};
static I2CDeviceStruct astTheI2CDevices[I2C_MAX] = {NULL};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum I2CEnumToSTM32Enum(
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

// -------------------------------------------------------------
BOOL I2C_Initialize(
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

// -------------------------------------------------------------
BOOL I2C_Reset(
   I2CControllerEnum eController_)
{
   return RCC_ResetPeripheralClock(I2CEnumToSTM32Enum(eController_));
}

// -------------------------------------------------------------
BOOL I2C_Enable(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheI2CDevices[eController_].pstRegisters->CR1 |= CR1_PE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL I2C_Disable(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheI2CDevices[eController_].pstRegisters->CR1 &= ~CR1_PE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL I2C_SetConfig(
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
         uiTRISEValue = (uiPCLK1Frequency/MSEC_TO_SEC) + 1;
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

         uiTRISEValue = ((uiPCLK1Frequency * 300)/NSEC_TO_SEC) + 1;

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

// -------------------------------------------------------------
I2CConfigurationStruct* I2C_GetConfig(
   I2CControllerEnum eController_)
{
   if(astTheI2CDevices[eController_].pstRegisters == NULL)
   {
      return NULL;
   }

   return &(astTheI2CDevices[eController_].stConfiguration);
}

// -------------------------------------------------------------
BOOL I2C_WriteData(
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
      UCHAR ucSendAddr = (ucAddress_ << 1) | I2C_RWBIT_WRITE;
      astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

      // Ensure the address has been sent and clear the bit
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR));
      UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
      uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;

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

// -------------------------------------------------------------
BOOL I2C_ReadData(
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
         UCHAR ucSendAddr = (ucAddress_ << 1) | I2C_RWBIT_WRITE;
         astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

         // Ensure the address has been sent and clear the bit
         while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR));
         UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
         uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;

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
      UCHAR ucSendAddr = (ucAddress_ << 1) | I2C_RWBIT_READ;
      astTheI2CDevices[eController_].pstRegisters->DR = ucSendAddr;

      // Ensure the address has been sent and clear the bit
      while(!(astTheI2CDevices[eController_].pstRegisters->SR1 & SR1_ADDR));
      UINT uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR1;
      uiDummyRead = astTheI2CDevices[eController_].pstRegisters->SR2;

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

