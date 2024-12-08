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
void
EXTI_EnableInterrupt(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_,
   EXTITriggerEnum eMode_)
{
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
}

//--------------------------------------------------------------
void
EXTI_DisableInterrupt(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   EXTI_EnableInterrupt(ePort_, ePin_, EXTI_TRIGGER_NONE);
}

//--------------------------------------------------------------
void
EXTI_ClearPendingInterrupt(
   GPIOPinEnum ePin_)
{
   pstTheEXTIController->PR |= (1UL << ePin_);
}
