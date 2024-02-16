// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SYSCFG_H_
#define SYSCFG_H_

// Includes ---------------------------------------------------------------------------------------
#include "../stm32f407vgt6.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

// -------------------------------------------------------------
// SYSCFG Controller Register Bitmasks
// -------------------------------------------------------------
// #define MEMRMP
// #define PMC
#define EXTICR1_EXTI3         (0x0FUL << 12)
#define EXTICR1_EXTI2         (0x0FUL << 8)
#define EXTICR1_EXTI1         (0x0FUL << 4)
#define EXTICR1_EXTI0         (0x0FUL << 0)
#define EXTICR2_EXTI7         (0x0FUL << 12)
#define EXTICR2_EXTI6         (0x0FUL << 8)
#define EXTICR2_EXTI5         (0x0FUL << 4)
#define EXTICR2_EXTI4         (0x0FUL << 0)
#define EXTICR3_EXTI11        (0x0FUL << 12)
#define EXTICR3_EXTI10        (0x0FUL << 8)
#define EXTICR3_EXTI9         (0x0FUL << 4)
#define EXTICR3_EXTI8         (0x0FUL << 0)
#define EXTICR4_EXTI15        (0x0FUL << 12)
#define EXTICR4_EXTI14        (0x0FUL << 8)
#define EXTICR4_EXTI13        (0x0FUL << 4)
#define EXTICR4_EXTI12        (0x0FUL << 0)
// #define EXTICR

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// SYSCFG Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT MEMRMP;
   UINT PMC;
   UINT EXTICR1;
   UINT EXTICR2;
   UINT EXTICR3;
   UINT EXTICR4;
   UINT RESERVED[2];
   UINT CMPCR;
} SYSCFGRegistersStruct;

// Functions --------------------------------------------------------------------------------------
SYSCFGRegistersStruct* GetSYSCFGController()
{
   return (SYSCFGRegistersStruct*)PERIPHERAL_ADDRESS_RCC;
}

#endif // SYSCFG_H_
