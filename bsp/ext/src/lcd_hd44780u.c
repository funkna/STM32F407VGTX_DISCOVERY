//------------------------------------------------------------------------------
//! \file lcd_hd44780u.c
//! \brief LCD device funcionality.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include "lcd_hd44780u.h"
#include "gpio.h"
#include "time.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define HD440780U_GPIO_PORT      (GPIO_PORT_D)
#define HD440780U_PIN_RS         (GPIO_PIN_0)
#define HD440780U_PIN_RW         (GPIO_PIN_1)
#define HD440780U_PIN_E          (GPIO_PIN_2)
#define HD440780U_PIN_D4         (GPIO_PIN_3)
#define HD440780U_PIN_D5         (GPIO_PIN_4)
#define HD440780U_PIN_D6         (GPIO_PIN_5)
#define HD440780U_PIN_D7         (GPIO_PIN_6)
#define HD440780U_LINE_BUFFER    (16U)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
GPIOConfigurationStruct stTheLCDPinConfig = {
   GPIOMODE_GP_OUTPUT,
   GPIOTYPE_OPENDRAIN,
   GPIOSPEED_VHI,
   GPIOPUPD_NONE,
   GPIOALTFUNC_AF0
};

//------------------------------------------------------------------------------
static BOOL
DataWrite4Bit(
   UCHAR ucNibble_)
{
   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_E, GPIO_HI);

   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_D4, (ucNibble_ & 0x1));
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_D5, (ucNibble_ & 0x2));
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_D6, (ucNibble_ & 0x4));
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_D7, (ucNibble_ & 0x8));

   DelayMS(1);
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_E, GPIO_LO);
   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
HD440780U_Initialize()
{
   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_RS, &stTheLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_RW, &stTheLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_E,  &stTheLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D4, &stTheLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D5, &stTheLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D6, &stTheLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D7, &stTheLCDPinConfig);

   DelayMS(40);

   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RS, GPIO_LO);
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RW, GPIO_LO);

   bSuccess &= DataWrite4Bit(0x3);

   DelayMS(5);

   bSuccess &= DataWrite4Bit(0x3);

   DelayMS(1);

   bSuccess &= DataWrite4Bit(0x3);
   bSuccess &= DataWrite4Bit(0x2);

   bSuccess &= HD440780U_SendCommand(0x20);
   bSuccess &= HD440780U_SendCommand(0x08);
   bSuccess &= HD440780U_SendCommand(0x01);
   bSuccess &= HD440780U_SendCommand(0x07);

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
HD440780U_SendCommand(
   UCHAR ucCommand_)
{
   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RS, GPIO_LO);
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RW, GPIO_LO);

   DelayMS(1);

   DataWrite4Bit((ucCommand_ & 0xF0) >> 4);
   DataWrite4Bit(ucCommand_ & 0x0F);

   // DelayMS(2); // Maximum time

   return bSuccess;
}

//------------------------------------------------------------------------------
BOOL
HD440780U_WriteByte(
   UCHAR ucByte_)
{
   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RS, GPIO_HI);
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RW, GPIO_LO);

   DelayMS(1);

   DataWrite4Bit((ucByte_ & 0xF0) >> 4);
   DataWrite4Bit(ucByte_ & 0x0F);

   DelayMS(1);

   return bSuccess;
}

//------------------------------------------------------------------------------
void
HD440780U_WriteString(
   HD440780ULineEnum eLine_,
   const SCHAR* szFormat_,
   ...)
{
   if(eLine_ == HD440780U_LINE_1)
   {
      (void)HD440780U_SendCommand(0x80); // Set DRAM address to column 0 in line 1.
   }
   else
   {
      (void)HD440780U_SendCommand((0x80 | 0x40)); // Set DRAM address to column 0 in line 2.

   }

   static SCHAR acBuffer[HD440780U_LINE_BUFFER];

   va_list stArgs;
   va_start(stArgs, szFormat_);
   UINT uiBytesInBuffer = vsnprintf(&acBuffer[0], HD440780U_LINE_BUFFER, szFormat_, stArgs);
   va_end(stArgs);

   for(UINT uiIndex = 0; uiIndex < uiBytesInBuffer; uiIndex++)
   {
      HD440780U_WriteByte((UCHAR)acBuffer[uiIndex]);
   }
}
