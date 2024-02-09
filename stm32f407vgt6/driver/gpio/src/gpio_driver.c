// Includes ---------------------------------------------------------------------------------------
#include "device/gpio/gpio.h"
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static GPIORegistersStruct* apstTheGPIOControllers[GPIO_MAX] = {NULL};
static BOOL abGPIOInitialized[GPIO_MAX] = {FALSE};

// Functions --------------------------------------------------------------------------------------
BOOL GPIO_Initialize(
   GPIOControllerEnum eGPIOController_)
{
   if(abGPIOInitialized[eGPIOController_])
   {
      STM32F407VGT6_PeriperalEnum eSTM32Peripheral = INVALID;
      switch(eGPIOController_)
      {
         case GPIO_GPIOA:
            eSTM32Peripheral = GPIOA;
            break;
         case GPIO_GPIOB:
            eSTM32Peripheral = GPIOB;
            break;
         case GPIO_GPIOC:
            eSTM32Peripheral = GPIOC;
            break;
         case GPIO_GPIOD:
            eSTM32Peripheral = GPIOD;
            break;
         case GPIO_GPIOE:
            eSTM32Peripheral = GPIOE;
            break;
         case GPIO_GPIOF:
            eSTM32Peripheral = GPIOF;
            break;
         case GPIO_GPIOG:
            eSTM32Peripheral = GPIOG;
            break;
         case GPIO_GPIOH:
            eSTM32Peripheral = GPIOH;
            break;
         case GPIO_GPIOI:
            eSTM32Peripheral = GPIOI;
            break;
         default:
            return FALSE;
      }

      if(!RCC_EnablePeripheralClock(eSTM32Peripheral))
      {
         (void)RCC_ResetPeripheralClock(eSTM32Peripheral);
         return FALSE;
      }

      apstTheGPIOControllers[eGPIOController_] = GetGPIOController(eGPIOController_);
      if(apstTheGPIOControllers[eGPIOController_] == NULL)
      {
         return FALSE;
      }

      abGPIOInitialized[eGPIOController_] = TRUE;
   }
   return TRUE;
}
