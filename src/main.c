//------------------------------------------------------------------------------
//! \file main.c
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "exti.h"
#include "nvic.h"
#include "rcc.h"
#include "syscfg.h"
#include "systick.h"

#include "button.h"
#include "console.h"
#include "led.h"
#include "time.h"

//------------------------------------------------------------------------------
static BOOL InitializeBSP()
{
   RCC_Initialize();
   SYSTICK_Initialize();
   NVIC_Initialize();
   EXTI_Initialize();
   SYSCFG_Initialize();

   if(!Button_Initialize()) return FALSE;
   if(!Console_Initialize()) return FALSE;
   if(!LED_Initialize()) return FALSE;

   return TRUE;
}


//------------------------------------------------------------------------------
int main(void)
{
   if(!InitializeBSP()) while(TRUE);
   Console_Printf("BSP Initialized.\r\n");

   Console_Printf("STM32F407VGTX_DISCOVERY running.\r\n");
   while(TRUE)
   {
      if(Button_WasPressed(BUTTON_0))
      {
         Button_Acknowledge(BUTTON_0);
         LED_Toggle(LED_BLUE);
         Console_Printf("Button pressed!\r\n");
      }

      Button_RunTask();
      ConsoleEcho_RunTask();
   }
}
