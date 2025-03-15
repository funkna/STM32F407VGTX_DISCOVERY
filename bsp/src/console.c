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
#define CONSOLE_BUFFER_SIZE   (256)
#define CONSOLE_USART         (USART2)

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

static UCHAR aucReadBuffer[CONSOLE_BUFFER_SIZE];
static UCHAR aucWriteBuffer[CONSOLE_BUFFER_SIZE];

//------------------------------------------------------------------------------
BOOL
Console_Initialize()
{
   return USART_Initialize(CONSOLE_USART, &stTheConsoleUSARTConfig);
}

//------------------------------------------------------------------------------
void
Console_Printf(
   const SCHAR* szFormat_,
   ...)
{
   va_list stArgs;
   va_start(stArgs, szFormat_);
   UINT uiBytesInBuffer = vsnprintf((SCHAR*)(&aucWriteBuffer[0]), CONSOLE_BUFFER_SIZE, szFormat_, stArgs);
   va_end(stArgs);

   (void)USART_WriteData(CONSOLE_USART, &aucWriteBuffer[0], uiBytesInBuffer);
}

//------------------------------------------------------------------------------
void
ConsoleEcho_RunTask()
{
   UINT uiEchoBytes = USART_ReadData(CONSOLE_USART, &aucReadBuffer[0], CONSOLE_BUFFER_SIZE);
   if(uiEchoBytes > 0)
   {
      (void)USART_WriteData(CONSOLE_USART, &aucReadBuffer[0], uiEchoBytes);
   }
}
