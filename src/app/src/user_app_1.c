// Includes ---------------------------------------------------------------------------------------
#include "led.h"
#include "button.h"
#include "ext/aardvark.h"

#include "drivers/nvic_driver.h"
#include "drivers/exti_driver.h"
// #include "drivers/spi_driver.h"
#include "drivers/syscfg_driver.h"
#include "drivers/i2c_driver.h"

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
   BOOL bSuccess = TRUE;
   bSuccess |= Button_ConfigureAsInterrupt(BUTTON_PRESS, &ButtonPressCallback);

   I2CConfigurationStruct stI2CMasterConfig = {
      I2C1_DEVICE_ADDRESS,
      I2CACK_ENABLE,
      I2CDUTY_NONE,
      I2CCLK_SM_100KHZ
   };

   bSuccess |= I2C_SetConfig(I2C1, &stI2CMasterConfig);
   bSuccess |= I2C_Enable(I2C1);
   bSuccess |= I2C_ConfigureAsInterrupt(I2C1);

   bSuccess |= InitializeAardvark();

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

      static BOOL bWriteCompleted = FALSE;
      static UCHAR ucTheAardvarkLEDValue = 0xAA;

      if((I2C_GetState(I2C1) == I2CSTATE_IDLE) &&
         (!bWriteCompleted))
      {
         (void)WriteOutputAardvark(~ucTheAardvarkLEDValue);
         bWriteCompleted = TRUE;
      }

      if((I2C_GetState(I2C1) == I2CSTATE_IDLE) &&
         (bWriteCompleted))
      {
         (void)ReadOutputAardvark(&ucTheAardvarkLEDValue);
         bWriteCompleted = FALSE;
      }
   }
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
