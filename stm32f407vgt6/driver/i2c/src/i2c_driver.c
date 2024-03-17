// Includes ---------------------------------------------------------------------------------------
#include "device/i2c/i2c.h"
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"
#include "driver/i2c/i2c_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static I2CRegistersStruct* apstTheI2CControllers[I2C_MAX] = {NULL};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum I2CEnumToSTM32Enum(
   I2CControllerEnum eController_)
{
   switch(eController_)
   {
      case I2C_I2C1:
         return I2C1;
      case I2C_I2C2:
         return I2C2;
      case I2C_I2C3:
         return I2C3;
      default:
         return INVALID;
   }
}

// -------------------------------------------------------------
BOOL I2C_Initialize(
   I2CControllerEnum eController_)
{
   if(apstTheI2CControllers[eController_] == NULL)
   {
      STM32F407VGT6_PeriperalEnum ePeripheral = I2CEnumToSTM32Enum(eController_);
      apstTheI2CControllers[eController_] = GetI2CController(eController_);
      if((apstTheI2CControllers[eController_] == NULL) ||
         (!RCC_EnablePeripheralClock(ePeripheral)))
      {
         (void)I2C_Deinitialize(eController_);
         return FALSE;
      }

      if(eController_ == I2C_I2C1)
      {
         GPIOPinConfigurationStruct stI2CConfig = {GPIOMODE_ALT_FUNC, GPIOTYPE_OPENDRAIN, GPIOSPEED_VHI, GPIOPUPD_PD, GPIOALTFUNC_AF4};
         GPIO_SetConfig(GPIO_GPIOB, GPIO_PIN_6, &stI2CConfig); // SCL
         GPIO_SetConfig(GPIO_GPIOB, GPIO_PIN_7, &stI2CConfig); // SDA
      }
      else
      {
         return FALSE;
      }
   }
   return TRUE;
}

// -------------------------------------------------------------
BOOL I2C_Deinitialize(
   I2CControllerEnum eController_)
{
   STM32F407VGT6_PeriperalEnum ePeripheral = I2CEnumToSTM32Enum(eController_);
   apstTheI2CControllers[eController_] = NULL;
   return RCC_ResetPeripheralClock(ePeripheral);
}
