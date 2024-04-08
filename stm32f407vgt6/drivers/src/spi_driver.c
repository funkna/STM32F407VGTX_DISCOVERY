// Includes ---------------------------------------------------------------------------------------
#include <string.h>
#include "devices/spi.h"
#include "drivers/gpio_driver.h"
#include "drivers/rcc_driver.h"
#include "drivers/spi_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
typedef struct
{
   UCHAR* pucReceiveBuffer;
   UINT uiReceiveBytes;
   UINT uiRequestedBytes;
} SPIBuffersStruct;

typedef struct
{
   SPIRegistersStruct* pstRegisters;
   SPIConfigurationStruct stConfiguration;
   SPIBuffersStruct stBuffers;
   SPITransferStateEnum eState;
} SPIDeviceStruct;

// Statics, Externs & Globals ---------------------------------------------------------------------
static const GPIOConfigurationStruct stTheSPIPinConfig = {
   GPIOMODE_ALT_FUNC,
   GPIOTYPE_PUSHPULL,
   GPIOSPEED_HI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF5
};
static SPIDeviceStruct astTheSPIDevices[SPI_MAX] = {0};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum SPIEnumToSTM32Enum(
   SPIControllerEnum eController_)
{
   switch(eController_)
   {
      case SPI1:
      {
         return PERIPHERAL_SPI1;
      }
      case SPI2:
      {
         return PERIPHERAL_SPI2_I2S2;
      }
      case SPI3:
      {
         return PERIPHERAL_SPI3_I2S3;
      }
      default:
      {
         return PERIPHERAL_INVALID;
      }
   }
}

// -------------------------------------------------------------
// Handle the EXTI0 interrupt here, as it routed to the button.
// -------------------------------------------------------------
void SPI2_IRQHandler(void)
{
   UINT uiSPI2_SR = astTheSPIDevices[SPI2].pstRegisters->SR;

   // Receive Interrupt
   if((uiSPI2_SR & SR_RXNE) &&
      (astTheSPIDevices[SPI2].stBuffers.pucReceiveBuffer != NULL))
   {
      if(SPI_ReadByte(SPI2, astTheSPIDevices[SPI2].stBuffers.pucReceiveBuffer))
      {
         astTheSPIDevices[SPI2].stBuffers.pucReceiveBuffer++;
         astTheSPIDevices[SPI2].stBuffers.uiReceiveBytes++;
      }

      if(astTheSPIDevices[SPI2].stBuffers.uiRequestedBytes == astTheSPIDevices[SPI2].stBuffers.uiReceiveBytes)
      {
         astTheSPIDevices[SPI2].pstRegisters->CR2 &= ~CR2_RXNEIE;
         astTheSPIDevices[SPI2].eState = SPISTATE_IDLE;
      }
   }
}

// -------------------------------------------------------------
BOOL SPI_Initialize(
   SPIControllerEnum eController_)
{
   BOOL bSuccess = FALSE;
   astTheSPIDevices[eController_].pstRegisters = GetSPIController(eController_);
   if(astTheSPIDevices[eController_].pstRegisters != NULL)
   {
      bSuccess = RCC_EnablePeripheralClock(SPIEnumToSTM32Enum(eController_));
   }

   if(bSuccess)
   {
      switch(eController_)
      {
         case SPI1:
         {
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_4, &stTheSPIPinConfig); // SS
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_5, &stTheSPIPinConfig); // SCK
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_6, &stTheSPIPinConfig); // MISO
            GPIO_SetConfig(GPIO_PORT_A, GPIO_PIN_7, &stTheSPIPinConfig); // MOSI
            break;
         }
         case SPI2:
         {
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_12, &stTheSPIPinConfig); // SS
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_13, &stTheSPIPinConfig); // SCK
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_14, &stTheSPIPinConfig); // MISO
            GPIO_SetConfig(GPIO_PORT_B, GPIO_PIN_15, &stTheSPIPinConfig); // MOSI
            break;
         }
         case SPI3: // TODO: Fall-through for now
         default:
         {
            return FALSE;
         }
      }
   }

   return bSuccess;
}

// -------------------------------------------------------------
BOOL SPI_Reset(
   SPIControllerEnum eController_)
{
   return RCC_ResetPeripheralClock(SPIEnumToSTM32Enum(eController_));
}

