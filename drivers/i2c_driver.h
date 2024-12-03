// Redundancy Prevention --------------------------------------------------------------------------
#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "stm32f407vgt6.h"

// Defines ----------------------------------------------------------------------------------------
#define I2C1_DEVICE_ADDRESS   (0x61)
#define I2C2_DEVICE_ADDRESS   (0x62)
#define I2C3_DEVICE_ADDRESS   (0x63)

// Typedefs ---------------------------------------------------------------------------------------

typedef enum
{
   I2CMODE_MASTER = 0,
   I2CMODE_SLAVE
} I2CModeEnum;

typedef enum
{
   I2CACK_DISABLE = 0,
   I2CACK_ENABLE
} I2CAcknowledgeModeEnum;

typedef enum
{
   I2CDUTY_NONE = 0,
   I2CDUTY_2 = I2CDUTY_NONE,
   I2CDUTY_16_9,
} I2CDutyCycleEnum;

typedef enum
{
   I2CCLK_SM_100KHZ = 0,
   I2CCLK_FM_200KHZ
} I2CClockSpeedEnum;

typedef struct
{
   UCHAR ucAddress;
   I2CAcknowledgeModeEnum eAckMode;
   I2CDutyCycleEnum eDutyCycle;
   I2CClockSpeedEnum eClockSpeed;
} I2CConfigurationStruct;

typedef enum
{
   I2CTRANSFER_WRITE = 0,
   I2CTRANSFER_READ
} I2CTransferTypeEnum;

typedef enum
{
   I2CSTATE_IDLE = 0,
   I2CSTATE_BEGIN,
   I2CSTATE_START_SENT,
   I2CSTATE_IN_PROGRESS,
   I2CSTATE_DATA_SENT,
   I2CSTATE_ERROR
} I2CTransferStateEnum;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Inititalize an I2C controller.
// -------------------------------------------------------------
BOOL I2C_Initialize(
   I2CControllerEnum eController_);

// -------------------------------------------------------------
// Reset an I2C controller.
// -------------------------------------------------------------
BOOL I2C_Reset(
   I2CControllerEnum eController_);

// -------------------------------------------------------------
// Set configuration for a I2C controller.
// -------------------------------------------------------------
BOOL I2C_SetConfig(
   I2CControllerEnum eController_,
   const I2CConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Get configuration for a I2C controller.
// -------------------------------------------------------------
I2CConfigurationStruct* I2C_GetConfig(
   I2CControllerEnum eController_);

// -------------------------------------------------------------
// Enable a I2C controller.
// -------------------------------------------------------------
BOOL I2C_Enable(
   I2CControllerEnum eController_);

// -------------------------------------------------------------
// Disable a I2C controller.
// -------------------------------------------------------------
BOOL I2C_Disable(
   I2CControllerEnum eController_);

// -------------------------------------------------------------
// Write data to the I2C lines
// -------------------------------------------------------------
BOOL I2C_WriteData(
   I2CControllerEnum eController_,
   I2CModeEnum eMode_,
   UCHAR ucAddress_,
   UCHAR* pucData_,
   UINT uiLength_);

// -------------------------------------------------------------
// Read data from the I2C lines
// -------------------------------------------------------------
BOOL I2C_ReadData(
   I2CControllerEnum eController_,
   I2CModeEnum eMode_,
   UCHAR ucAddress_,
   UCHAR* pucCommand_,
   UINT uiCommandLength_,
   UCHAR* pucData_,
   UINT uiLength_);

// -------------------------------------------------------------
// Start a transfer on the I2C bus.
// -------------------------------------------------------------
BOOL I2C_MasterTransfer(
   I2CControllerEnum eController_,
   I2CTransferTypeEnum eTransferType_,
   UCHAR ucAddress_,
   UCHAR* pucBuffer_,
   UINT uiSize_);

// -------------------------------------------------------------
// Get the transfer state of an I2C controller.
// -------------------------------------------------------------
I2CTransferStateEnum I2C_GetState(
   I2CControllerEnum eController_);

// -------------------------------------------------------------
// Enable an interrupt vector for an I2C controller.
// -------------------------------------------------------------
BOOL I2C_ConfigureAsInterrupt(
   I2CControllerEnum eController_);

#endif // I2C_DRIVER_H_
