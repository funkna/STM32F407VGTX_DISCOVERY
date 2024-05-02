// Redundancy Prevention --------------------------------------------------------------------------
#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "peripherals.h"

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

#endif // I2C_DRIVER_H_
