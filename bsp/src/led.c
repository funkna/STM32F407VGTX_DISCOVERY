// Includes ---------------------------------------------------------------------------------------
#include "led.h"
#include "drivers/gpio_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
// Functions --------------------------------------------------------------------------------------
static GPIOPinEnum GetGPIOFromLED(
   LEDTypeEnum eLED_)
{
   switch(eLED_)
   {
      case LED_GREEN:
         return GPIO_PIN_12;
      case LED_ORANGE:
         return GPIO_PIN_13;
      case LED_RED:
         return GPIO_PIN_14;
      case LED_BLUE:
         return GPIO_PIN_15;
      default:
         return GPIO_PIN_NONE;
   }
};

// -------------------------------------------------------------
BOOL LED_Initialize()
{
   BOOL bSuccess = TRUE;
   const GPIOConfigurationStruct stLEDGPIOConfig = {GPIOMODE_GP_OUTPUT, GPIOTYPE_PUSHPULL, GPIOSPEED_MED, GPIOPUPD_PD};
   bSuccess &= GPIO_SetConfig(GPIO_PORT_D, GetGPIOFromLED(LED_GREEN), &stLEDGPIOConfig);
   bSuccess &= GPIO_SetConfig(GPIO_PORT_D, GetGPIOFromLED(LED_ORANGE), &stLEDGPIOConfig);
   bSuccess &= GPIO_SetConfig(GPIO_PORT_D, GetGPIOFromLED(LED_RED), &stLEDGPIOConfig);
   bSuccess &= GPIO_SetConfig(GPIO_PORT_D, GetGPIOFromLED(LED_BLUE), &stLEDGPIOConfig);
   return bSuccess;
}

// -------------------------------------------------------------
void LED_On(
   LEDTypeEnum eLED_)
{
   (void)GPIO_WritePin(GPIO_PORT_D, GetGPIOFromLED(eLED_), GPIO_HI);
}

// -------------------------------------------------------------
void LED_Off(
   LEDTypeEnum eLED_)
{
   (void)GPIO_WritePin(GPIO_PORT_D, GetGPIOFromLED(eLED_), GPIO_LO);
}

// -------------------------------------------------------------
void LED_Toggle(
   LEDTypeEnum eLED_)
{
   (void)GPIO_TogglePin(GPIO_PORT_D, GetGPIOFromLED(eLED_));
}
