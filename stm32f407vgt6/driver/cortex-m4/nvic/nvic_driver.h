// Redundancy Prevention --------------------------------------------------------------------------
#ifndef NVIC_DRIVER_H_
#define NVIC_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
#define MAX_IRQ_NUMBER     (81)
#define MIN_IRQ_NUMBER     (0)
#define NUM_IRQ_NUMBERS    (MAX_IRQ_NUMBER - MIN_IRQ_NUMBER + 1)
#define MAX_IRQ_PRIORITY   (0x0F)
#define MIN_IRQ_PRIORITY   (0x00)
#define IRQ_PRIORITY_BITS  (4)

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// IRQ Configuration Actions.
// -------------------------------------------------------------
typedef enum
{
   IRQ_ENABLE,
   IRQ_CLEAR
} IRQConfigActionEnum;

// -------------------------------------------------------------
// IRQ Priority Options.
// -------------------------------------------------------------
typedef enum
{
   IRQ_PRIORITY_0,
   IRQ_PRIORITY_1,
   IRQ_PRIORITY_2,
   IRQ_PRIORITY_3,
   IRQ_PRIORITY_4,
   IRQ_PRIORITY_5,
   IRQ_PRIORITY_6,
   IRQ_PRIORITY_7,
   IRQ_PRIORITY_8,
   IRQ_PRIORITY_9,
   IRQ_PRIORITY_10,
   IRQ_PRIORITY_11,
   IRQ_PRIORITY_12,
   IRQ_PRIORITY_13,
   IRQ_PRIORITY_14,
   IRQ_PRIORITY_15,
   IRQ_PRIORITY_MAX
} IRQPriorityEnum;

// -------------------------------------------------------------
// IRQ Vector Numbers.
// -------------------------------------------------------------
typedef enum
{
   IRQ_VECTOR_EXTI0 = 6,
   IRQ_VECTOR_EXTI1 = 7,
   IRQ_VECTOR_EXTI2 = 8,
   IRQ_VECTOR_EXTI3 = 9,
   IRQ_VECTOR_EXTI4 = 10,
   IRQ_VECTOR_MAX = 82
} IRQVectorEnum;

// Functions --------------------------------------------------------------------------------------
BOOL NVIC_Initialize();

// -------------------------------------------------------------
// Configure an interrupt via the Cortex-M4 NVIC.
// -------------------------------------------------------------
BOOL NVIC_ConfigureInterrupt(
   IRQVectorEnum eIRQNumber_,
   IRQPriorityEnum eIRQPriority_,
   IRQConfigActionEnum eAction_);

#endif // NVIC_DRIVER_H_
