// Includes ---------------------------------------------------------------------------------------
#include <string.h>
#include "ext/ds1307.h"
#include "rtc_lcd.h"

// Defines ----------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static DS1307TimeKeepingStruct stTheLastTime;
static DS1307TimeKeepingStruct stTheCurrentTime = {0, 0, 0, 1, 1, 1, 24}; // Beginning of 2024.

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
static void PrintTimeKeepingStruct(
   DS1307TimeKeepingStruct* pstTimeAndDate_)
{
   Console_Printf("[%02d:%02d:%02d] (%02d/%02d/%02d)",
      pstTimeAndDate_->ucHours, pstTimeAndDate_->ucMinutes, pstTimeAndDate_->ucSeconds,
      pstTimeAndDate_->ucDay, pstTimeAndDate_->ucMonth, pstTimeAndDate_->ucYear);
}

// -------------------------------------------------------------
BOOL Initialize_RTCLCD()
{
   BOOL bSuccess = TRUE;
   bSuccess &= Console_Initialize();
   Console_Printf("+--------- RTC on LCD App Init ---------+");

   bSuccess &= DS1307_Initialize();
   bSuccess &= DS1307_DisableTimeKeeping();
   bSuccess &= DS1307_SetTimeAndDate(&stTheCurrentTime);
   bSuccess &= DS1307_EnableTimeKeeping();
   Console_Printf("DS1307 Time Keeping Enabled.");

   return bSuccess;
}

// -------------------------------------------------------------
void Run_RTCLCD()
{
   // Get, compare and print the current time from the RTC chip
   if(DS1307_GetTimeAndDate(&stTheCurrentTime))
   {
      if(0 != memcmp(&stTheLastTime, &stTheCurrentTime, sizeof(DS1307TimeKeepingStruct)))
      {
         memcpy(&stTheLastTime, &stTheCurrentTime, sizeof(DS1307TimeKeepingStruct));
         PrintTimeKeepingStruct(&stTheCurrentTime);
      }
   }
}

// -------------------------------------------------------------
BOOL Exit_RTCLCD()
{
   BOOL bSuccess = TRUE;
   return bSuccess;
}