// -------------------------------------------------------------
BOOL SPI_Enable(
   SPIControllerEnum eController_)
{
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheSPIDevices[eController_].pstRegisters->CR1 |= CR1_SPE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_Disable(
   SPIControllerEnum eController_)
{
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheSPIDevices[eController_].pstRegisters->CR1 &= ~CR1_SPE;
   return TRUE;
}

// -------------------------------------------------------------
BOOL SPI_SetConfig(
   SPIControllerEnum eController_,
   const SPIConfigurationStruct* pstConfiguration_)
{
   if((astTheSPIDevices[eController_].pstRegisters == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   UINT uiCR1Value = astTheSPIDevices[eController_].pstRegisters->CR1;
   UINT uiCR2Value = astTheSPIDevices[eController_].pstRegisters->CR2;

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

   if(pstConfiguration_->eInternalSelect == SPISSI_ENABLE)
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

   astTheSPIDevices[eController_].pstRegisters->CR1 = uiCR1Value;
   astTheSPIDevices[eController_].pstRegisters->CR2 = uiCR2Value;

   memcpy(&(astTheSPIDevices[eController_].stConfiguration), pstConfiguration_, sizeof(SPIConfigurationStruct));

   return TRUE;
}

// -------------------------------------------------------------
SPIConfigurationStruct* SPI_GetConfig(
   SPIControllerEnum eController_)
{
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return NULL;
   }

   return &(astTheSPIDevices[eController_].stConfiguration);
}

// -------------------------------------------------------------
BOOL SPI_ReadByte(
   SPIControllerEnum eController_,
   UCHAR* pucData_)
{
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   if(astTheSPIDevices[eController_].pstRegisters->SR & SR_RXNE)
   {
      *pucData_ = astTheSPIDevices[eController_].pstRegisters->DR;
      return TRUE;
   }

   return FALSE;
}

// -------------------------------------------------------------
BOOL SPI_WriteByte(
   SPIControllerEnum eController_,
   UCHAR ucData_)
{
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   if(astTheSPIDevices[eController_].pstRegisters->SR & SR_TXE)
   {
      astTheSPIDevices[eController_].pstRegisters->DR = ucData_;
      return TRUE;
   }
   return FALSE;
}

// -------------------------------------------------------------
BOOL SPI_ReadTransfer(
   SPIControllerEnum eController_,
   UCHAR* pucReceiveBuffer_,
   UINT uiRequestedBytes_)
{
   // Verify arguments & callback
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   if(pucReceiveBuffer_ == NULL)
   {
      // Set the buffer
      astTheSPIDevices[eController_].stBuffers.pucReceiveBuffer = pucReceiveBuffer_;
      astTheSPIDevices[eController_].stBuffers.uiReceiveBytes = 0;
      astTheSPIDevices[eController_].stBuffers.uiRequestedBytes = uiRequestedBytes_;

      if(astTheSPIDevices[eController_].eState == SPISTATE_IDLE)
      {
         astTheSPIDevices[eController_].eState = SPISTATE_BUSY;
      }

      // Enable the Receive Not Empty Interrupt Enable bit
      astTheSPIDevices[eController_].pstRegisters->CR2 |= CR2_RXNEIE;

      return TRUE;
   }

   return FALSE;
}

// -------------------------------------------------------------
SPITransferStateEnum SPI_GetTransferState(
   SPIControllerEnum eController_)
{
   return astTheSPIDevices[eController_].eState;
}

// -------------------------------------------------------------
BOOL SPI_ConfigureAsInterrupt(
   SPIControllerEnum eController_)
{
   if(astTheSPIDevices[eController_].pstRegisters == NULL)
   {
      return FALSE;
   }

   IRQVectorEnum eIRQVector = IRQ_VECTOR_MAX;
   switch(eController_)
   {
      case SPI1:
      {
         eIRQVector = IRQ_VECTOR_SPI1;
         break;
      }
      case SPI2:
      {
         eIRQVector = IRQ_VECTOR_SPI2;
         break;
      }
      case SPI3:
      default:
         return FALSE;
   }

   astTheSPIDevices[eController_].eState = SPISTATE_IDLE;

   return NVIC_ConfigureInterrupt(eIRQVector, IRQ_PRIORITY_0, IRQ_ENABLE);
}
