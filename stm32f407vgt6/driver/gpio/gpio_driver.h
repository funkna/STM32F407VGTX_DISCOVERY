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
// GPIO Alternate Functions
// -------------------------------------------------------------
typedef enum
{
   ALTFUNC_AF0       = 0x00,
   ALTFUNC_AF1       = 0x01,
   ALTFUNC_AF2       = 0x02,
   ALTFUNC_AF3       = 0x03,
   ALTFUNC_AF4       = 0x04,
   ALTFUNC_AF5       = 0x05,
   ALTFUNC_AF6       = 0x06,
   ALTFUNC_AF7       = 0x07,
   ALTFUNC_AF8       = 0x08,
   ALTFUNC_AF9       = 0x09,
   ALTFUNC_AF10      = 0x0A,
   ALTFUNC_AF11      = 0x0B,
   ALTFUNC_AF12      = 0x0C,
   ALTFUNC_AF13      = 0x0D,
   ALTFUNC_AF14      = 0x0E,
   ALTFUNC_AF15      = 0x0F
} GPIOAltFuncEnum;

// -------------------------------------------------------------
// GPIO Pin Configuration Information
// -------------------------------------------------------------
typedef struct
{
   GPIOPinModeEnum eMode;
   GPIOOutputTypeEnum eOutputType;
   GPIOSpeedEnum eSpeed;
   GPIOPUPDEnum ePUPD;
   GPIOAltFuncEnum eAlternateFunction;
} GPIOPinConfigurationStruct;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Inititalize a GPIO Port.
// -------------------------------------------------------------
BOOL GPIO_Initialize(
   GPIOPortEnum eGPIOPort_);

// -------------------------------------------------------------
// Deinititalize a GPIO Port.
// -------------------------------------------------------------
BOOL GPIO_Deinitialize(
   GPIOPortEnum eGPIOPort_);

// -------------------------------------------------------------
// Set configurations for a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_SetConfig(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   const GPIOPinConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Get configurations for a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_GetConfig(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   GPIOPinConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Read a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_ReadPin(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   GPIOStateEnum* peState_);

// -------------------------------------------------------------
// Write to a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_WritePin(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   GPIOStateEnum eState_);

// -------------------------------------------------------------
// Toggle a GPIO pin.
// -------------------------------------------------------------
BOOL GPIO_TogglePin(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_);

#endif // GPIO_DRIVER_H_
