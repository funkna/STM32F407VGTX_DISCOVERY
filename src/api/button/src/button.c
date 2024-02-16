// Includes ---------------------------------------------------------------------------------------
#include "button/button.h"
#include "driver/gpio/gpio_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static GPIOControllerEnum eTheButtonGPIOPort = GPIO_GPIOA;
static const GPIOPinConfigurationStruct stTheButtonGPIOConfig = {MODE_INPUT, OUTPUT_OPENDRAIN, SPEED_VHI, PUPD_NONE};

// Functions --------------------------------------------------------------------------------------
static GPIOPinEnum GetGPIOFromButton(
   ButtonTypeEnum eButton_)
{
   switch(eButton_)
   {
      case BUTTON_USER:
         return GPIO_PIN_0;
      default:
         return GPIO_PIN_NONE;
   }
};

BOOL Button_Initialize()
{
   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_SetConfig(eTheButtonGPIOPort, GetGPIOFromButton(BUTTON_USER), &stTheButtonGPIOConfig);
   return bSuccess;
}

BOOL Button_IsPressed(
   ButtonTypeEnum eButton_)
{
   GPIOStateEnum eButtonState = GPIO_LO;
   BOOL bSuccess = GPIO_ReadPin(eTheButtonGPIOPort, GetGPIOFromButton(eButton_), &eButtonState);
   return (bSuccess && (GPIO_HI == eButtonState));
}
