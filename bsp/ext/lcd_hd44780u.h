//------------------------------------------------------------------------------
//! \file lcd_hd44780u.h
//! \brief LCD device funcionality.
//------------------------------------------------------------------------------
#ifndef __LCD_HD44780U
#define __LCD_HD44780U

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief LCD Line
//------------------------------------------------------------------------------
typedef enum
{
   HD440780U_LINE_1 = 0,
   HD440780U_LINE_2,
   HD440780U_LINE_MAX
} HD440780ULineEnum;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
BOOL HD440780U_Initialize();
BOOL HD440780U_SendCommand(UCHAR ucCommand_);
BOOL HD440780U_WriteByte(UCHAR ucByte_);
void HD440780U_WriteString(HD440780ULineEnum eLine_, const SCHAR* szFormat_, ...);

#endif // __LCD_HD44780U
