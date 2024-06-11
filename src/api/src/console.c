// Includes ---------------------------------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include "console.h"
#include "drivers/usart_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
USARTConfigurationStruct stTheUSARTConfig = {
   USARTBAUD_9600,
   USARTWORD_8BIT,
   USARTPARITY_NONE,
   USARTSTOP_1BIT,
   USARTFLOWCTL_DISABLED
};

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
BOOL Console_Initialize()
{
   BOOL bSuccess = TRUE;
   bSuccess &= USART_Initialize(CONSOLE_USART);
   bSuccess &= USART_SetConfig(CONSOLE_USART, &stTheUSARTConfig);
   bSuccess &= USART_Enable(CONSOLE_USART);
   return bSuccess;
}

// -------------------------------------------------------------
void Console_Printf(const SCHAR* szFormat_, ...)
{
   static SCHAR acTimeBuffer[CONSOLE_BUFFER_SIZE];

   va_list stArgs;
   va_start(stArgs, szFormat_);
   UINT uiBytesInBuffer = vsnprintf(&acTimeBuffer[0], (CONSOLE_BUFFER_SIZE - 2), szFormat_, stArgs);
   va_end(stArgs);

   acTimeBuffer[uiBytesInBuffer++] = '\r';
   acTimeBuffer[uiBytesInBuffer++] = '\n';

   USART_WriteData(CONSOLE_USART, acTimeBuffer, uiBytesInBuffer);
}
