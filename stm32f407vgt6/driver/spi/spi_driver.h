// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "device/peripherals.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

typedef enum
{
   SPIMODE_SLAVE = 0,
   SPIMODE_MASTER
} SPIModeEnum;

typedef enum
{
   SPIBUS_FULL_DUPLEX = 0,
   SPIBUS_HALF_DUPLEX,
   SPIBUS_SIMPLEX_RX
} SPIBusConfigEnum;

typedef enum
{
   SPICLK_PRESCALARDIV_2 = 0,
   SPICLK_PRESCALARDIV_4,
   SPICLK_PRESCALARDIV_8,
   SPICLK_PRESCALARDIV_16,
   SPICLK_PRESCALARDIV_32,
   SPICLK_PRESCALARDIV_64,
   SPICLK_PRESCALARDIV_128,
   SPICLK_PRESCALARDIV_256
} SPIClockPrescalarEnum;

typedef enum
{
   SPICPOL_IDLE_LO = 0,
   SPICPOL_IDLE_HI
} SPIClockPolarityEnum;

typedef enum
{
   SPICPHA_RISE = 0,
   SPICPHA_FALL
} SPIClockPhaseEnum;

typedef enum
{
   SPIDFF_8BITS = 0,
   SPIDFF_16BITS
} SPIDataFrameSizeEnum;

typedef enum
{
   SPISSM_DISABLE = 0,
   SPISSM_ENABLE
} SPISoftwareSlaveManagementEnum;

typedef enum
{
   SPISSI_DISABLE = 0,
   SPISSI_ENABLE
} SPISlaveSelectInternalEnum;

typedef enum
{
   SPIMULTIMASTER_DISABLE = 0,
   SPIMULTIMASTER_ENABLE
} SPIMultiMasterEnum;

typedef struct
{
   SPIModeEnum eMode;
   SPIBusConfigEnum eBusConfig;
   SPIClockPrescalarEnum eClockPrescalar;
   SPIClockPolarityEnum eClockPolarity;
   SPIClockPhaseEnum eClockPhase;
   SPIDataFrameSizeEnum eDataFrameSize;
   SPISoftwareSlaveManagementEnum eSlaveManagement;
   SPISlaveSelectInternalEnum eInternalSelect;
   SPIMultiMasterEnum eMultiMaster;
} SPIConfigurationStruct;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Inititalize a SPI controller.
// -------------------------------------------------------------
BOOL SPI_Initialize(
   SPIControllerEnum eController_);

// -------------------------------------------------------------
// Deinititalize a SPI controller.
// -------------------------------------------------------------
BOOL SPI_Deinitialize(
   SPIControllerEnum eController_);

// -------------------------------------------------------------
// Set configurations for a SPI controller.
// -------------------------------------------------------------
BOOL SPI_SetConfig(
   SPIControllerEnum eController_,
   const SPIConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Get configurations for a SPI controller.
// -------------------------------------------------------------
BOOL SPI_GetConfig(
   SPIControllerEnum eController_,
   SPIConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Enable a SPI controller.
// -------------------------------------------------------------
BOOL SPI_Enable(
   SPIControllerEnum eController_);

// -------------------------------------------------------------
// Disable a SPI controller.
// -------------------------------------------------------------
BOOL SPI_Disable(
   SPIControllerEnum eController_);

// -------------------------------------------------------------
// Read data from the SPI bus.
// -------------------------------------------------------------
BOOL SPI_Read(
   SPIControllerEnum eController_,
   UCHAR* pucData_);

// -------------------------------------------------------------
// Write data to the SPI bus.
// -------------------------------------------------------------
BOOL SPI_Write(
   SPIControllerEnum eController_,
   UCHAR ucData_);

#endif // SPI_DRIVER_H_