// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SYSTICK_DRIVER_H_
#define SYSTICK_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
#define TICKS_PER_MSEC (2000)
#define ROLLOVER_TICKS (0xFFFFFF)

// Functions --------------------------------------------------------------------------------------
BOOL SYSTICK_Initialize();

// -------------------------------------------------------------
// Get the current system ticks from the Cortex-M4
// -------------------------------------------------------------
UINT SYSTICK_GetTicks();

#endif // SYSTICK_DRIVER_H_
