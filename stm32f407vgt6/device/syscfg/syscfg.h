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

#define EXTI_PIN_PORT_A       (0x00)
#define EXTI_PIN_PORT_B       (0x01)
#define EXTI_PIN_PORT_C       (0x02)
#define EXTI_PIN_PORT_D       (0x03)
#define EXTI_PIN_PORT_E       (0x04)
#define EXTI_PIN_PORT_F       (0x05)
#define EXTI_PIN_PORT_G       (0x06)
#define EXTI_PIN_PORT_H       (0x07)
#define EXTI_PIN_PORT_I       (0x08)
#define EXTI_PIN_PORT_J       (0x09)
#define EXTI_PIN_PORT_K       (0x0A)

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
   UINT EXTICR;
} SYSCFGRegistersStruct;

// Functions --------------------------------------------------------------------------------------

// Singleton instance(s) for SYSCFG controller(s)
static SYSCFGRegistersStruct* pstTheSYSCFGController = NULL;
SYSCFGRegistersStruct* GetSYSCFGController()
{
   if(pstTheSYSCFGController == NULL)
   {
      pstTheSYSCFGController = (SYSCFGRegistersStruct*)PERIPHERAL_ADDRESS_RCC;
   }

   return pstTheSYSCFGController;
}

#endif // SYSCFG_H_
