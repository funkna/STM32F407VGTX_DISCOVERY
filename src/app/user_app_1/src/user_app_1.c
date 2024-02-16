// Includes ---------------------------------------------------------------------------------------
#include "led/led.h"
#include "button/button.h"

#include "driver/cortex-m4/nvic/nvic_driver.h"
#include "driver/exti/exti_driver.h"
#include "driver/syscfg/syscfg_driver.h"

#include "user_app_1/user_app_1.h"

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
   return Button_ConfigureAsInterrupt(BUTTON_PRESS, &ButtonPressCallback);
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
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
