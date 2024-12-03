// Redundancy Prevention --------------------------------------------------------------------------
#ifndef NVIC_H_
#define NVIC_H_

// Includes ---------------------------------------------------------------------------------------
#include "cortex_m4.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
#define NUM_IRQ_CONFIG_REGISTERS    (8)
#define NUM_IRQ_PRIORITY_REGISTERS  (60)

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// NVIC Controller Register Structure
// -------------------------------------------------------------
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

// Functions --------------------------------------------------------------------------------------
NVICRegistersStruct* GetNVICController()
{
   return (NVICRegistersStruct*)PERIPHERAL_ADDRESS_NVIC;
}

#endif // NVIC_H_
