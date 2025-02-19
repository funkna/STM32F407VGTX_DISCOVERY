//------------------------------------------------------------------------------
//! \file main.c
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "nvic.h"
#include "systick.h"
#include "exti.h"
#include "gpio.h"
#include "rcc.h"
#include "i2c.h"
#include "usart.h"
#include "syscfg.h"

#include "button.h"
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
   if(!LED_Initialize()) return FALSE;

   return TRUE;
}


//------------------------------------------------------------------------------
int main(void)
{
   if(!InitializeBSP()) while(TRUE);

   while(TRUE)
   {
      if(Button_WasPressed(BUTTON_0))
      {
         Button_Acknowledge(BUTTON_0);
         LED_Toggle(LED_BLUE);
      }

      Button_RunTask();
      // LED_Toggle(LED_BLUE);

      // DelayMS(1000);
   }
}
