// Redundancy Prevention --------------------------------------------------------------------------
#ifndef EXTI_H_
#define EXTI_H_

// Includes ---------------------------------------------------------------------------------------
#include "../stm32f407vgt6.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

//--------------------------------------------------------------
// EXTI Controller Register Bitmasks (All registers map *Rxx bits.)
//--------------------------------------------------------------
#define R22        (0x01UL << 22)
#define R21        (0x01UL << 21)
#define R20        (0x01UL << 20)
#define R19        (0x01UL << 19)
#define R18        (0x01UL << 18)
#define R17        (0x01UL << 17)
#define R16        (0x01UL << 16)
#define R15        (0x01UL << 15)
#define R14        (0x01UL << 14)
#define R13        (0x01UL << 13)
#define R12        (0x01UL << 12)
#define R11        (0x01UL << 11)
#define R10        (0x01UL << 10)
#define R09        (0x01UL << 9)
#define R08        (0x01UL << 8)
#define R07        (0x01UL << 7)
#define R06        (0x01UL << 6)
#define R05        (0x01UL << 5)
#define R04        (0x01UL << 4)
#define R03        (0x01UL << 3)
#define R03        (0x01UL << 3)
#define R02        (0x01UL << 2)
#define R01        (0x01UL << 1)
#define R00        (0x01UL << 0)

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
