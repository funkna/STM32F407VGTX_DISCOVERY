// Includes ---------------------------------------------------------------------------------------
#include "device/cortex-m4/nvic/nvic.h"
#include "driver/cortex-m4/nvic/nvic_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static NVICRegistersStruct* pstTheNVICController = NULL;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
BOOL NVIC_Initialize()
{
   if(pstTheNVICController == NULL)
   {
      pstTheNVICController = GetNVICController();
   }
   return TRUE;
}

// -------------------------------------------------------------
BOOL NVIC_ConfigureInterrupt(
   IRQVectorEnum eIRQNumber_,
   IRQPriorityEnum eIRQPriority_,
   IRQConfigActionEnum eAction_)
{
   BOOL bSuccess = FALSE;
   if(pstTheNVICController != NULL)
   {
      if(eAction_ == IRQ_ENABLE)
      {
         pstTheNVICController->NVIC_ISER[(eIRQNumber_ / 32)] |= (1UL << (eIRQNumber_ % 32));
         pstTheNVICController->NVIC_IPR[(eIRQNumber_ / 4)] |= (eIRQPriority_ << (((eIRQNumber_ % 4) * 8) + (8 - IRQ_PRIORITY_BITS)));
         bSuccess = TRUE;
      }

      if(eAction_ == IRQ_CLEAR)
      {
         pstTheNVICController->NVIC_ICER[(eIRQNumber_ / 32)] &= ~(1UL << (eIRQNumber_ % 32));
         pstTheNVICController->NVIC_IPR[(eIRQNumber_ / 4)] &= ~(((1UL << IRQ_PRIORITY_BITS) - 1) << (((eIRQNumber_ % 4) * 8) + (8 - IRQ_PRIORITY_BITS)));
         bSuccess = TRUE;
      }
   }
   return bSuccess;
}
