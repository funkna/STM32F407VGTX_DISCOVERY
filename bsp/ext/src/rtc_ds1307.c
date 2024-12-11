//------------------------------------------------------------------------------
//! \file rtc_ds1307.c
//! \brief Real-Time Clock device functionality.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "rtc_ds1307.h"
#include "i2c.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define DS1307_SECONDS_CH           (0x01UL << 7) // DS1307_REG_ADDR_SECONDS
#define DS1307_HOURS_12HR24HR       (0x01UL << 6) // DS1307_REG_ADDR_HOURS
#define DS1307_HOURS_AMPM           (0x01UL << 5) // DS1307_REG_ADDR_HOURS
#define DS1307_CONTROL_RS0          (0x01UL << 0) // DS1307_REG_ADDR_CONTROL
#define DS1307_CONTROL_RS1          (0x01UL << 1) // DS1307_REG_ADDR_CONTROL
#define DS1307_CONTROL_SQWE         (0x01UL << 4) // DS1307_REG_ADDR_CONTROL
#define DS1307_CONTROL_OUT          (0x01UL << 7) // DS1307_REG_ADDR_CONTROL

#define BCD_TENS_SHIFT              (4)
#define CONVERT_TO_BCD(x)           ((x % 10) | ((x / 10) << BCD_TENS_SHIFT))
#define CONVERT_FROM_BCD(x)         ((x & ((0x01 << BCD_TENS_SHIFT) - 1)) + ((x >> BCD_TENS_SHIFT) * 10))

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief DS1307 device addresses
//------------------------------------------------------------------------------
typedef enum
{
   DS1307_REG_ADDR_SECONDS = 0,
   DS1307_REG_ADDR_MINUTES,
   DS1307_REG_ADDR_HOURS,
   DS1307_REG_ADDR_DAY,
   DS1307_REG_ADDR_MONTH,
   DS1307_REG_ADDR_YEAR,
   DS1307_REG_ADDR_CONTROL,
   DS1307_REG_ADDR_MAX
} DS1307RegisterAddressEnum;

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static const I2CConfigurationStruct stTheDS1307I2CConfig = {
   I2C1_DEVICE_ADDRESS,
   I2CACK_ENABLE,
   I2CDUTY_NONE,
   I2CCLK_SM_100KHZ
};

//------------------------------------------------------------------------------
BOOL
DS1307_Initialize()
{
   BOOL bSuccess = TRUE;
   bSuccess &= I2C_Initialize(DS1307_I2C);
   bSuccess &= I2C_SetConfig(DS1307_I2C, &stTheDS1307I2CConfig);
   bSuccess &= I2C_Enable(DS1307_I2C);
   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
DS1307_EnableTimeKeeping()
{
   BOOL bSuccess = TRUE;
   UCHAR aucSetTimeAndDateCommandBuffer[2] = {DS1307_REG_ADDR_SECONDS, 0x00};

   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   aucSetTimeAndDateCommandBuffer[1] &= ~DS1307_SECONDS_CH;
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
DS1307_DisableTimeKeeping()
{
   BOOL bSuccess = TRUE;
   UCHAR aucSetTimeAndDateCommandBuffer[2] = {DS1307_REG_ADDR_SECONDS, 0x00};

   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   aucSetTimeAndDateCommandBuffer[1] |= DS1307_SECONDS_CH;
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
DS1307_GetTimeAndDate(
   DS1307TimeKeepingStruct* pstTimeAndDate_)
{
   BOOL bSuccess = TRUE;
   UCHAR aucSetTimeAndDateCommandBuffer[2] = {0};

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_SECONDS;
   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   pstTimeAndDate_->ucSeconds = CONVERT_FROM_BCD(aucSetTimeAndDateCommandBuffer[1]);

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_MINUTES;
   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   pstTimeAndDate_->ucMinutes = CONVERT_FROM_BCD(aucSetTimeAndDateCommandBuffer[1]);

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_HOURS;
   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   pstTimeAndDate_->ucHours = CONVERT_FROM_BCD(aucSetTimeAndDateCommandBuffer[1]);

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_DAY;
   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   pstTimeAndDate_->ucDay = CONVERT_FROM_BCD(aucSetTimeAndDateCommandBuffer[1]);

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_MONTH;
   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   pstTimeAndDate_->ucMonth = CONVERT_FROM_BCD(aucSetTimeAndDateCommandBuffer[1]);

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_YEAR;
   bSuccess &= I2C_ReadData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], 1, &aucSetTimeAndDateCommandBuffer[1], 1);
   pstTimeAndDate_->ucYear = CONVERT_FROM_BCD(aucSetTimeAndDateCommandBuffer[1]);

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
DS1307_SetTimeAndDate(
   DS1307TimeKeepingStruct* pstTimeAndDate_)
{
   BOOL bSuccess = TRUE;
   UCHAR aucSetTimeAndDateCommandBuffer[2] = {0};

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_SECONDS;
   aucSetTimeAndDateCommandBuffer[1] = CONVERT_TO_BCD(pstTimeAndDate_->ucSeconds);
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_MINUTES;
   aucSetTimeAndDateCommandBuffer[1] = CONVERT_TO_BCD(pstTimeAndDate_->ucMinutes);
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_HOURS;
   aucSetTimeAndDateCommandBuffer[1] = CONVERT_TO_BCD(pstTimeAndDate_->ucHours);
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_DAY;
   aucSetTimeAndDateCommandBuffer[1] = CONVERT_TO_BCD(pstTimeAndDate_->ucDay);
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_MONTH;
   aucSetTimeAndDateCommandBuffer[1] = CONVERT_TO_BCD(pstTimeAndDate_->ucMonth);
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   aucSetTimeAndDateCommandBuffer[0] = DS1307_REG_ADDR_YEAR;
   aucSetTimeAndDateCommandBuffer[1] = CONVERT_TO_BCD(pstTimeAndDate_->ucYear);
   bSuccess &= I2C_WriteData(DS1307_I2C, I2CMODE_MASTER, DS1307_I2C_ADDR, &aucSetTimeAndDateCommandBuffer[0], sizeof(aucSetTimeAndDateCommandBuffer));

   return bSuccess;
}
