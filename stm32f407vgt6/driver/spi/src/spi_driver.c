// Includes ---------------------------------------------------------------------------------------
#include "device/spi/spi.h"
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"
#include "driver/spi/spi_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static SPIRegistersStruct* apstTheSPIControllers[SPI_MAX] = {NULL};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum SPIEnumToSTM32Enum(
   SPIControllerEnum eController_)
{
   switch(eController_)
   {
      case SPI_SPI1:
         return SPI1;
      case SPI_SPI2:
         return SPI2_I2S2;
      case SPI_SPI3:
         return SPI3_I2S3;
      default:
         return INVALID;
   }
}

// -------------------------------------------------------------
BOOL SPI_Initialize(
   SPIControllerEnum eController_)
{
   if(apstTheSPIControllers[eController_] == NULL)
   {
      STM32F407VGT6_PeriperalEnum ePeripheral = SPIEnumToSTM32Enum(eController_);
      apstTheSPIControllers[eController_] = GetSPIController(eController_);
      if((apstTheSPIControllers[eController_] == NULL) ||
         (!RCC_EnablePeripheralClock(ePeripheral)))
      {
         (void)SPI_Deinitialize(eController_);
         return FALSE;
      }

      GPIOPinConfigurationStruct stSPIConfig = {GPIOMODE_ALT_FUNC, GPIOTYPE_PUSHPULL, GPIOSPEED_HI, GPIOPUPD_NONE, GPIOALTFUNC_AF5};
      if(eController_ == SPI_SPI1)
      {
         GPIO_SetConfig(GPIO_GPIOA, GPIO_PIN_4, &stSPIConfig); // SS
         GPIO_SetConfig(GPIO_GPIOA, GPIO_PIN_5, &stSPIConfig); // SCK
         GPIO_SetConfig(GPIO_GPIOA, GPIO_PIN_6, &stSPIConfig); // MISO
         GPIO_SetConfig(GPIO_GPIOA, GPIO_PIN_7, &stSPIConfig); // MOSI
      }
      else if(eController_ == SPI_SPI2)
      {
         GPIO_SetConfig(GPIO_GPIOB, GPIO_PIN_12, &stSPIConfig); // SS
         GPIO_SetConfig(GPIO_GPIOB, GPIO_PIN_13, &stSPIConfig); // SCK
         GPIO_SetConfig(GPIO_GPIOB, GPIO_PIN_14, &stSPIConfig); // MISO
         GPIO_SetConfig(GPIO_GPIOB, GPIO_PIN_15, &stSPIConfig); // MOSI
      }
      else
      {
         // TODO
         return FALSE;
      }
   }
   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_Deinitialize(
   SPIControllerEnum eController_)
{
   STM32F407VGT6_PeriperalEnum ePeripheral = SPIEnumToSTM32Enum(eController_);
   apstTheSPIControllers[eController_] = NULL;
   return RCC_ResetPeripheralClock(ePeripheral);
}

// -------------------------------------------------------------
BOOL SPI_Enable(
   SPIControllerEnum eController_)
{
   if(apstTheSPIControllers[eController_] == NULL)
   {
      return FALSE;
   }

   apstTheSPIControllers[eController_]->CR1 |= CR1_SPE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_Disable(
   SPIControllerEnum eController_)
{
   if(apstTheSPIControllers[eController_] == NULL)
   {
      return FALSE;
   }

   apstTheSPIControllers[eController_]->CR1 &= ~CR1_SPE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_SetConfig(
   SPIControllerEnum eController_,
   const SPIConfigurationStruct* pstConfiguration_)
{
   if(apstTheSPIControllers[eController_] == NULL)
   {
      return FALSE;
   }

   UINT uiCR1Value = apstTheSPIControllers[eController_]->CR1;
   UINT uiCR2Value = apstTheSPIControllers[eController_]->CR2;

   // Master/Slave mode
   if(pstConfiguration_->eMode == SPIMODE_MASTER)
   {
      uiCR1Value |= CR1_MSTR;
   }
   else // SPIMODE_SLAVE
   {
      uiCR1Value &= ~CR1_MSTR;
   }

   // Bus mode Bi-Directional settings
   switch(pstConfiguration_->eBusConfig)
   {
      case SPIBUS_FULL_DUPLEX:
         uiCR1Value &= ~CR1_BIDIMODE;
         break;
      case SPIBUS_HALF_DUPLEX:
         uiCR1Value |= CR1_BIDIMODE;
         break;
      case SPIBUS_SIMPLEX_RX:
         uiCR1Value &= ~CR1_BIDIMODE;
         uiCR1Value |= CR1_RXONLY;
         break;
   }

   // Clock prescalar division
   switch(pstConfiguration_->eClockPrescalar)
   {
      case SPICLK_PRESCALARDIV_2:
         uiCR1Value |= (CR1_BR_PCLK_DIV2 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_4:
         uiCR1Value |= (CR1_BR_PCLK_DIV4 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_8:
         uiCR1Value |= (CR1_BR_PCLK_DIV8 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_16:
         uiCR1Value |= (CR1_BR_PCLK_DIV16 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_32:
         uiCR1Value |= (CR1_BR_PCLK_DIV32 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_64:
         uiCR1Value |= (CR1_BR_PCLK_DIV64 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_128:
         uiCR1Value |= (CR1_BR_PCLK_DIV128 << CR1_BR_OFFSET);
         break;
      case SPICLK_PRESCALARDIV_256:
         uiCR1Value |= (CR1_BR_PCLK_DIV256 << CR1_BR_OFFSET);
         break;
   }

   // Clock polarity
   if(pstConfiguration_->eClockPolarity == SPICPOL_IDLE_HI)
   {
      uiCR1Value |= CR1_CPOL;

      // Clock edge trigger
      if(pstConfiguration_->eClockPhase == SPICPHA_FALL)
      {
         uiCR1Value &= ~CR1_CPHA;
      }
      else // SPICPHA_RISE
      {
         uiCR1Value |= CR1_CPHA;
      }
   }
   else // SPICPOL_IDLE_LO
   {
      uiCR1Value &= ~CR1_CPOL;

      // Clock edge trigger
      if(pstConfiguration_->eClockPhase == SPICPHA_FALL)
      {
         uiCR1Value |= CR1_CPHA;
      }
      else // SPICPHA_RISE
      {
         uiCR1Value &= ~CR1_CPHA;
      }
   }

   if(pstConfiguration_->eDataFrameSize == SPIDFF_16BITS)
   {
      uiCR1Value |= CR1_DFF;
   }
   else // SPIDFF_8BITS
   {
      uiCR1Value &= ~CR1_DFF;
   }

   if(pstConfiguration_->eSlaveManagement == SPISSM_ENABLE)
   {
      uiCR1Value |= CR1_SSM;
   }
   else // SPISSM_DISABLE
   {
      uiCR1Value &= ~CR1_SSM;
   }

   if(pstConfiguration_->eSlaveManagement == SPISSI_ENABLE)
   {
      uiCR1Value |= CR1_SSI;
   }
   else // SPISSI_DISABLE
   {
      uiCR1Value &= ~CR1_SSI;
   }

   if(pstConfiguration_->eMultiMaster == SPIMULTIMASTER_ENABLE)
   {
      uiCR2Value &= ~CR2_SSOE;
   }
   else // SPIMULTIMASTER_DISABLE
   {
      uiCR2Value |= CR2_SSOE;
   }

   apstTheSPIControllers[eController_]->CR1 = uiCR1Value;
   apstTheSPIControllers[eController_]->CR2 = uiCR2Value;
   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_GetConfig(
   SPIControllerEnum eController_,
   SPIConfigurationStruct* pstConfiguration_)
{
   // TODO
   return FALSE;
}

// -------------------------------------------------------------
BOOL SPI_Read(
   SPIControllerEnum eController_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   if(apstTheSPIControllers[eController_] == NULL)
   {
      return FALSE;
   }

   while(uiDataLength_ > 0)
   {
      if(apstTheSPIControllers[eController_]->SR & SR_RXNE)
      {
         *pucData_ = apstTheSPIControllers[eController_]->DR;
         pucData_++;
         uiDataLength_--;
      }
   }

   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_Write(
   SPIControllerEnum eController_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   if(apstTheSPIControllers[eController_] == NULL)
   {
      return FALSE;
   }

   while(uiDataLength_ > 0)
   {
      if(apstTheSPIControllers[eController_]->SR & SR_TXE)
      {
         apstTheSPIControllers[eController_]->DR = *pucData_;
         pucData_++;
         uiDataLength_--;
      }
   }

   return TRUE;
}
