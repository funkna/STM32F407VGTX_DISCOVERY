//------------------------------------------------------------------------------
//! \file spi.h
//! \brief Serial Peripheral Interface driver.
//! \ref docs\stm32f407_reference_manual.pdf section 28.
//------------------------------------------------------------------------------
#ifndef __SPI_H
#define __SPI_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "types.h"
#include "nvic.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief SPI Controller Register Bitmasks
//------------------------------------------------------------------------------
#define CR1_BIDIMODE          (0x01UL << 15) // Bidirectional data mode enable
#define CR1_BIDIOE            (0x01UL << 14) // Output enable in bidirectional mode
#define CR1_CRCEN             (0x01UL << 13) // Hardware CRC calculation enable
#define CR1_CRCNEXT           (0x01UL << 12) // CRC transfer next
#define CR1_DFF               (0x01UL << 11) // Data frame format
#define CR1_RXONLY            (0x01UL << 10) // Receive only
#define CR1_SSM               (0x01UL << 9)  // Software slave management
#define CR1_SSI               (0x01UL << 8)  // Internal slave select
#define CR1_LSBFIRST          (0x01UL << 7)  // Frame format
#define CR1_SPE               (0x01UL << 6)  // SPI enable
#define CR1_BR_OFFSET         (3)
#define CR1_BR                (0x07UL << CR1_BR_OFFSET)  // Baud rate control
#define CR1_MSTR              (0x01UL << 2)  // Master selection
#define CR1_CPOL              (0x01UL << 1)  // Clock polarity
#define CR1_CPHA              (0x01UL << 0)  // Clock phase
#define CR2_TXEIE             (0x01UL << 7)  // Tx buffer empty interrupt enable
#define CR2_RXNEIE            (0x01UL << 6)  // Rx buffer empty interrupt enable
#define CR2_ERRIE             (0x01UL << 5)  // Error interrupt enable
#define CR2_FRF               (0x01UL << 4)  // Frame format
#define CR2_SSOE              (0x01UL << 2)  // SS output enable
#define CR2_TXDMAEN           (0x01UL << 1)  // Tx buffer DMA enable
#define CR2_RXDMAEN           (0x01UL << 0)  // Rx buffer DMA enable
#define SR_FRE                (0x01UL << 8)  // Frame format error
#define SR_BSY                (0x01UL << 7)  // Busy flag
#define SR_OVR                (0x01UL << 6)  // Overrun flag
#define SR_MODF               (0x01UL << 5)  // Mode fault
#define SR_CRCERR             (0x01UL << 4)  // CRC error flag
#define SR_UDR                (0x01UL << 3)  // Underrun flag
#define SR_CHSIDE             (0x01UL << 2)  // Channel side
#define SR_TXE                (0x01UL << 1)  // Transmit buffer empty
#define SR_RXNE               (0x01UL << 0)  // Receive buffer not empty

#define CR1_BR_PCLK_DIV2      (0b000UL)
#define CR1_BR_PCLK_DIV4      (0b001UL)
#define CR1_BR_PCLK_DIV8      (0b010UL)
#define CR1_BR_PCLK_DIV16     (0b011UL)
#define CR1_BR_PCLK_DIV32     (0b100UL)
#define CR1_BR_PCLK_DIV64     (0b101UL)
#define CR1_BR_PCLK_DIV128    (0b110UL)
#define CR1_BR_PCLK_DIV256    (0b111UL)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief SPI Controller Mode
//------------------------------------------------------------------------------
typedef enum
{
   SPIMODE_SLAVE = 0,
   SPIMODE_MASTER
} SPIModeEnum;

//------------------------------------------------------------------------------
//! \brief SPI Bus Config
//------------------------------------------------------------------------------
typedef enum
{
   SPIBUS_FULL_DUPLEX = 0,
   SPIBUS_HALF_DUPLEX,
   SPIBUS_SIMPLEX_RX
} SPIBusConfigEnum;

//------------------------------------------------------------------------------
//! \brief SPI Clock Prescaler
//------------------------------------------------------------------------------
typedef enum
{
   SPICLK_PRESCALERDIV_2 = 0,
   SPICLK_PRESCALERDIV_4,
   SPICLK_PRESCALERDIV_8,
   SPICLK_PRESCALERDIV_16,
   SPICLK_PRESCALERDIV_32,
   SPICLK_PRESCALERDIV_64,
   SPICLK_PRESCALERDIV_128,
   SPICLK_PRESCALERDIV_256
} SPIClockPrescalerEnum;

