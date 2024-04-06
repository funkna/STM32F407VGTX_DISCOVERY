// Redundancy Prevention --------------------------------------------------------------------------
#ifndef NVIC_DRIVER_H_
#define NVIC_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "irq.h"

// Functions --------------------------------------------------------------------------------------
BOOL NVIC_Initialize();

// -------------------------------------------------------------
// Configure an interrupt via the Cortex-M4 NVIC.
// -------------------------------------------------------------
BOOL NVIC_ConfigureInterrupt(
   IRQVectorEnum eIRQNumber_,
   IRQPriorityEnum eIRQPriority_,
   IRQConfigActionEnum eAction_);

#endif // NVIC_DRIVER_H_
