// Includes ---------------------------------------------------------------------------------------
#include "device/peripherals.h"
#include "device/syscfg/syscfg.h"
#include "driver/rcc/rcc_driver.h"
#include "driver/syscfg/syscfg_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static SYSCFGRegistersStruct* pstTheSYSCFGController = NULL;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
BOOL SYSCFG_Initialize()
{
   if(pstTheSYSCFGController == NULL)
   {
      pstTheSYSCFGController = GetSYSCFGController();
      if(!RCC_EnablePeripheralClock(SYSCFG))
      {
         (void)SYSCFG_Initialize();
         return FALSE;
      }
   }
   return TRUE;
}

// -------------------------------------------------------------
BOOL SYSCFG_Deinitialize()
{
   pstTheSYSCFGController = NULL;
   return RCC_ResetPeripheralClock(SYSCFG);
}

// -------------------------------------------------------------
BOOL SYSCFG_ConfigureEXTI(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   BOOL bSuccess = TRUE;
   UCHAR ucSysCfgCR = (ePin_ / 4);
   UCHAR ucEXTIPort = (ePort_ & 0x0F);
   switch(ucSysCfgCR)
   {
      case 0:
         pstTheSYSCFGController->EXTICR1 |= (ucEXTIPort << (ucEXTIPort % 4));
         break;
      case 1:
         pstTheSYSCFGController->EXTICR2 |= (ucEXTIPort << (ucEXTIPort % 4));
         break;
      case 2:
         pstTheSYSCFGController->EXTICR3 |= (ucEXTIPort << (ucEXTIPort % 4));
         break;
      case 3:
         pstTheSYSCFGController->EXTICR4 |= (ucEXTIPort << (ucEXTIPort % 4));
         break;
      default:
         bSuccess = FALSE;
         break;
   }
   return bSuccess;
}