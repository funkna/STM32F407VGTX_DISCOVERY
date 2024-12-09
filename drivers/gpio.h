//------------------------------------------------------------------------------
//! \file gpio.h
//! \brief General Purpose Input/Output driver.
//! \ref docs\stm32f407_reference_manual.pdf section 8.
//------------------------------------------------------------------------------
#ifndef __GPIO_H
#define __GPIO_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief GPIO Register Bitmasks
//------------------------------------------------------------------------------
#define MODER_MASK      (0x03)
#define OTYPER_MASK     (0x01)
#define OSPEEDR_MASK    (0x03)
#define PUPDR_MASK      (0x03)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief GPIO Pin State
//------------------------------------------------------------------------------
typedef enum
{
   GPIO_LO = 0,
   GPIO_HI
} GPIOStateEnum;

//------------------------------------------------------------------------------
//! \brief GPIO Pin Mode
//------------------------------------------------------------------------------
typedef enum
{
   GPIOMODE_INPUT        = 0b00,
   GPIOMODE_GP_OUTPUT    = 0b01,
   GPIOMODE_ALT_FUNC     = 0b10,
   GPIOMODE_ANALOG       = 0b11
} GPIOPinModeEnum;

//------------------------------------------------------------------------------
//! \brief GPIO Output Type
//------------------------------------------------------------------------------
typedef enum
{
   GPIOTYPE_PUSHPULL   = 0b0,
   GPIOTYPE_OPENDRAIN  = 0b1
} GPIOOutputTypeEnum;

//------------------------------------------------------------------------------
//! \brief GPIO Speed
//------------------------------------------------------------------------------
typedef enum
{
   GPIOSPEED_LOW         = 0b00,
   GPIOSPEED_MED         = 0b01,
   GPIOSPEED_HI          = 0b10,
   GPIOSPEED_VHI         = 0b11
} GPIOSpeedEnum;

//------------------------------------------------------------------------------
//! \brief GPIO Pull-up/Pull-down
//------------------------------------------------------------------------------
typedef enum
{
   GPIOPUPD_NONE         = 0b00,
   GPIOPUPD_PU           = 0b01,
   GPIOPUPD_PD           = 0b10
} GPIOPUPDEnum;

//------------------------------------------------------------------------------
//! \brief GPIO Alternate Functions
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
//! \brief GPIO Pin Configuration Information
//------------------------------------------------------------------------------
typedef struct
{
   GPIOPinModeEnum eMode;
   GPIOOutputTypeEnum eOutputType;
   GPIOSpeedEnum eSpeed;
   GPIOPUPDEnum ePUPD;
   GPIOAltFuncEnum eAlternateFunction;
} GPIOConfigurationStruct;

//------------------------------------------------------------------------------
//! \brief GPIO Controller Register Structure
//------------------------------------------------------------------------------
typedef volatile struct
{
   UINT MODER;       // Mode
   UINT OTYPER;      // Output Type
   UINT OSPEEDR;     // Output Speed
   UINT PUPDR;       // Pull-Up/Pull-Down
   UINT IDR;         // Input Data
   UINT ODR;         // Output Data
   UINT BSRR;        // Bit Set/Reset
   UINT LCKR;        // Configuration Lock
   UINT AFRL;        // Alternate Function Low
   UINT AFRH;        // Alternate Function High
} GPIORegistersStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
BOOL GPIO_Initialize(GPIOPortEnum eGPIOPort_);
BOOL GPIO_Reset(GPIOPortEnum eGPIOPort_);
BOOL GPIO_SetConfig(GPIOPortEnum eGPIOPort_, GPIOPinEnum ePin_, const GPIOConfigurationStruct* pstConfiguration_);
GPIOConfigurationStruct* GPIO_GetConfig(GPIOPortEnum eGPIOPort_, GPIOPinEnum ePin_);
BOOL GPIO_ReadPin(GPIOPortEnum eGPIOPort_, GPIOPinEnum ePin_, GPIOStateEnum* peState_);
BOOL GPIO_WritePin(GPIOPortEnum eGPIOPort_, GPIOPinEnum ePin_, GPIOStateEnum eState_);
BOOL GPIO_TogglePin(GPIOPortEnum eGPIOPort_, GPIOPinEnum ePin_);

#endif // __GPIO_H



