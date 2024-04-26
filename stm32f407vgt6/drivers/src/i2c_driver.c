// Includes ---------------------------------------------------------------------------------------
#include "devices/i2c.h"
#include "drivers/gpio_driver.h"
#include "drivers/rcc_driver.h"
#include "drivers/i2c_driver.h"

// Defines ----------------------------------------------------------------------------------------
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
   GPIOPUPD_PD,
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
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_6, &stTheI2CPinConfig); // SCL
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_7, &stTheI2CPinConfig); // SDA
            break;
         }
         case I2C2: // TODO: Fall-through for now
         case I2C3: // TODO: Fall-through for now
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

   UINT uiCR1Value = astTheI2CDevices[eController_].pstRegisters->CR1;
   UINT uiCR2Value = astTheI2CDevices[eController_].pstRegisters->CR2;
   UINT uiCCRValue = astTheI2CDevices[eController_].pstRegisters->CCR;
   UINT uiOAR1Value = astTheI2CDevices[eController_].pstRegisters->OAR1;

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
         // For Standard Mode:
         // T_high = T_low = CCR * T_PCLK1
         // T_high = (1/100kHz)/2 = 5us
         // T_PCLK1 = (1/16MHz) = 0.0625us
         // 5us/0.0625us = 80
         // CCR = 80
         uiCCRValue |= (CCR_CCR & 80);
         uiCCRValue &= ~CCR_FS;
         break;
      }
      case I2CCLK_FM_200KHZ:
      {
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
            uiCCRValue |= (CCR_CCR & 26);
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
            uiCCRValue |= (CCR_CCR & 3);
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


