// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SYSCFG_DRIVER_H_
#define SYSCFG_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "drivers/gpio_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Initialize the SYSCFG controller
// -------------------------------------------------------------
BOOL SYSCFG_Initialize();

// -------------------------------------------------------------
// Reset the SYSCFG controller
// -------------------------------------------------------------
BOOL SYSCFG_Reset();

// -------------------------------------------------------------
// Configure a GPIO port & pin as an external interrupt
// -------------------------------------------------------------
BOOL SYSCFG_ConfigureEXTI(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_);

#endif // SYSCFG_DRIVER_H_
