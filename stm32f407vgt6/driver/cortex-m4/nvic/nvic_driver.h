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
typedef enum
{
   IRQ_ENABLE,
   IRQ_CLEAR
} IRQConfigActionEnum;

// Functions --------------------------------------------------------------------------------------
BOOL NVIC_Initialize();

BOOL NVIC_ConfigureInterrupt(
   UCHAR ucIRQNumber_,
   UCHAR ucIRQPriority_,
   IRQConfigActionEnum eAction_);
#endif // NVIC_DRIVER_H_
