// Redundancy Prevention --------------------------------------------------------------------------
#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "device/peripherals.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Functions --------------------------------------------------------------------------------------
BOOL RCC_Initialize();

BOOL RCC_EnablePeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_);

BOOL RCC_ResetPeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_);

#endif // RCC_DRIVER_H_
