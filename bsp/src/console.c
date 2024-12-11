//------------------------------------------------------------------------------
//! \file console.c
//! \brief Serial console functionality.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include "console.h"
#include "usart.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
USARTConfigurationStruct stTheConsoleUSARTConfig = {
   USARTBAUD_9600,
   USARTWORD_8BIT,
   USARTPARITY_NONE,
   USARTSTOP_1BIT,
   USARTFLOWCTL_DISABLED
};

//------------------------------------------------------------------------------
BOOL
Console_Initialize()
{
   BOOL bSuccess = TRUE;
   bSuccess &= USART_Initialize(CONSOLE_USART);
   bSuccess &= USART_SetConfig(CONSOLE_USART, &stTheConsoleUSARTConfig);
   bSuccess &= USART_Enable(CONSOLE_USART);
   return bSuccess;
}

//------------------------------------------------------------------------------
void
Console_Printf(
   const SCHAR* szFormat_,
   ...)
{
   static UCHAR aucBuffer[CONSOLE_BUFFER_SIZE];

   va_list stArgs;
   va_start(stArgs, szFormat_);
   UINT uiBytesInBuffer = vsnprintf((SCHAR*)(&aucBuffer[0]), (CONSOLE_BUFFER_SIZE - 2), szFormat_, stArgs);
   va_end(stArgs);

   aucBuffer[uiBytesInBuffer++] = '\r';
   aucBuffer[uiBytesInBuffer++] = '\n';

   USART_WriteData(CONSOLE_USART, aucBuffer, uiBytesInBuffer);
}