//------------------------------------------------------------------------------
//! \brief SPI Clock Polarity
//------------------------------------------------------------------------------
typedef enum
{
   SPICPOL_IDLE_LO = 0,
   SPICPOL_IDLE_HI
} SPIClockPolarityEnum;

//------------------------------------------------------------------------------
//! \brief SPI Clock Phase
//------------------------------------------------------------------------------
typedef enum
{
   SPICPHA_RISE = 0,
   SPICPHA_FALL
} SPIClockPhaseEnum;

//------------------------------------------------------------------------------
//! \brief SPI Data Frame Size
//------------------------------------------------------------------------------
typedef enum
{
   SPIDFF_8BITS = 0,
   SPIDFF_16BITS
} SPIDataFrameSizeEnum;

//------------------------------------------------------------------------------
//! \brief SPI Software Slave Management
//------------------------------------------------------------------------------
typedef enum
{
   SPISSM_DISABLE = 0,
   SPISSM_ENABLE
} SPISoftwareSlaveManagementEnum;

//------------------------------------------------------------------------------
//! \brief SPI Slave Select Interval
//------------------------------------------------------------------------------
typedef enum
{
   SPISSI_DISABLE = 0,
   SPISSI_ENABLE
} SPISlaveSelectInternalEnum;

//------------------------------------------------------------------------------
//! \brief SPI Multi-master Mode
//------------------------------------------------------------------------------
typedef enum
{
   SPIMULTIMASTER_DISABLE = 0,
   SPIMULTIMASTER_ENABLE
} SPIMultiMasterEnum;

//------------------------------------------------------------------------------
//! \brief SPI Controller Configuration
//------------------------------------------------------------------------------
typedef struct
{
   SPIModeEnum eMode;
   SPIBusConfigEnum eBusConfig;
   SPIClockPrescalerEnum eClockPrescalar;
   SPIClockPolarityEnum eClockPolarity;
   SPIClockPhaseEnum eClockPhase;
   SPIDataFrameSizeEnum eDataFrameSize;
   SPISoftwareSlaveManagementEnum eSlaveManagement;
   SPISlaveSelectInternalEnum eInternalSelect;
   SPIMultiMasterEnum eMultiMaster;
} SPIConfigurationStruct;

//------------------------------------------------------------------------------
//! \brief SPI Trnasfer State
//------------------------------------------------------------------------------
typedef enum
{
   SPISTATE_IDLE = 0x00,
   SPISTATE_TX_BUSY = 0x01,
   SPISTATE_RX_BUSY = 0x02,
   SPISTATE_ERROR = 0x04
} SPITransferStateEnum;

//------------------------------------------------------------------------------
//! \brief SPI Controller Register Structure
//------------------------------------------------------------------------------
typedef volatile struct
{
   UINT CR1;         // Control (Not used in I2S mode)
   UINT CR2;         // Control
   UINT SR;          // Status
   UINT DR;          // Data
   UINT CRCPR;       // CRC polynomial
   UINT RXCRCR;      // RX CRC
   UINT TXCRCR;      // TX CRC
   UINT I2SCFGR;     // I2S configuration
   UINT I2SPR;       // I2S prescalar
} SPIRegistersStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
BOOL SPI_Initialize(SPIControllerEnum eController_);
BOOL SPI_Reset(SPIControllerEnum eController_);
BOOL SPI_SetConfig(SPIControllerEnum eController_, const SPIConfigurationStruct* pstConfiguration_);
SPIConfigurationStruct* SPI_GetConfig(SPIControllerEnum eController_);
BOOL SPI_Enable(SPIControllerEnum eController_);
BOOL SPI_Disable(SPIControllerEnum eController_);
BOOL SPI_ReadByte(SPIControllerEnum eController_, UCHAR* pucData_);
BOOL SPI_WriteByte(SPIControllerEnum eController_, UCHAR ucData_);
BOOL SPI_Transfer(SPIControllerEnum eController_, UCHAR* pucReceiveBuffer_, UINT uiRequestedBytes_, UCHAR* pucTransmitBuffer_, UINT uiDispatchedBytes_);
SPITransferStateEnum SPI_GetStates(SPIControllerEnum eController_);
BOOL SPI_ConfigureAsInterrupt(SPIControllerEnum eController_);

#endif // __SPI_H
