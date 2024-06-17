// Includes ---------------------------------------------------------------------------------------
#include <stdarg.h>
#include "ext/hd44780u.h"
#include "drivers/gpio_driver.h"
#include "time.h"

// Defines ----------------------------------------------------------------------------------------
#define HD440780U_GPIO_PORT      (GPIO_PORT_D)
#define HD440780U_PIN_RS         (GPIO_PIN_0)
#define HD440780U_PIN_RW         (GPIO_PIN_1)
#define HD440780U_PIN_E          (GPIO_PIN_2)
#define HD440780U_PIN_D4         (GPIO_PIN_3)
#define HD440780U_PIN_D5         (GPIO_PIN_4)
#define HD440780U_PIN_D6         (GPIO_PIN_5)
#define HD440780U_PIN_D7         (GPIO_PIN_6)
#define HD440780U_LINE_BUFFER    (16)

// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
static BOOL DataWrite4Bit(
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

// -------------------------------------------------------------
BOOL HD440780U_Initialize()
{
   GPIOConfigurationStruct stLCDPinConfig = {
      GPIOMODE_GP_OUTPUT,
      GPIOTYPE_OPENDRAIN,
      GPIOSPEED_VHI,
      GPIOPUPD_NONE,
      GPIOALTFUNC_AF0
   };

   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_RS, &stLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_RW, &stLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_E,  &stLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D4, &stLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D5, &stLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D6, &stLCDPinConfig);
   bSuccess &= GPIO_SetConfig(HD440780U_GPIO_PORT, HD440780U_PIN_D7, &stLCDPinConfig);

   DelayMS(40);

   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RS, GPIO_LO);
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RW, GPIO_LO);

   bSuccess &= DataWrite4Bit(0x03);

   DelayMS(5);

   bSuccess &= DataWrite4Bit(0x03);

   DelayMS(1);

   bSuccess &= DataWrite4Bit(0x03);

   return bSuccess;
}

// -------------------------------------------------------------
BOOL HD440780U_SendCommand(
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

// -------------------------------------------------------------
BOOL HD440780U_WriteByte(
   UCHAR ucByte_)
{
   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RS, GPIO_HI);
   bSuccess &= GPIO_WritePin(HD440780U_GPIO_PORT, HD440780U_PIN_RW, GPIO_LO);

   DelayMS(1);

   DataWrite4Bit(ucByte_ & 0x0F);
   DataWrite4Bit((ucByte_ & 0xF0) >> 4);

   DelayMS(1);

   return bSuccess;
}



// -------------------------------------------------------------
void HD440780U_WriteString(
   const SCHAR* szFormat_,
   ...)
{
   (void)HD440780U_SendCommand(0x01); // Clear the display.
   DelayMS(2);
   (void)HD440780U_SendCommand(0x06); // Set DRAM address to 0 and increment cursor with DRAM writes.

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
