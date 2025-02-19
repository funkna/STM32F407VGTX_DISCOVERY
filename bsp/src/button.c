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
#include "systick.h"
#include "time.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define BUTTON_PORT              (GPIO_PORT_A)
#define BUTTON_PIN_0             (GPIO_PIN_0)
#define BUTTON_IRQ_VECTOR_0      (IRQ_VECTOR_EXTI0)
#define BUTTON_TO_GPIO(x)        ((GPIOPinEnum)(x) + BUTTON_PIN_0)
#define BUTTON_DEBOUNCE_TIME_MS  (75) // Magic number

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief Button states match to GPIO states
//------------------------------------------------------------------------------
typedef enum
{
   BUTTON_RELEASED = GPIO_LO,
   BUTTON_PRESSED = GPIO_HI
} ButtonStateEnum;

//------------------------------------------------------------------------------
//! \brief Button state informatio
//------------------------------------------------------------------------------
typedef struct
{
   ButtonStateEnum eCurrentState;
   ButtonStateEnum eQueuedState;
   UINT uiDebounceStartTicks;
   BOOL bIsDebouncing;
   BOOL bWasPressed;
} ButtonStateInfoStruct;

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static const GPIOConfigurationStruct stTheButtonGPIOConfig = {
   GPIOMODE_INPUT,
   GPIOTYPE_OPENDRAIN,
   GPIOSPEED_VHI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF0
};

static ButtonStateInfoStruct astTheButtonStates[BUTTON_MAX];

//------------------------------------------------------------------------------
//! \brief IRQ Handlers
//------------------------------------------------------------------------------
static void
Button_InterruptHandler(
   ButtonTypeEnum eButtonType_)
{
   EXTI_ClearPendingInterrupt(BUTTON_TO_GPIO(eButtonType_));

   if(astTheButtonStates[eButtonType_].bIsDebouncing)
   {
      return;
   }

   ButtonStateEnum eButtonState = BUTTON_RELEASED;
   if(GPIO_ReadPin(BUTTON_PORT, BUTTON_TO_GPIO(eButtonType_), (GPIOStateEnum*)(&eButtonState)) &&
   (eButtonState == BUTTON_PRESSED))
   {
      astTheButtonStates[eButtonType_].bWasPressed = TRUE;
   }

   astTheButtonStates[eButtonType_].eQueuedState = eButtonState;
   astTheButtonStates[eButtonType_].bIsDebouncing = TRUE;
   astTheButtonStates[eButtonType_].uiDebounceStartTicks = SYSTICK_GetTicks();
}

//------------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
   Button_InterruptHandler(BUTTON_0);
}

//------------------------------------------------------------------------------
BOOL
Button_Initialize()
{
   if(!GPIO_Initialize(BUTTON_PORT)) return FALSE;
   if(!GPIO_SetConfig(BUTTON_PORT, BUTTON_PIN_0, &stTheButtonGPIOConfig)) return FALSE;
   if(!NVIC_ConfigureInterrupt(BUTTON_IRQ_VECTOR_0, IRQ_PRIORITY_0, IRQ_ENABLE)) return FALSE;
   if(!SYSCFG_ConfigureEXTI(BUTTON_PORT, BUTTON_PIN_0)) return FALSE;
   if(!EXTI_EnableInterrupt(BUTTON_PORT, BUTTON_PIN_0, EXTI_TRIGGER_BOTH)) return FALSE;
   return TRUE;
}

//------------------------------------------------------------------------------
BOOL
Button_IsPressed(
   ButtonTypeEnum eButton_)
{
   return (astTheButtonStates[eButton_].eCurrentState == BUTTON_PRESSED);
}

//------------------------------------------------------------------------------
BOOL
Button_IsReleased(
   ButtonTypeEnum eButton_)
{
   return (astTheButtonStates[eButton_].eCurrentState == BUTTON_RELEASED);
}

//------------------------------------------------------------------------------
BOOL
Button_WasPressed(
   ButtonTypeEnum eButton_)
{
   return astTheButtonStates[eButton_].bWasPressed;
}

//------------------------------------------------------------------------------
void
Button_Acknowledge(
   ButtonTypeEnum eButton_)
{
   astTheButtonStates[eButton_].bWasPressed = FALSE;
}

//------------------------------------------------------------------------------
void
Button_RunTask()
{
   for(UINT uiIndex = 0; uiIndex < BUTTON_MAX; uiIndex++)
   {
      if((astTheButtonStates[uiIndex].bIsDebouncing) &&
         (TickDeltaToMS(astTheButtonStates[uiIndex].uiDebounceStartTicks, SYSTICK_GetTicks()) > BUTTON_DEBOUNCE_TIME_MS))
      {
         astTheButtonStates[uiIndex].bIsDebouncing = FALSE;
         astTheButtonStates[uiIndex].uiDebounceStartTicks = 0UL;
      }

      if((astTheButtonStates[uiIndex].eQueuedState != astTheButtonStates[uiIndex].eCurrentState) &&
         (!astTheButtonStates[uiIndex].bIsDebouncing))
      {
         astTheButtonStates[uiIndex].eCurrentState = astTheButtonStates[uiIndex].eQueuedState;
      }
   }
}
