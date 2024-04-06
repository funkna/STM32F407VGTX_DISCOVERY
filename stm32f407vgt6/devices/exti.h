// Redundancy Prevention --------------------------------------------------------------------------
#ifndef EXTI_H_
#define EXTI_H_

// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "peripherals.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

//--------------------------------------------------------------
// EXTI Controller Register Structure
//--------------------------------------------------------------
typedef volatile struct
{
   UINT IMR;         // Interrupt mask
   UINT EMR;         // Event mask
   UINT RTSR;        // Rising trigger selection
   UINT FTSR;        // Falling trigger selection
   UINT SWIER;       // Software interrupt event
   UINT PR;          // Pending
} EXTIRegistersStruct;

// Functions --------------------------------------------------------------------------------------
EXTIRegistersStruct* GetEXTIController()
{
   return (EXTIRegistersStruct*)PERIPHERAL_ADDRESS_EXTI;
}

#endif // EXTI_H_
