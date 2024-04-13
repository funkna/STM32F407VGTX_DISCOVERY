// Includes ---------------------------------------------------------------------------------------
#include "led.h"
#include "button.h"

#include "drivers/nvic_driver.h"
#include "drivers/exti_driver.h"
#include "drivers/spi_driver.h"
#include "drivers/syscfg_driver.h"

#include "user_app_1.h"

// Statics, Externs & Globals ---------------------------------------------------------------------
static UCHAR aucTheSPIWriteTransferBuffer[] = {0xAA};
static UCHAR aucTheSPIReadTransferBuffer[64] = {0};
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

   bSuccess |= SPI_SetConfig(SPI1, &stSPIMasterConfig);
   bSuccess |= SPI_Enable(SPI1);

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

   bSuccess |= SPI_SetConfig(SPI2, &stSPISlaveConfig);
   bSuccess |= SPI_Enable(SPI2);
   bSuccess |= SPI_ConfigureAsInterrupt(SPI2);

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

      if(SPI_GetReceiveTransferState(SPI2) == SPISTATE_IDLE)
      {
         (void)SPI_Transfer(SPI2, &aucTheSPIReadTransferBuffer[0], 4, NULL, 0);
      }

      if(SPI_GetTransmitTransferState(SPI2) == SPISTATE_IDLE)
      {
         (void)SPI_Transfer(SPI2, NULL, 0, &aucTheSPIWriteTransferBuffer[0], 1);
      }
   }
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
