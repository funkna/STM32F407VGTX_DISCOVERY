//------------------------------------------------------------------------------
//! \file syscfg.c
//! \brief Reset and Clock Control driver implementation.
//------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "syscfg.h"
#include "rcc.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static SYSCFGRegistersStruct* pstTheSYSCFGRegisters = NULL;

//------------------------------------------------------------------------------
void
SYSCFG_Initialize()
{
   pstTheSYSCFGRegisters = (SYSCFGRegistersStruct*)PERIPHERAL_ADDRESS_SYSCFG;
   (void)RCC_EnablePeripheralClock(PERIPHERAL_SYSCFG);
}

//------------------------------------------------------------------------------
void
SYSCFG_Reset()
{
   (void)RCC_ResetPeripheralClock(PERIPHERAL_SYSCFG);
}

//------------------------------------------------------------------------------
BOOL
SYSCFG_ConfigureEXTI(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   UCHAR ucSYSCFGControlRegisterIndex = (ePin_ / NUM_SYSCFG_EXTICR);
   UCHAR ucEXTIPort = (ePort_ & ((0x01 << NUM_SYSCFG_EXTICR) - 1));

   if((ucSYSCFGControlRegisterIndex < NUM_SYSCFG_EXTICR) &&
      (ucEXTIPort < GPIO_PORT_MAX))
   {
      pstTheSYSCFGRegisters->EXTICR[ucSYSCFGControlRegisterIndex] |= (ucEXTIPort << (ucEXTIPort % NUM_SYSCFG_EXTICR));
      return TRUE;
   }

   return FALSE;
}
