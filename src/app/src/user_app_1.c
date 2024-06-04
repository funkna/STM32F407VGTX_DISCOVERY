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
      USARTMODE_TXRX,
      USARTBAUD_9600,
      USARTWORD_8BIT,
      USARTPARITY_NONE,
      USARTSTOP_1BIT,
      USARTFLOWCTL_DISABLED
   };

   bSuccess |= USART_SetConfig(USART2, &stUSARTConfig);
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

      UCHAR aucReadBuffer[0xFF] = {0};

      // Echo a byte.
      USART_ReadData(USART2, (UCHAR*)&aucReadBuffer[0], 1);
      USART_WriteData(USART2, (UCHAR*)&aucReadBuffer[0], 1);
   }
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
