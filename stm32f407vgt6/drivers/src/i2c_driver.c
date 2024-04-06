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
