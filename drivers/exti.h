//------------------------------------------------------------------------------
//! \file exti.h
//! \brief External Interrupt/Event Controller driver.
//! \ref docs\stm32f407_reference_manual.pdf section 12.2.
//------------------------------------------------------------------------------
#ifndef __EXTI_H
#define __EXTI_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "gpio.h"
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief EXTI Controller Register Structure
//------------------------------------------------------------------------------
typedef volatile struct
{
   UINT IMR;         // Interrupt mask
   UINT EMR;         // Event mask
   UINT RTSR;        // Rising trigger selection
   UINT FTSR;        // Falling trigger selection
   UINT SWIER;       // Software interrupt event
   UINT PR;          // Pending
} EXTIRegistersStruct;

//------------------------------------------------------------------------------
//! \brief External Interrupt Trigger
//------------------------------------------------------------------------------
typedef enum
{
   EXTI_TRIGGER_RISE,
   EXTI_TRIGGER_FALL,
   EXTI_TRIGGER_BOTH,
   EXTI_TRIGGER_NONE
} EXTITriggerEnum;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
void EXTI_Initialize();
BOOL EXTI_EnableInterrupt(GPIOPortEnum eController_, GPIOPinEnum ePin_, EXTITriggerEnum eMode_);
BOOL EXTI_DisableInterrupt(GPIOPortEnum eController_, GPIOPinEnum ePin_);
void EXTI_ClearPendingInterrupt(GPIOPinEnum ePin_);


#endif // __EXTI_H
