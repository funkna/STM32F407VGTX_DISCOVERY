// Includes ---------------------------------------------------------------------------------------
#include <string.h>
#include "led.h"
#include "button.h"

#include "drivers/usart_driver.h"

#include "user_app_1.h"

// Defines ----------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static UINT uiCounter = 0;
static const UINT uiMAX_COUNT = 0x10000;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
static void ButtonPressCallback(void)
{
   LED_Toggle(LED_RED);
}

// -------------------------------------------------------------
BOOL Initialize_UserApp1()
{
   BOOL bSuccess = FALSE;
   bSuccess |= Button_ConfigureAsInterrupt(BUTTON_PRESS, &ButtonPressCallback);

   USARTConfigurationStruct stUSARTConfig = {
      USARTBAUD_9600,
      USARTWORD_8BIT,
      USARTPARITY_NONE,
      USARTSTOP_1BIT,
      USARTFLOWCTL_DISABLED
   };

   bSuccess |= USART_SetConfig(USART2, &stUSARTConfig);
   bSuccess |= USART_ConfigureAsInterrupt(USART2);
   bSuccess |= USART_Enable(USART2);

   return bSuccess;
}

// -------------------------------------------------------------
void Run_UserApp1()
{
  uiCounter++;
  if(uiCounter > uiMAX_COUNT)
  {
     uiCounter = 0;

     LED_Toggle(LED_GREEN);
  }

   static BOOL bWriteComplete = TRUE; // TRUE to get started.
   static UCHAR aucReadBuffer = 0x00;

   // Echo a byte.
   if(bWriteComplete)
   {
      USART_Transfer(USART2, USARTTRANSFER_READ, &aucReadBuffer, 1);
      bWriteComplete = FALSE;
   }

   if(USART_GetStates(USART2) == USARTSTATE_IDLE)
   {
      USART_WriteData(USART2, &aucReadBuffer, 1);
      bWriteComplete = TRUE;
   }

}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
