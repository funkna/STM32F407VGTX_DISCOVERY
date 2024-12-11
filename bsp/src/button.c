//------------------------------------------------------------------------------
//! \file button.c
//! \brief On-board button functionality.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "button.h"
#include "nvic.h"
#include "exti.h"
#include "gpio.h"
#include "syscfg.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static void (*pfButtonInterruptCallback)(void) = NULL;

static const GPIOConfigurationStruct stTheButtonGPIOConfig = {
   GPIOMODE_INPUT,
   GPIOTYPE_OPENDRAIN,
   GPIOSPEED_VHI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF0
};


//------------------------------------------------------------------------------
//! \brief IRQ Handler
//------------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
   EXTI_ClearPendingInterrupt(GPIO_PIN_0);

   if(pfButtonInterruptCallback != NULL)
   {
      pfButtonInterruptCallback();
   }
}

//------------------------------------------------------------------------------
BOOL
Button_Initialize()
{
   return GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_0, &stTheButtonGPIOConfig);
}

//------------------------------------------------------------------------------
BOOL
Button_ConfigureAsInterrupt(
   ButtonActionEnum eAction_,
   void (*fpCallback_)(void))
{
   EXTITriggerEnum eEXTITrigger = EXTI_TRIGGER_NONE;
   switch(eAction_)
   {
      case BUTTON_PRESS:
         eEXTITrigger = EXTI_TRIGGER_RISE;
         break;
      case BUTTON_RELEASE:
         eEXTITrigger = EXTI_TRIGGER_FALL;
         break;
      case BUTTON_BOTH:
         eEXTITrigger = EXTI_TRIGGER_BOTH;
         break;
      case BUTTON_NONE:
      default: // Fall-through
         break;
   }

   if(fpCallback_ != NULL)
   {
      pfButtonInterruptCallback = fpCallback_;
   }

   BOOL bSuccess = TRUE;
   bSuccess |= NVIC_ConfigureInterrupt(IRQ_VECTOR_EXTI0, IRQ_PRIORITY_0, IRQ_ENABLE);
   bSuccess |= SYSCFG_ConfigureEXTI(GPIO_PORT_A, GPIO_PIN_0);
   EXTI_EnableInterrupt(GPIO_PORT_A, GPIO_PIN_0, eEXTITrigger);
   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
Button_IsPressed()
{
   GPIOStateEnum eButtonState = GPIO_LO;
   BOOL bSuccess = GPIO_ReadPin(GPIO_PORT_A, GPIO_PIN_0, &eButtonState);
   return (bSuccess && (GPIO_HI == eButtonState));
}
