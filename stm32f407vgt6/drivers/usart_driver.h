// Redundancy Prevention --------------------------------------------------------------------------
#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

// Includes ---------------------------------------------------------------------------------------
#include "types.h"
#include "peripherals.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------

typedef enum
{
   USARTMODE_TXRX = 0,
   USARTMODE_TX,
   USARTMODE_RX
}
USARTModeEnum;

typedef enum
{
   USARTBAUD_1200 = 0,
   USARTBAUD_2400,
   USARTBAUD_9600,
   USARTBAUD_19200,
   USARTBAUD_38400,
   USARTBAUD_57600,
   USARTBAUD_115200,
   USARTBAUD_230400,
   USARTBAUD_460800
}
USARTBaudRateEnum;

typedef enum
{
   USARTWORD_8BIT = 0,
}
USARTWordLengthEnum;

typedef enum
{
   USARTPARITY_NONE = 0,
   USARTPARITY_ODD,
   USARTPARITY_EVEN
}
USARTParityBitsEnum;

typedef enum
{
   USARTSTOP_1BIT = 0,
   USARTSTOP_0_5BIT,
   USARTSTOP_2BIT,
   USARTSTOP_1_5BIT
}
USARTStopBitsEnum;

typedef enum
{
   USARTFLOWCTL_DISABLED = 0,
   USARTFLOWCTL_CTS,
   USARTFLOWCTL_RTS,
   USARTFLOWCTL_CTS_RTS
}
USARTFlowControlEnum;

typedef struct
{
   USARTModeEnum eMode;
   USARTBaudRateEnum eBaudRate;
   USARTWordLengthEnum eWordLength;
   USARTParityBitsEnum ePartiy;
   USARTStopBitsEnum eStopBits;
   USARTFlowControlEnum eFlowControl;
} USARTConfigurationStruct;

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
// Inititalize a USART controller.
// -------------------------------------------------------------
BOOL USART_Initialize(
   USARTControllerEnum eController_);

// -------------------------------------------------------------
// Reset a USART controller.
// -------------------------------------------------------------
BOOL USART_Reset(
   USARTControllerEnum eController_);

// -------------------------------------------------------------
// Set configuration for a USART controller.
// -------------------------------------------------------------
BOOL USART_SetConfig(
   USARTControllerEnum eController_,
   const USARTConfigurationStruct* pstConfiguration_);

// -------------------------------------------------------------
// Get configuration for a USART controller.
// -------------------------------------------------------------
USARTConfigurationStruct* USART_GetConfig(
   USARTControllerEnum eController_);

// -------------------------------------------------------------
// Enable a USART controller.
// -------------------------------------------------------------
BOOL USART_Enable(
   USARTControllerEnum eController_);

// -------------------------------------------------------------
// Disable a USART controller.
// -------------------------------------------------------------
BOOL USART_Disable(
   USARTControllerEnum eController_);

// -------------------------------------------------------------
// Read data from a USART controller.
// -------------------------------------------------------------
BOOL USART_ReadData(
   USARTControllerEnum eController_,
   UCHAR* pucData_,
   UINT uiDataLength_);

// -------------------------------------------------------------
// Write data to a USART controller.
// -------------------------------------------------------------
BOOL USART_WriteData(
   USARTControllerEnum eController_,
   const UCHAR* pucData_,
   UINT uiDataLength_);

#endif // USART_DRIVER_H_
