// Redundancy Prevention --------------------------------------------------------------------------
#ifndef NVIC_H_
#define NVIC_H_

// Includes ---------------------------------------------------------------------------------------
#include "../../stm32f407vgt6.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// NVIC Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT NVIC_ISER[8];
   UINT NVIC_ICER[8];
   UINT NVIC_ISPR[8];
   UINT NVIC_ICPR[8];
   UINT NVIC_IABR[8];
   UINT NVIC_IPR[60];
   UINT NVIC_STIR;
} NVICRegistersStruct;

// Functions --------------------------------------------------------------------------------------
NVICRegistersStruct* GetNVICController()
{
   return (NVICRegistersStruct*)PERIPHERAL_ADDRESS_NVIC;
}

#endif // NVIC_H_
