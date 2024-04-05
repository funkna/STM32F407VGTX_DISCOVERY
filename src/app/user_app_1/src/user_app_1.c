// Includes ---------------------------------------------------------------------------------------
#include "led/led.h"
#include "button/button.h"

#include "driver/cortex-m4/nvic/nvic_driver.h"
#include "driver/exti/exti_driver.h"
#include "driver/spi/spi_driver.h"
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
   BOOL bSuccess = TRUE;
   bSuccess |= Button_ConfigureAsInterrupt(BUTTON_PRESS, &ButtonPressCallback);

   SPIConfigurationStruct stSPIMasterConfig = {
      SPIMODE_MASTER,
      SPIBUS_FULL_DUPLEX,
      SPICLK_PRESCALARDIV_2,
      SPICPOL_IDLE_LO,
      SPICPHA_RISE,
      SPIDFF_8BITS,
      SPISSM_ENABLE,
      SPISSI_ENABLE,
      SPIMULTIMASTER_DISABLE
   };

   bSuccess |= SPI_SetConfig(SPI_SPI1, &stSPIMasterConfig);
   bSuccess |= SPI_Enable(SPI_SPI1);

   SPIConfigurationStruct stSPISlaveConfig = {
      SPIMODE_SLAVE,
      SPIBUS_FULL_DUPLEX,
      SPICLK_PRESCALARDIV_2,
      SPICPOL_IDLE_LO,
      SPICPHA_RISE,
      SPIDFF_8BITS,
      SPISSM_DISABLE,
      SPISSI_DISABLE,
      SPIMULTIMASTER_DISABLE
   };

   bSuccess |= SPI_SetConfig(SPI_SPI2, &stSPISlaveConfig);
   bSuccess |= SPI_Enable(SPI_SPI2);

   return bSuccess;
}

// -------------------------------------------------------------
void Run_UserApp1()
{
   static UCHAR aucWriteData[1] = {0xAA};
   static UCHAR aucReadData[1];

   uiCounter++;
   if(uiCounter > uiMAX_COUNT)
   {
      uiCounter = 0;
      if(SPI_Write(SPI_SPI1, &aucWriteData[0], 1))
      {
         LED_Toggle(LED_GREEN);
      }

      for(UINT uiCounter2 = 0; uiCounter2 < 0x1000; uiCounter2++)

      if(SPI_Read(SPI_SPI2, &aucReadData[0], 1) &&
         (aucWriteData[0] == aucReadData[0]))
      {
         LED_Toggle(LED_ORANGE);
      }
   }
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
