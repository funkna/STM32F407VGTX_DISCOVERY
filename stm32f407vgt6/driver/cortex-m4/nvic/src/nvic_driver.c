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
   UCHAR ucIRQNumber_,
   UCHAR ucIRQPriority_,
   IRQConfigActionEnum eAction_)
{
   BOOL bSuccess = FALSE;
   if((pstTheNVICController != NULL) ||
      (ucIRQNumber_ > MAX_IRQ_NUMBER) ||
      (ucIRQPriority_ > MAX_IRQ_PRIORITY))

   {
      if(eAction_ == IRQ_ENABLE)
      {
         pstTheNVICController->NVIC_ISER[(ucIRQNumber_ / 32)] |= (1UL << (ucIRQNumber_ % 32));
         // pstTheNVICController->NVIC_IPR[(ucIRQNumber_ / 4)] |= (ucIRQPriority_ << (((ucIRQNumber_ % 4) * 8) + (8 - IRQ_PRIORITY_BITS)));
         bSuccess = TRUE;
      }

      if(eAction_ == IRQ_CLEAR)
      {
         pstTheNVICController->NVIC_ICER[(ucIRQNumber_ / 32)] &= ~(1UL << (ucIRQNumber_ % 32));
         // pstTheNVICController->NVIC_IPR[(ucIRQNumber_ / 4)] &= ~(0xFF << (((ucIRQNumber_ % 4) * 8) + (8 - IRQ_PRIORITY_BITS)));
         bSuccess = TRUE;
      }
   }
   return bSuccess;
}