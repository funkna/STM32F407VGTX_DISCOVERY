//------------------------------------------------------------------------------
//! \file led.c
//! \brief On-board LED funcionality.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "led.h"
#include "gpio.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define LED_PORT        (GPIO_PORT_D)
#define LED_PIN_GREEN   (GPIO_PIN_12)
#define LED_PIN_ORANGE  (GPIO_PIN_13)
#define LED_PIN_RED     (GPIO_PIN_14)
#define LED_PIN_BLUE    (GPIO_PIN_15)
#define LED_TO_GPIO(x)  ((GPIOPinEnum)(x) + LED_PIN_GREEN)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief LED states match to GPIO states
//------------------------------------------------------------------------------
typedef enum
{
   LED_OFF = GPIO_LO,
   LED_ON = GPIO_HI
} LEDStateEnum;

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static const GPIOConfigurationStruct stTheLEDGPIOConfig = {
   GPIOMODE_GP_OUTPUT,
   GPIOTYPE_PUSHPULL,
   GPIOSPEED_MED,
   GPIOPUPD_PD
};

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
BOOL
LED_Initialize()
{
   if(!GPIO_Initialize(LED_PORT)) return FALSE;
   if(!GPIO_SetConfig(LED_PORT, LED_PIN_GREEN, &stTheLEDGPIOConfig)) return FALSE;
   if(!GPIO_SetConfig(LED_PORT, LED_PIN_ORANGE, &stTheLEDGPIOConfig)) return FALSE;
   if(!GPIO_SetConfig(LED_PORT, LED_PIN_RED, &stTheLEDGPIOConfig)) return FALSE;
   if(!GPIO_SetConfig(LED_PORT, LED_PIN_BLUE, &stTheLEDGPIOConfig)) return FALSE;
   return TRUE;
}

//------------------------------------------------------------------------------
void
LED_On(
   LEDTypeEnum eLED_)
{
   (void)GPIO_WritePin(LED_PORT, LED_TO_GPIO(eLED_), LED_ON);
}

//------------------------------------------------------------------------------
void
LED_Off(
   LEDTypeEnum eLED_)
{
   (void)GPIO_WritePin(LED_PORT, LED_TO_GPIO(eLED_), LED_OFF);
}

//------------------------------------------------------------------------------
void
LED_Toggle(
   LEDTypeEnum eLED_)
{
   LEDStateEnum eState = LED_OFF;
   if(GPIO_ReadPin(LED_PORT, LED_TO_GPIO(eLED_), (GPIOStateEnum*)(&eState)))
   {
      (void)GPIO_WritePin(LED_PORT, LED_TO_GPIO(eLED_), ((eState == LED_OFF) ? LED_ON : LED_OFF));
   }
}
