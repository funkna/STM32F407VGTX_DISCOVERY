// Includes ---------------------------------------------------------------------------------------
#include "led.h"
#include "button.h"

#include "drivers/nvic_driver.h"
#include "drivers/exti_driver.h"
// #include "drivers/spi_driver.h"
#include "drivers/syscfg_driver.h"
#include "drivers/i2c_driver.h"

#include "user_app_1.h"

// Defines ----------------------------------------------------------------------------------------
#define AARDVARK_I2C_PORT_EXPANDER_ADDRESS   (0x38) // This can be configured by the hardware jumper.
#define AARDVARK_I2C_CMD_INPUT_REGISTER      (0x00)
#define AARDVARK_I2C_CMD_OUTPUT_REGISTER     (0x01)
#define AARDVARK_I2C_CMD_POLARITY_REGISTER   (0x02)
#define AARDVARK_I2C_CMD_CONFIG_REGISTER     (0x03)
#define AARDVARK_I2C_PORT_ALL_PINS           (0xFF)

// Statics, Externs & Globals ---------------------------------------------------------------------
static UINT uiCounter = 0;
static const UINT uiMAX_COUNT = 0x10000;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
static BOOL InitializeAardvark(void)
{
   const UINT uiCONFIG_COMMAND_LENGTH = 2;
   UCHAR aucConfigureIODirectionCommand[] = {
      AARDVARK_I2C_CMD_CONFIG_REGISTER,
      ~AARDVARK_I2C_PORT_ALL_PINS
   };

   return I2C_WriteData(I2C1, I2CMODE_MASTER, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucConfigureIODirectionCommand[0], uiCONFIG_COMMAND_LENGTH);
}

// -------------------------------------------------------------
static BOOL WriteOutputAardvark(
   UCHAR ucValue_)
{
   const UINT uiWRITE_OUTPUT_COMMAND_LENGTH = 2;
   UCHAR aucWriteIODirectionCommand[] = {
      AARDVARK_I2C_CMD_OUTPUT_REGISTER,
      ucValue_
   };

   return I2C_WriteData(I2C1, I2CMODE_MASTER, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucWriteIODirectionCommand[0], uiWRITE_OUTPUT_COMMAND_LENGTH);
}

// -------------------------------------------------------------
static BOOL ReadOutputAardvark(
   UCHAR* pucValue_)
{
   if(pucValue_ == NULL)
   {
      return FALSE;
   }

   const UINT uiREAD_OUTPUT_COMMAND_LENGTH = 1;
   UCHAR aucReadIODirectionCommand[] = {
      AARDVARK_I2C_CMD_OUTPUT_REGISTER
   };

   // Utilizing repeated START here, but alternatively an entirely different I2C Write transaction could be performed here.
   return I2C_ReadData(I2C1, I2CMODE_MASTER, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucReadIODirectionCommand[0], uiREAD_OUTPUT_COMMAND_LENGTH, pucValue_, 1);
}

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

      static UCHAR ucTheAardvarkLEDValue = 0xAA;
      WriteOutputAardvark(~ucTheAardvarkLEDValue);
      ReadOutputAardvark(&ucTheAardvarkLEDValue);
   }
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
