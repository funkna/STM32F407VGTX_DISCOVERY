// Includes ---------------------------------------------------------------------------------------
#include "user_app_1/user_app_1.h"

int main(void)
{
   BOOL bInitializationSuccess = FALSE;
   bInitializationSuccess = Initialize_UserApp1();

   if(bInitializationSuccess)
   {
      while(TRUE)
      {
         Run_UserApp1();
      }
   }
   Exit_UserApp1();
}
