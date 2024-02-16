// Redundancy Prevention --------------------------------------------------------------------------
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "device/peripherals.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// GPIO Pin State
// -------------------------------------------------------------
typedef enum
{
   GPIO_LO = 0,
   GPIO_HI
} GPIOStateEnum;

// -------------------------------------------------------------
// GPIO Pins
// -------------------------------------------------------------
typedef enum
{
   GPIO_PIN_0 = 0,
   GPIO_PIN_1,
   GPIO_PIN_2,
   GPIO_PIN_3,
   GPIO_PIN_4,
   GPIO_PIN_5,
   GPIO_PIN_6,
   GPIO_PIN_7,
   GPIO_PIN_8,
   GPIO_PIN_9,
   GPIO_PIN_10,
   GPIO_PIN_11,
   GPIO_PIN_12,
   GPIO_PIN_13,
   GPIO_PIN_14,
   GPIO_PIN_15,
   GPIO_PIN_MAX,
   GPIO_PIN_NONE= 0xFFFFFFFF
} GPIOPinEnum;

// -------------------------------------------------------------
// GPIO Pin Mode
// -------------------------------------------------------------
typedef enum
{
   MODE_INPUT        = 0b00,
   MODE_GP_OUTPUT    = 0b01,
   MODE_ALT_FUNC     = 0b10,
   MODE_ANALOG       = 0b11
} GPIOPinModeEnum;

// -------------------------------------------------------------
// GPIO Output Type
// -------------------------------------------------------------
typedef enum
{
   OUTPUT_PUSHPULL   = 0b0,
   OUTPUT_OPENDRAIN  = 0b1
} GPIOOutputTypeEnum;

// -------------------------------------------------------------
// GPIO Speed
// -------------------------------------------------------------
typedef enum
{
   SPEED_LOW         = 0b00,
   SPEED_MED         = 0b01,
   SPEED_HI          = 0b10,
   SPEED_VHI         = 0b11
} GPIOSpeedEnum;

// -------------------------------------------------------------
// GPIO Pull-up/Pull-down
// -------------------------------------------------------------
typedef enum
{
   PUPD_NONE         = 0b00,
   PUPD_PU           = 0b01,
   PUPD_PD           = 0b10
} GPIOPUPDEnum;

// -------------------------------------------------------------
// GPIO Pin Configuration Information
// -------------------------------------------------------------
typedef struct
{
   GPIOPinModeEnum eMode;
   GPIOOutputTypeEnum eOutputType;
   GPIOSpeedEnum eSpeed;
   GPIOPUPDEnum ePUPD;
} GPIOPinConfigurationStruct;

// -------------------------------------------------------------
// GPIO Port has 16 pins, so USHORT will suffice.
// -------------------------------------------------------------
// typedef USHORT GPIOPortState;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Inititalize a GPIO controller.
// -------------------------------------------------------------
BOOL GPIO_Initialize(
   GPIOControllerEnum eGPIOController_);

// -------------------------------------------------------------
// Deinititalize a GPIO controller.
// -------------------------------------------------------------
BOOL GPIO_Deinitialize(
   GPIOControllerEnum eGPIOController_);

// -------------------------------------------------------------
// Set/Get configurations for a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_SetConfig(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   const GPIOPinConfigurationStruct* pstConfiguration_);
// -------------------------------------------------------------
BOOL GPIO_GetConfig(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPinConfigurationStruct* pstConfiguration_);
// -------------------------------------------------------------
BOOL GPIO_SetConfigPinMode(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPinModeEnum eMode_);
// -------------------------------------------------------------
BOOL GPIO_GetConfigPinMode(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPinModeEnum* peMode_);
// -------------------------------------------------------------
BOOL GPIO_SetConfigPinOutputType(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOOutputTypeEnum eOutputType_);
// -------------------------------------------------------------
BOOL GPIO_GetConfigPinOutputType(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOOutputTypeEnum* peOutputType_);
// -------------------------------------------------------------
BOOL GPIO_SetConfigPinSpeed(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOSpeedEnum eSpeed_);
// -------------------------------------------------------------
BOOL GPIO_GetConfigPinSpeed(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOSpeedEnum* peSpeed_);
// -------------------------------------------------------------
BOOL GPIO_SetConfigPinPUPD(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPUPDEnum ePUPD_);
// -------------------------------------------------------------
BOOL GPIO_GetConfigPinPUPD(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPUPDEnum* pePUPD_);

// -------------------------------------------------------------
// Read a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_ReadPin(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOStateEnum* peState_);

// -------------------------------------------------------------
// Read a port of GPIO pins.
// -------------------------------------------------------------
// BOOL GPIO_ReadPort(
//    GPIOControllerEnum eGPIOController_,
//    GPIOPortState* pusPort_);

// -------------------------------------------------------------
// Write to a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_WritePin(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOStateEnum eState_);

// -------------------------------------------------------------
// Write to a port of GPIO pins.
// -------------------------------------------------------------
// BOOL GPIO_WritePort(
//    GPIOControllerEnum eGPIOController_,
//    GPIOPortState usPort_);

// -------------------------------------------------------------
// Toggle a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_TogglePin(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_);

// -------------------------------------------------------------
// Toggle a port of GPIO pins.
// -------------------------------------------------------------
// BOOL GPIO_TogglePort(
//    GPIOControllerEnum eGPIOController_);

#endif // GPIO_DRIVER_H_
