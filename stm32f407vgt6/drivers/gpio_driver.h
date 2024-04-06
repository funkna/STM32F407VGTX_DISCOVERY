// Redundancy Prevention --------------------------------------------------------------------------
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "peripherals.h"

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
// GPIO Pin Mode
// -------------------------------------------------------------
typedef enum
{
   GPIOMODE_INPUT        = 0b00,
   GPIOMODE_GP_OUTPUT    = 0b01,
   GPIOMODE_ALT_FUNC     = 0b10,
   GPIOMODE_ANALOG       = 0b11
} GPIOPinModeEnum;

// -------------------------------------------------------------
// GPIO Output Type
// -------------------------------------------------------------
typedef enum
{
   GPIOTYPE_PUSHPULL   = 0b0,
   GPIOTYPE_OPENDRAIN  = 0b1
} GPIOOutputTypeEnum;

// -------------------------------------------------------------
// GPIO Speed
// -------------------------------------------------------------
typedef enum
{
   GPIOSPEED_LOW         = 0b00,
   GPIOSPEED_MED         = 0b01,
   GPIOSPEED_HI          = 0b10,
   GPIOSPEED_VHI         = 0b11
} GPIOSpeedEnum;

// -------------------------------------------------------------
// GPIO Pull-up/Pull-down
// -------------------------------------------------------------
typedef enum
{
   GPIOPUPD_NONE         = 0b00,
   GPIOPUPD_PU           = 0b01,
   GPIOPUPD_PD           = 0b10
} GPIOPUPDEnum;

// -------------------------------------------------------------
// GPIO Alternate Functions
// -------------------------------------------------------------
typedef enum
{
   GPIOALTFUNC_AF0       = 0x00,
   GPIOALTFUNC_AF1       = 0x01,
   GPIOALTFUNC_AF2       = 0x02,
   GPIOALTFUNC_AF3       = 0x03,
   GPIOALTFUNC_AF4       = 0x04,
   GPIOALTFUNC_AF5       = 0x05,
   GPIOALTFUNC_AF6       = 0x06,
   GPIOALTFUNC_AF7       = 0x07,
   GPIOALTFUNC_AF8       = 0x08,
   GPIOALTFUNC_AF9       = 0x09,
   GPIOALTFUNC_AF10      = 0x0A,
   GPIOALTFUNC_AF11      = 0x0B,
   GPIOALTFUNC_AF12      = 0x0C,
   GPIOALTFUNC_AF13      = 0x0D,
   GPIOALTFUNC_AF14      = 0x0E,
   GPIOALTFUNC_AF15      = 0x0F
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
} GPIOConfigurationStruct;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Inititalize a GPIO controller.
// -------------------------------------------------------------
BOOL GPIO_Initialize(
   GPIOPortEnum eGPIOPort_);

// -------------------------------------------------------------
// Reset a GPIO controller.
// -------------------------------------------------------------
BOOL GPIO_Reset(
   GPIOPortEnum eGPIOPort_);

// -------------------------------------------------------------
// Set the configuration for a GPIO port & pin.
// -------------------------------------------------------------
BOOL GPIO_SetConfig(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   const GPIOConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Get the configuration for a GPIO port & pin.
// -------------------------------------------------------------
GPIOConfigurationStruct* GPIO_GetConfig(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_);

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
