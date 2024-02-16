// Redundancy Prevention --------------------------------------------------------------------------
#ifndef EXTI_DRIVER_H_
#define EXTI_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "driver/gpio/gpio_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
typedef enum
{
   EXTI_TRIGGER_RISE,
   EXTI_TRIGGER_FALL,
   EXTI_TRIGGER_BOTH,
   EXTI_TRIGGER_NONE
} EXTIModeEnum;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Initialize the EXTI controller.
// -------------------------------------------------------------
BOOL EXTI_Initialize();

// -------------------------------------------------------------
// Enable an EXTI interrupt for a GPIO pin.
// -------------------------------------------------------------
BOOL EXTI_EnableInterrupt(
   GPIOControllerEnum eController_,
   GPIOPinEnum ePin_,
   EXTIModeEnum eMode_);

// -------------------------------------------------------------
// Disable an EXTI interrupt for a GPIO pin.
// -------------------------------------------------------------
BOOL EXTI_DisableInterrupt(
   GPIOControllerEnum eController_,
   GPIOPinEnum ePin_);

#endif // EXTI_DRIVER_H_