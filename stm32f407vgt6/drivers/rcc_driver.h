// Redundancy Prevention --------------------------------------------------------------------------
#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "peripherals.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
typedef enum
{
   CLKTYPE_PCLK1
} ClockTypeEnum;

typedef enum
{
   CLKSRC_HSI,
   CLKSRC_HSE,
   CLKSRC_PLL,
   CLKSRC_UNKNOWN
} ClockSourceEnum;

// Functions --------------------------------------------------------------------------------------

//--------------------------------------------------------------
// Initialize the RCC register structure
//--------------------------------------------------------------
BOOL RCC_Initialize();

//--------------------------------------------------------------
// Enable a peripheral clock
//--------------------------------------------------------------
BOOL RCC_EnablePeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_);

//--------------------------------------------------------------
// Reset a peripheral clock
//--------------------------------------------------------------
BOOL RCC_ResetPeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_);

//--------------------------------------------------------------
// What is the current clock source used for
//--------------------------------------------------------------
ClockSourceEnum RCC_GetSystemClockSource();

//--------------------------------------------------------------
// Get the frequency of a specific clock type
//--------------------------------------------------------------
ULONG RCC_GetClockFrequency(
   ClockTypeEnum eClockType_);

#endif // RCC_DRIVER_H_
