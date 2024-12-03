// Redundancy Prevention --------------------------------------------------------------------------
#ifndef DS1307_H_
#define DS1307_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
#define DS1307_I2C            (I2C1)
#define DS1307_I2C_ADDR       (0x68)

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
typedef struct
{
   UCHAR ucSeconds;
   UCHAR ucMinutes;
   UCHAR ucHours;
   UCHAR ucDay;
   UCHAR ucMonth;
   UCHAR ucYear;
} DS1307TimeKeepingStruct;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Initialize the DS1307 RTC Module
// -------------------------------------------------------------
BOOL DS1307_Initialize();

// -------------------------------------------------------------
// Enable time keeping on the DS1307 RTC Module
// -------------------------------------------------------------
BOOL DS1307_EnableTimeKeeping();

// -------------------------------------------------------------
// Disable time keeping on the DS1307 RTC Module
// -------------------------------------------------------------
BOOL DS1307_DisableTimeKeeping();

// -------------------------------------------------------------
// Get the time and date information from the DS1307 RTC Module
// -------------------------------------------------------------
BOOL DS1307_GetTimeAndDate(
   DS1307TimeKeepingStruct* pstTimeAndDate_);

// -------------------------------------------------------------
// Set the time and date information from the DS1307 RTC Module
// -------------------------------------------------------------
BOOL DS1307_SetTimeAndDate(
   DS1307TimeKeepingStruct* pstTimeAndDate_);

#endif // DS1307_H_
