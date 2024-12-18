//------------------------------------------------------------------------------
//! \file nvic.c
//! \brief Nested Vectored Interrupt Controller driver implementation.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "nvic.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define NUM_IRQ_VECTORS_FIELDS_ISER    (32)
#define NUM_IRQ_PRIORITY_FIELDS_IPR    (4)
#define NUM_IRQ_PRIORITY_BITS_TOTAL    (8)
#define NUM_IRQ_PRIORITY_BITS_IN_USE   (4)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static NVICRegistersStruct* pstTheNVICController = NULL;

//------------------------------------------------------------------------------
void NVIC_Initialize()
{
   pstTheNVICController = (NVICRegistersStruct*)PERIPHERAL_ADDRESS_NVIC;
}

// -------------------------------------------------------------
BOOL NVIC_ConfigureInterrupt(
   IRQVectorEnum eIRQNumber_,
   IRQPriorityEnum eIRQPriority_,
   IRQConfigActionEnum eAction_)
{
   UINT uiIxERIndex = (eIRQNumber_ / NUM_IRQ_VECTORS_FIELDS_ISER);
   UINT uiIPRIndex = (eIRQNumber_ / NUM_IRQ_PRIORITY_FIELDS_IPR);
   if((uiIxERIndex < NUM_IRQ_CONFIG_REGISTERS) &&
      (uiIPRIndex < NUM_IRQ_PRIORITY_REGISTERS))
   {
      UINT uiIRQVectorBit = (eIRQNumber_ % NUM_IRQ_VECTORS_FIELDS_ISER);
      UINT uiIRQPriorityBits = ((eIRQNumber_ % NUM_IRQ_PRIORITY_FIELDS_IPR) * NUM_IRQ_PRIORITY_BITS_TOTAL);
      UINT uiUnusedPriorityBits = (NUM_IRQ_PRIORITY_BITS_TOTAL - NUM_IRQ_PRIORITY_BITS_IN_USE);

      if(eAction_ == IRQ_ENABLE)
      {
         pstTheNVICController->NVIC_ISER[uiIxERIndex] |= (1UL << uiIRQVectorBit);
         pstTheNVICController->NVIC_IPR[uiIPRIndex] |= (eIRQPriority_ << (uiIRQPriorityBits + uiUnusedPriorityBits));
      }

      if(eAction_ == IRQ_CLEAR)
      {
         pstTheNVICController->NVIC_ICER[uiIxERIndex] &= ~(1UL << uiIRQVectorBit);
         pstTheNVICController->NVIC_IPR[uiIPRIndex] &= ~(MAX_IRQ_PRIORITY << (uiIRQPriorityBits + uiUnusedPriorityBits));
      }

      return TRUE;
   }

   return FALSE;
}
