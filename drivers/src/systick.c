//------------------------------------------------------------------------------
//! \file systick.c
//! \brief System Tick timer driver implementation.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "cortex_m4.h"
#include "systick.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static SYSTICKRegistersStruct* pstTheSYSTICKController = NULL;

//------------------------------------------------------------------------------
void
SYSTICK_Initialize()
{
   pstTheSYSTICKController = (SYSTICKRegistersStruct*)PERIPHERAL_ADDRESS_SYSTICK;
   pstTheSYSTICKController->LOAD = LOAD_RELOAD_MASK;
   pstTheSYSTICKController->CTRL |= CTRL_ENABLE;
}

//------------------------------------------------------------------------------
void
SYSTICK_ClearTicks()
{
   pstTheSYSTICKController->VAL = 1; // Write any value to clear
}

//------------------------------------------------------------------------------
UINT
SYSTICK_GetTicks()
{
   return (UINT)(pstTheSYSTICKController->VAL & VAL_CURRENT_MASK);
}
