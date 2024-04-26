// Redundancy Prevention --------------------------------------------------------------------------
#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "peripherals.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

typedef enum
{
   I2CACK_DISABLE = 0,
   I2CACK_ENABLE
} I2CAcknowledgeModeEnum;

typedef enum
{
   I2CDUTY_2 = 0,
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

#endif // I2C_DRIVER_H_
