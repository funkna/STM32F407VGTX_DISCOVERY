// Includes ---------------------------------------------------------------------------------------
// Drivers
#include "driver/cortex-m4/nvic/nvic_driver.h"

#include "driver/exti/exti_driver.h"
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"
#include "driver/syscfg/syscfg_driver.h"

// APIs
#include "button/button.h"
#include "led/led.h"

// Apps
#include "user_app_1/user_app_1.h"

static BOOL InitializeDriversAndAPI()
{
   // Initialize Drivers
   BOOL bInitSuccess = TRUE;
   bInitSuccess &= RCC_Initialize();
   bInitSuccess &= NVIC_Initialize();
   bInitSuccess &= EXTI_Initialize();
   bInitSuccess &= SYSCFG_Initialize();
   bInitSuccess &= GPIO_Initialize(GPIO_GPIOA);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOB);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOC);
   bInitSuccess &= GPIO_Initialize(GPIO_GPIOD);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOE);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOF);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOG);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOH);
   // bInitSuccess &= GPIO_Initialize(GPIO_GPIOI);

   // Initialize API
   bInitSuccess &= LED_Initialize();
   bInitSuccess &= Button_Initialize();

   return bInitSuccess;
}

static BOOL InitializeApplications()
{
   // Initialize Apps
   BOOL bAppInitSuccess = TRUE;
   bAppInitSuccess &= Initialize_UserApp1();
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
      Run_UserApp1();
   }
   Exit_UserApp1();
}
