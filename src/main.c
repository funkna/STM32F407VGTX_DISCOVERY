// Includes ---------------------------------------------------------------------------------------
// Drivers
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"
// APIs
#include "led/led.h"
// Apps
#include "user_app_1/user_app_1.h"

static BOOL InitializeDriversAndAPI()
{
   // Initialize Drivers
   BOOL bInitSuccess = TRUE;
   bInitSuccess &= RCC_Initialize();
   bInitSuccess &= GPIO_Initialize(GPIO_GPIOD);

   // Initialize API
   bInitSuccess &= LED_Initialize();

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
