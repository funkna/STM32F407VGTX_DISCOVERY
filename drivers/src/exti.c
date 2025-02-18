//------------------------------------------------------------------------------
//! \file exti.c
//! \brief External Interrupt/Event Controller driver implementation.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "exti.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static EXTIRegistersStruct* pstTheEXTIController = NULL;

//------------------------------------------------------------------------------
void
EXTI_Initialize()
{
   pstTheEXTIController = (EXTIRegistersStruct*)PERIPHERAL_ADDRESS_EXTI;
}

//------------------------------------------------------------------------------
BOOL
EXTI_EnableInterrupt(
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
BOOL
EXTI_DisableInterrupt(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   return EXTI_EnableInterrupt(ePort_, ePin_, EXTI_TRIGGER_NONE);
}

//--------------------------------------------------------------
void
EXTI_ClearPendingInterrupt(
   GPIOPinEnum ePin_)
{
   pstTheEXTIController->PR |= (1UL << ePin_);
}
