// Includes ---------------------------------------------------------------------------------------
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"
#include "user_app_1/user_app_1.h"

// Statics, Externs & Globals ---------------------------------------------------------------------
static UINT uiCounter = 0;
static const UINT uiMAX_COUNT = 0x8000;

// Functions --------------------------------------------------------------------------------------
BOOL Initialize_UserApp1()
{
   if(!RCC_Initialize())
   {
      return FALSE;
   }

   if(!GPIO_Initialize(GPIO_GPIOD))
   {
      return FALSE;
   }

   BOOL bSuccess = TRUE;

   bSuccess = bSuccess && GPIO_SetConfigPinMode(GPIO_GPIOD, GPIO_PIN_12, MODE_GP_OUTPUT);
   bSuccess = bSuccess && GPIO_SetConfigPinOutputType(GPIO_GPIOD, GPIO_PIN_12, OUTPUT_PUSHPULL);
   bSuccess = bSuccess && GPIO_SetConfigPinSpeed(GPIO_GPIOD, GPIO_PIN_12, SPEED_MED);
   bSuccess = bSuccess && GPIO_SetConfigPinPUPD(GPIO_GPIOD, GPIO_PIN_12, PUPD_PD);


   return bSuccess;
}

void Run_UserApp1()
{
   uiCounter++;
   if(uiCounter > uiMAX_COUNT)
   {
      uiCounter = 0;
      GPIO_TogglePin(GPIO_GPIOD, GPIO_PIN_12);
   }
}

BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
