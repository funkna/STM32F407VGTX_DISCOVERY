// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SYSTICK_H_
#define SYSTICK_H_

// Includes ---------------------------------------------------------------------------------------
#include "cortex_m4.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

//--------------------------------------------------------------
// SYSTICK Controller Register Bitmasks
//--------------------------------------------------------------
#define CTRL_ENABLE              (0x01UL << 0)  // Counter enable
#define CTRL_TICKINT             (0x01UL << 1)  // Systick exception request enable
#define CTRL_CLKSOURCE           (0x01UL << 2)  // Clock source selection
#define CTRL_COUNTFLAG           (0x01UL << 16) // Count flag
#define LOAD_RELOAD_MASK         (0x00FFFFFFUL)
#define VAL_CURRENT_MASK         (0x00FFFFFFUL)


// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// SYSTICK Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT CTRL;
   UINT LOAD;
   UINT VAL;
   UINT CALIB;
} SYSTICKRegistersStruct;

// Functions --------------------------------------------------------------------------------------
SYSTICKRegistersStruct* GetSYSTICKController()
{
   return (SYSTICKRegistersStruct*)PERIPHERAL_ADDRESS_SYSTICK;
}

#endif // SYSTICK_H_
