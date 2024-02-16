// Includes ---------------------------------------------------------------------------------------
#include "led/led.h"
#include "user_app_1/user_app_1.h"

// Statics, Externs & Globals ---------------------------------------------------------------------
static UINT uiCounter0 = 0;
static UINT uiCounter1 = 0;
static const UINT uiMAX_COUNT = 0x20000;

// Functions --------------------------------------------------------------------------------------
BOOL Initialize_UserApp1()
{
   BOOL bSuccess = TRUE;

   return bSuccess;
}

void Run_UserApp1()
{
   uiCounter0++;
   if(uiCounter0 > uiMAX_COUNT)
   {
      uiCounter0 = 0;
      uiCounter1++;
      if(uiCounter1 == 1)
      {
         LED_On(LED_GREEN);
      }
      if(uiCounter1 == 2)
      {
         LED_On(LED_ORANGE);
      }
      if(uiCounter1 == 3)
      {
         LED_On(LED_RED);
      }
      if(uiCounter1 == 4)
      {
         LED_On(LED_BLUE);
      }
      if(uiCounter1 == 5)
      {
         LED_Off(LED_GREEN);
         LED_Off(LED_ORANGE);
         LED_Off(LED_RED);
         LED_Off(LED_BLUE);
         uiCounter1 = 0;
      }
   }
}

BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
