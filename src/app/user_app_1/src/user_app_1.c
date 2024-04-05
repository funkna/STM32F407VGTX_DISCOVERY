// Includes ---------------------------------------------------------------------------------------
#include "led/led.h"
#include "button/button.h"

#include "driver/cortex-m4/nvic/nvic_driver.h"
#include "driver/exti/exti_driver.h"
#include "driver/spi/spi_driver.h"
#include "driver/syscfg/syscfg_driver.h"

#include "user_app_1/user_app_1.h"

// Statics, Externs & Globals ---------------------------------------------------------------------
static UCHAR ucTheSPIReadByte = 0x00;
static UINT uiCounter = 0;
static const UINT uiMAX_COUNT = 0x10000;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
static void ButtonPressCallback(void)
{
   LED_Toggle(LED_RED);
}

static void SPIReadCallback(void)
{
   ucTheSPIReadByte = 0x00;

   SPI_Read(SPI_SPI2, &ucTheSPIReadByte);
   if(0xAA == ucTheSPIReadByte)
   {
      LED_Toggle(LED_ORANGE);
   }
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

   bSuccess |= SPI_ConfigureAsInterrupt(SPI_SPI2, SPIINTTYPE_RECEIVE, &SPIReadCallback);

   return bSuccess;
}

// -------------------------------------------------------------
void Run_UserApp1()
{
   uiCounter++;
   if(uiCounter > uiMAX_COUNT)
   {
      uiCounter = 0;
      if(SPI_Write(SPI_SPI1, 0xAA))
      {
         LED_Toggle(LED_GREEN);
      }
   }
}

// -------------------------------------------------------------
BOOL Exit_UserApp1()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
