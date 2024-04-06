// Includes ---------------------------------------------------------------------------------------
#include "peripherals.h"
#include "devices/syscfg.h"
#include "drivers/rcc_driver.h"
#include "drivers/syscfg_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static SYSCFGRegistersStruct* pstTheSYSCFGRegisters = NULL;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
BOOL SYSCFG_Initialize()
{
   pstTheSYSCFGRegisters = GetSYSCFGController();

   BOOL bSuccess = FALSE;
   if(pstTheSYSCFGRegisters != NULL)
   {
      bSuccess = RCC_EnablePeripheralClock(PERIPHERAL_SYSCFG);
   }
   return bSuccess;
}

// -------------------------------------------------------------
BOOL SYSCFG_Reset()
{
   return RCC_ResetPeripheralClock(PERIPHERAL_SYSCFG);
}

// -------------------------------------------------------------
BOOL SYSCFG_ConfigureEXTI(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   if(pstTheSYSCFGRegisters == NULL)
   {
      return FALSE;
   }

   UCHAR ucSYSCFGControlRegisterIndex = (ePin_ / NUM_SYSCFG_EXTICR);
   UCHAR ucEXTIPort = (ePort_ & ((0x01 << NUM_SYSCFG_EXTICR) - 1));

   BOOL bSuccess = FALSE;
   if((ucSYSCFGControlRegisterIndex < NUM_SYSCFG_EXTICR) &&
      (ucEXTIPort < GPIO_PORT_MAX))
   {
      bSuccess = TRUE;
      pstTheSYSCFGRegisters->EXTICR[ucSYSCFGControlRegisterIndex] |= (ucEXTIPort << (ucEXTIPort % NUM_SYSCFG_EXTICR));
   }
   return bSuccess;
}