//------------------------------------------------------------------------------
//! \file nvic.h
//! \brief Nested Vectored Interrupt Controller driver.
//! \ref docs\arm-cortex-m4_generic_user_guide.pdf section 4.3.
//------------------------------------------------------------------------------
#ifndef __NVIC_H
#define __NVIC_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "cortex_m4.h"
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define NUM_IRQ_CONFIG_REGISTERS    (8)
#define NUM_IRQ_PRIORITY_REGISTERS  (60)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief NVIC Controller Register Structure
//------------------------------------------------------------------------------
typedef volatile struct
{
   UINT NVIC_ISER[NUM_IRQ_CONFIG_REGISTERS];
   UINT NVIC_ICER[NUM_IRQ_CONFIG_REGISTERS];
   UINT NVIC_ISPR[NUM_IRQ_CONFIG_REGISTERS];
   UINT NVIC_ICPR[NUM_IRQ_CONFIG_REGISTERS];
   UINT NVIC_IABR[NUM_IRQ_CONFIG_REGISTERS];
   UINT NVIC_IPR[NUM_IRQ_PRIORITY_REGISTERS];
   UINT NVIC_STIR;
} NVICRegistersStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
void NVIC_Initialize();
BOOL NVIC_ConfigureInterrupt(IRQVectorEnum eIRQNumber_, IRQPriorityEnum eIRQPriority_, IRQConfigActionEnum eAction_);

#endif // __NVIC_H
