// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6/exti.h"
#include "drivers/exti_driver.h"
#include "drivers/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static EXTIRegistersStruct* pstTheEXTIController = NULL;

// Functions --------------------------------------------------------------------------------------
BOOL EXTI_Initialize()
{
   pstTheEXTIController = GetEXTIController();
   return (pstTheEXTIController != NULL);
}

//--------------------------------------------------------------
BOOL EXTI_EnableInterrupt(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_,
   EXTITriggerEnum eMode_)
{
   if(pstTheEXTIController == NULL)
   {
      return FALSE;
   }

   switch(eMode_)
   {
      case EXTI_TRIGGER_RISE:
      {
         pstTheEXTIController->IMR |= (1UL << ePin_);
         pstTheEXTIController->RTSR |= (1UL << ePin_);
         pstTheEXTIController->FTSR &= ~(1UL << ePin_);
         break;
      }
      case EXTI_TRIGGER_FALL:
      {
         pstTheEXTIController->IMR |= (1UL << ePin_);
         pstTheEXTIController->RTSR &= ~(1UL << ePin_);
         pstTheEXTIController->FTSR |= (1UL << ePin_);
         break;
      }
      case EXTI_TRIGGER_BOTH:
      {
         pstTheEXTIController->IMR |= (1UL << ePin_);
         pstTheEXTIController->RTSR |= (1UL << ePin_);
         pstTheEXTIController->FTSR |= (1UL << ePin_);
         break;
      }
      case EXTI_TRIGGER_NONE:
      default: // Fall-through
      {
         pstTheEXTIController->IMR &= ~(1UL << ePin_);
         pstTheEXTIController->RTSR &= ~(1UL << ePin_);
         pstTheEXTIController->FTSR &= ~(1UL << ePin_);
         break;
      }
   }

   return TRUE;
}

//--------------------------------------------------------------
BOOL EXTI_DisableInterrupt(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   return EXTI_EnableInterrupt(ePort_, ePin_, EXTI_TRIGGER_NONE);
}

//--------------------------------------------------------------
BOOL EXTI_ClearPendingInterrupt(
   GPIOPinEnum ePin_)
{
   if(pstTheEXTIController == NULL)
   {
      return FALSE;
   }

   pstTheEXTIController->PR |= (1UL << ePin_);
   return TRUE;
}
