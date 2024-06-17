// Redundancy Prevention --------------------------------------------------------------------------
#ifndef HD44870U_H_
#define HD44870U_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Initilize the HD440780U
// -------------------------------------------------------------
BOOL HD440780U_Initialize();

// -------------------------------------------------------------
// Send a command to the HD440780U
// -------------------------------------------------------------
BOOL HD440780U_SendCommand(
   UCHAR ucCommand_);

// -------------------------------------------------------------
// Write a byte to the HD440780U
// -------------------------------------------------------------
BOOL HD440780U_WriteByte(
   UCHAR ucByte_);

// -------------------------------------------------------------
// Write a series of characters to the HD440780U.
// -------------------------------------------------------------
void HD440780U_WriteString(
   const SCHAR* szFormat_,
   ...);

#endif // HD44870U_H_
