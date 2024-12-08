//------------------------------------------------------------------------------
//! \file systick.h
//! \brief System Tick timer driver
//! \ref docs\arm-cortex-m4_generic_user_guide.pdf section 4.5.
//------------------------------------------------------------------------------
#ifndef __SYSTICK_H
#define __SYSTICK_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define TICKS_PER_MSEC (2000)
#define ROLLOVER_TICKS (0xFFFFFF)

//------------------------------------------------------------------------------
//! \brief SYSTICK Controller Register Bitmasks
//------------------------------------------------------------------------------
#define CTRL_ENABLE              (0x01UL << 0)  // Counter enable
#define CTRL_TICKINT             (0x01UL << 1)  // Systick exception request enable
#define CTRL_CLKSOURCE           (0x01UL << 2)  // Clock source selection
#define CTRL_COUNTFLAG           (0x01UL << 16) // Count flag
#define LOAD_RELOAD_MASK         (0x00FFFFFFUL)
#define VAL_CURRENT_MASK         (0x00FFFFFFUL)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief SYSTICK Controller Register Structure
//------------------------------------------------------------------------------
typedef volatile struct
{
   UINT CTRL;
   UINT LOAD;
   UINT VAL;
   UINT CALIB;
} SYSTICKRegistersStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
void SYSTICK_Initialize();
void SYSTICK_ClearTicks();
UINT SYSTICK_GetTicks();

#endif // __SYSTICK_H
