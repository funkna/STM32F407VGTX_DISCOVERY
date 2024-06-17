// Includes ---------------------------------------------------------------------------------------
#include <string.h>
#include "ext/ds1307.h"
#include "ext/hd44780u.h"
#include "rtc_lcd.h"
#include "time.h"

#include "drivers/systick_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static DS1307TimeKeepingStruct stTheLastTime;
static DS1307TimeKeepingStruct stTheCurrentTime = {0, 0, 0, 1, 1, 24}; // Beginning of 2024.

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
static void PrintTimeKeepingStruct(
   DS1307TimeKeepingStruct* pstTimeAndDate_)
{
   Console_Printf("[%02d:%02d:%02d] (%02d/%02d/%02d)",
      pstTimeAndDate_->ucHours, pstTimeAndDate_->ucMinutes, pstTimeAndDate_->ucSeconds,
      pstTimeAndDate_->ucDay, pstTimeAndDate_->ucMonth, pstTimeAndDate_->ucYear);

    HD440780U_WriteString(HD440780U_LINE_1, "[%02d:%02d:%02d]",
       pstTimeAndDate_->ucHours, pstTimeAndDate_->ucMinutes, pstTimeAndDate_->ucSeconds);
    HD440780U_WriteString(HD440780U_LINE_2, "[%02d/%02d/%02d]",
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

   bSuccess &= HD440780U_Initialize();
   DelayMS(2);
   bSuccess &= HD440780U_SendCommand(0x01); // Clear the display.
   DelayMS(2);
   bSuccess &= HD440780U_SendCommand(0x0E); // Turn on display and cursor.
   DelayMS(2);
   bSuccess &= HD440780U_SendCommand(0x28); // Set data length to 4 bits, number of lines to 2 and character font to 5x8.
   DelayMS(2);
   bSuccess &= HD440780U_SendCommand(0x06); // Set DRAM address to 0 and increment cursor with DRAM writes.

   Console_Printf("LCD Initialized.");

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
