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
static BOOL InitializeDrivers()
{
   RCC_Initialize();
   SYSTICK_Initialize();
   NVIC_Initialize();
   EXTI_Initialize();
   SYSCFG_Initialize();

   return TRUE;
}

//------------------------------------------------------------------------------
static BOOL InitializeBSP()
{
   if(!Button_Initialize()) return FALSE;
   if(!LED_Initialize()) return FALSE;

   return TRUE;
}


//------------------------------------------------------------------------------
int main(void)
{
   if(!InitializeDrivers()) while(TRUE);
   if(!InitializeBSP()) while(TRUE);

   while(TRUE)
   {
      LED_On(LED_BLUE);
      DelayMS(500);
      LED_Off(LED_BLUE);
      DelayMS(500);
   }
}
