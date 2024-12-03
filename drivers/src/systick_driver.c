// Includes ---------------------------------------------------------------------------------------
#include "cortex_m4/systick.h"
#include "drivers/systick_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static SYSTICKRegistersStruct* pstTheSYSTICKController = NULL;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
BOOL SYSTICK_Initialize()
{
   pstTheSYSTICKController = GetSYSTICKController();

   pstTheSYSTICKController->LOAD = LOAD_RELOAD_MASK;
   pstTheSYSTICKController->CTRL |= CTRL_ENABLE;

   return (pstTheSYSTICKController != NULL);
}

// -------------------------------------------------------------
void SYSTICK_ClearTicks()
{
   pstTheSYSTICKController->VAL = 1; // Write any value to clear
}


// -------------------------------------------------------------
UINT SYSTICK_GetTicks()
{
   if(pstTheSYSTICKController == NULL)
   {
      return 0;
   }

   return (UINT)(pstTheSYSTICKController->VAL & VAL_CURRENT_MASK);
}
