// Includes ---------------------------------------------------------------------------------------
#include "led/led.h"
#include "button/button.h"
#include "user_app_1/user_app_1.h"

// Statics, Externs & Globals ---------------------------------------------------------------------
static UINT uiCounter = 0;
static const UINT uiMAX_COUNT = 0x10000;

// Functions --------------------------------------------------------------------------------------
BOOL Initialize_UserApp1()
{
   BOOL bSuccess = TRUE;

   return bSuccess;
}

void Run_UserApp1()
{
   uiCounter++;
   if(uiCounter > uiMAX_COUNT)
   {
      uiCounter = 0;
      LED_Toggle(LED_GREEN);
   }

   if(Button_IsPressed(BUTTON_USER))
   {
      LED_On(LED_BLUE);
   }
   else
   {
      LED_Off(LED_BLUE);
   }
}

BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
