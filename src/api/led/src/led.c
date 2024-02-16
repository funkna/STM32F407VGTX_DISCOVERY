// Includes ---------------------------------------------------------------------------------------
#include "led/led.h"
#include "driver/gpio/gpio_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static GPIOControllerEnum eTheLEDGPIOPort = GPIO_GPIOD;
static const GPIOPinConfigurationStruct stTheLEDGPIOConfig = {MODE_GP_OUTPUT, OUTPUT_PUSHPULL, SPEED_MED, PUPD_PD};

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
   bSuccess &= GPIO_SetConfig(eTheLEDGPIOPort, GetGPIOFromLED(LED_GREEN), &stTheLEDGPIOConfig);
   bSuccess &= GPIO_SetConfig(eTheLEDGPIOPort, GetGPIOFromLED(LED_ORANGE), &stTheLEDGPIOConfig);
   bSuccess &= GPIO_SetConfig(eTheLEDGPIOPort, GetGPIOFromLED(LED_RED), &stTheLEDGPIOConfig);
   bSuccess &= GPIO_SetConfig(eTheLEDGPIOPort, GetGPIOFromLED(LED_BLUE), &stTheLEDGPIOConfig);
   return bSuccess;
}

// -------------------------------------------------------------
void LED_On(
   LEDTypeEnum eLED_)
{
   GPIO_WritePin(eTheLEDGPIOPort, GetGPIOFromLED(eLED_), GPIO_HI);
}

// -------------------------------------------------------------
void LED_Off(
   LEDTypeEnum eLED_)
{
   GPIO_WritePin(eTheLEDGPIOPort, GetGPIOFromLED(eLED_), GPIO_LO);
}

// -------------------------------------------------------------
void LED_Toggle(
   LEDTypeEnum eLED_)
{
   GPIO_TogglePin(eTheLEDGPIOPort, GetGPIOFromLED(eLED_));
}
