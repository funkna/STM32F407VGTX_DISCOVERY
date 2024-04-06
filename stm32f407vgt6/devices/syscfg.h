// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SYSCFG_H_
#define SYSCFG_H_

// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "peripherals.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
#define NUM_SYSCFG_EXTICR   (4)

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// SYSCFG Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT MEMRMP;
   UINT PMC;
   UINT EXTICR[NUM_SYSCFG_EXTICR];
   UINT RESERVED[2];
   UINT CMPCR;
} SYSCFGRegistersStruct;

// Functions --------------------------------------------------------------------------------------
SYSCFGRegistersStruct* GetSYSCFGController()
{
   return (SYSCFGRegistersStruct*)PERIPHERAL_ADDRESS_SYSCFG;
}

#endif // SYSCFG_H_
