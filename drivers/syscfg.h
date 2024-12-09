//------------------------------------------------------------------------------
//! \file syscfg.h
//! \brief Reset and Clock Control driver.
//! \ref docs\stm32f407_reference_manual.pdf section 9.
//------------------------------------------------------------------------------
#ifndef __SYSCFG_H
#define __SYSCFG_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define NUM_SYSCFG_EXTICR   (4)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

// -------------------------------------------------------------
//! \brief SYSCFG Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT MEMRMP;
   UINT PMC;
   UINT EXTICR[NUM_SYSCFG_EXTICR];
   UINT RESERVED[2];
   UINT CMPCR;
} SYSCFGRegistersStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
void SYSCFG_Initialize();
void SYSCFG_Reset();
BOOL SYSCFG_ConfigureEXTI(GPIOPortEnum ePort_, GPIOPinEnum ePin_);

#endif // __SYSCFG_H
