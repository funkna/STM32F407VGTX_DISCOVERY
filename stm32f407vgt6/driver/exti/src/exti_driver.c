// Includes ---------------------------------------------------------------------------------------
#include "device/exti/exti.h"
#include "driver/exti/exti_driver.h"
#include "driver/rcc/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static EXTIRegistersStruct* pstTheEXTIController = NULL;

// Functions --------------------------------------------------------------------------------------
BOOL EXTI_Initialize()
{
   if(pstTheEXTIController == NULL)
   {
      pstTheEXTIController = GetEXTIController();
   }
   return TRUE;
}

//--------------------------------------------------------------
BOOL EXTI_EnableInterrupt(
   GPIOControllerEnum eController_,
   GPIOPinEnum ePin_,
   EXTIModeEnum eMode_)
{
   BOOL bSuccess = FALSE;
   if(pstTheEXTIController != NULL)
   {
      bSuccess = TRUE;
      switch(eMode_)
      {
         case EXTI_TRIGGER_RISE:
            pstTheEXTIController->IMR |= (1UL << ePin_);
            pstTheEXTIController->RTSR |= (1UL << ePin_);
            pstTheEXTIController->FTSR &= ~(1UL << ePin_);
            break;
         case EXTI_TRIGGER_FALL:
            pstTheEXTIController->IMR |= (1UL << ePin_);
            pstTheEXTIController->RTSR &= ~(1UL << ePin_);
            pstTheEXTIController->FTSR |= (1UL << ePin_);
            break;
         case EXTI_TRIGGER_BOTH:
            pstTheEXTIController->IMR |= (1UL << ePin_);
            pstTheEXTIController->RTSR |= (1UL << ePin_);
            pstTheEXTIController->FTSR |= (1UL << ePin_);
            break;
         case EXTI_TRIGGER_NONE:
         default: // Fall-through
            pstTheEXTIController->IMR &= ~(1UL << ePin_);
            pstTheEXTIController->RTSR &= ~(1UL << ePin_);
            pstTheEXTIController->FTSR &= ~(1UL << ePin_);
            break;
      }
   }
   return bSuccess;
}

//--------------------------------------------------------------
BOOL EXTI_DisableInterrupt(
   GPIOControllerEnum eController_,
   GPIOPinEnum ePin_)
{
   return EXTI_EnableInterrupt(eController_, ePin_, EXTI_TRIGGER_NONE);
}