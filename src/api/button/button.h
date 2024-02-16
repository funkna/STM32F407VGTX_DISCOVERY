// Redundancy Prevention --------------------------------------------------------------------------
#ifndef BUTTON_H_
#define BUTTON_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Button action enumerations.
// -------------------------------------------------------------
typedef enum
{
   BUTTON_PRESS,
   BUTTON_RELEASE,
   BUTTON_BOTH,
   BUTTON_NONE
} ButtonActionEnum;

// -------------------------------------------------------------
// Button type enumerations.
// -------------------------------------------------------------
typedef enum
{
   BUTTON_USER
} ButtonTypeEnum;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Initialize the Button API.
// -------------------------------------------------------------
BOOL Button_Initialize();

// -------------------------------------------------------------
// Configure the button to interrupt with a callback.
// -------------------------------------------------------------
BOOL Button_ConfigureAsInterrupt(
   ButtonActionEnum eAction_,
   void (*fpCallback_)(void));

// -------------------------------------------------------------
// Checks if a button currently pressed.
// -------------------------------------------------------------
BOOL Button_IsPressed();

#endif // BUTTON_H_
