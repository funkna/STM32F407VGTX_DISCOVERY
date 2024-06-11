// ------------------------------------------------------------------------------------------------
// Author: Nathan Funk
// Date: February 2024
//
// This project contains the source code for the STM32F407VGT6 Discovery Board, done in step with
// the Master MCU Udemy Course:
// https://www.udemy.com/course/mastering-microcontroller-with-peripheral-driver-development
//
// Documentation:
// https://www.st.com/en/microcontrollers-microprocessors/stm32f407vg.html
// https://www.st.com/en/evaluation-tools/stm32f4discovery.html
// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf
// ------------------------------------------------------------------------------------------------

// Drivers
#include "drivers/nvic_driver.h"
#include "drivers/exti_driver.h"
#include "drivers/gpio_driver.h"
#include "drivers/rcc_driver.h"
#include "drivers/i2c_driver.h"
#include "drivers/usart_driver.h"
#include "drivers/syscfg_driver.h"

// APIs
#include "button.h"
#include "led.h"

// Apps
#include "rtc_lcd.h"

static BOOL InitializeDriversAndAPI()
{
   BOOL bInitSuccess = TRUE;

   // Initialize Drivers
   bInitSuccess &= RCC_Initialize();
   bInitSuccess &= NVIC_Initialize();
   bInitSuccess &= EXTI_Initialize();
   bInitSuccess &= SYSCFG_Initialize();
   bInitSuccess &= GPIO_Initialize(GPIO_PORT_A); // Buttons
   bInitSuccess &= GPIO_Initialize(GPIO_PORT_B); // I2C
   bInitSuccess &= GPIO_Initialize(GPIO_PORT_D); // LEDs
   bInitSuccess &= I2C_Initialize(I2C1);
   bInitSuccess &= USART_Initialize(USART2);

   // Initialize API
   bInitSuccess &= LED_Initialize();
   bInitSuccess &= Button_Initialize();

   return bInitSuccess;
}

static BOOL InitializeApplications()
{
   // Initialize Apps
   BOOL bAppInitSuccess = TRUE;
   bAppInitSuccess &= Initialize_RTCLCD();
   return bAppInitSuccess;
}

int main(void)
{
   if(!InitializeDriversAndAPI())
   {
      LED_On(LED_RED);
      while(TRUE);
   }

   if(!InitializeApplications())
   {
      LED_On(LED_ORANGE);
      while(TRUE);
   }

   while(TRUE)
   {
      // Run Apps
      Run_RTCLCD();
   }
   Exit_RTCLCD();
}
