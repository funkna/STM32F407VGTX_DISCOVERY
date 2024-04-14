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
   I2CADDRLEN_7BIT = 0,
   I2CADDRLEN_10BIT
} I2CAddressLengthEnum;

typedef enum
{
   I2CADDRMODE_SINGLE = 0,
   I2CADDRMODE_DUAL
} I2CAddressModeEnum;

typedef struct
{
   I2CAddressLengthEnum eAddrLength;
   USHORT usAddress1;
   I2CAddressModeEnum eAddrMode;
   USHORT usAddress2;
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
