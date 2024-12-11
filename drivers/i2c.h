//------------------------------------------------------------------------------
//! \file i2c.h
//! \brief Inter-Integrated Circuit driver.
//! \ref docs\stm32f407_reference_manual.pdf section 27.
//------------------------------------------------------------------------------
#ifndef __I2C_H
#define __I2C_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define I2C1_DEVICE_ADDRESS   (0x61)
#define I2C2_DEVICE_ADDRESS   (0x62)
#define I2C3_DEVICE_ADDRESS   (0x63)

//------------------------------------------------------------------------------
//! \brief I2C Controller Register Bitmasks
//------------------------------------------------------------------------------
#define CR1_ACK               (0x01UL << 10) // Acknowledge enable
#define CR1_STOP              (0x01UL << 9)  // Stop generation
#define CR1_START             (0x01UL << 8)  // Start generation
#define CR1_PE                (0x01UL << 0)  // I2C enable
#define CR2_ITBUFEN           (0x01UL << 10) // Buffer interrupt enable
#define CR2_ITEVTEN           (0x01UL << 9)  // Event interrupt enable
#define CR2_ITERREN           (0x01UL << 8)  // Error interrupt enable
#define CR2_FREQ              (0x3FUL << 0)  // Peripheral clock frequency
#define CCR_FS                (0x01UL << 15) // I2C master mode selection
#define CCR_DUTY              (0x01UL << 14) // Fast mode duty cycle
#define CCR_CCR               (0x7FFUL << 0) // Clock control register in Fm/Sm mode (Master mode)
#define OAR1_ADD_7_1          (0x7FUL << 1)
#define OAR1_ADD_7_1_OFFSET   (1)
#define SR1_TXE               (0x01UL << 7)  // Data register empty
#define SR1_RXNE              (0x01UL << 6)  // Data register not empty
#define SR1_BTF               (0x01UL << 2)  // Byte transfer finished
#define SR1_ADDR              (0x01UL << 1)  // Address sent
#define SR1_SB                (0x01UL << 0)  // Start bit

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief I2C Controller Mode
//------------------------------------------------------------------------------
typedef enum
{
   I2CMODE_MASTER = 0,
   I2CMODE_SLAVE
} I2CModeEnum;

//------------------------------------------------------------------------------
//! \brief I2C Acknowledgement Mode
//------------------------------------------------------------------------------
typedef enum
{
   I2CACK_DISABLE = 0,
   I2CACK_ENABLE
} I2CAcknowledgeModeEnum;

//------------------------------------------------------------------------------
//! \brief I2C Duty Cycle
//------------------------------------------------------------------------------
typedef enum
{
   I2CDUTY_NONE = 0,
   I2CDUTY_2 = I2CDUTY_NONE,
   I2CDUTY_16_9,
} I2CDutyCycleEnum;

//------------------------------------------------------------------------------
//! \brief I2C Clock Speed
//------------------------------------------------------------------------------
typedef enum
{
   I2CCLK_SM_100KHZ = 0,
   I2CCLK_FM_200KHZ
} I2CClockSpeedEnum;

//------------------------------------------------------------------------------
//! \brief I2C Controller Configuration
//------------------------------------------------------------------------------
typedef struct
{
   UCHAR ucAddress;
   I2CAcknowledgeModeEnum eAckMode;
   I2CDutyCycleEnum eDutyCycle;
   I2CClockSpeedEnum eClockSpeed;
} I2CConfigurationStruct;

//------------------------------------------------------------------------------
//! \brief I2C Transfer Type
//------------------------------------------------------------------------------
typedef enum
{
   I2CTRANSFER_WRITE = 0,
   I2CTRANSFER_READ
} I2CTransferTypeEnum;

//------------------------------------------------------------------------------
//! \brief I2C Transfer State
//------------------------------------------------------------------------------
typedef enum
{
   I2CSTATE_IDLE = 0,
   I2CSTATE_BEGIN,
   I2CSTATE_START_SENT,
   I2CSTATE_IN_PROGRESS,
   I2CSTATE_DATA_SENT,
   I2CSTATE_ERROR
} I2CTransferStateEnum;

//------------------------------------------------------------------------------
//! \brief Inter-Integrated Circuit Controller Register Structure
//------------------------------------------------------------------------------
typedef volatile struct
{
   UINT CR1;         // Control 1
   UINT CR2;         // Control 2
   UINT OAR1;        // Own address 1
   UINT OAR2;        // Own address 2
   UINT DR;          // Data
   UINT SR1;         // Status 1
   UINT SR2;         // Status 2
   UINT CCR;         // Clock control
   UINT TRISE;       // Rise time
   UINT FLTR;        // Filter
} I2CRegistersStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
BOOL I2C_Initialize(I2CControllerEnum eController_);
BOOL I2C_Reset(I2CControllerEnum eController_);
BOOL I2C_SetConfig(I2CControllerEnum eController_, const I2CConfigurationStruct* pstConfiguration_);
I2CConfigurationStruct* I2C_GetConfig(I2CControllerEnum eController_);
BOOL I2C_Enable(I2CControllerEnum eController_);
BOOL I2C_Disable(I2CControllerEnum eController_);
BOOL I2C_WriteData(I2CControllerEnum eController_, I2CModeEnum eMode_, UCHAR ucAddress_, UCHAR* pucData_, UINT uiLength_);
BOOL I2C_ReadData(I2CControllerEnum eController_, I2CModeEnum eMode_, UCHAR ucAddress_, UCHAR* pucCommand_, UINT uiCommandLength_, UCHAR* pucData_, UINT uiLength_);
BOOL I2C_MasterTransfer(I2CControllerEnum eController_, I2CTransferTypeEnum eTransferType_, UCHAR ucAddress_, UCHAR* pucBuffer_, UINT uiSize_);
I2CTransferStateEnum I2C_GetState(I2CControllerEnum eController_);
BOOL I2C_ConfigureAsInterrupt(I2CControllerEnum eController_);

#endif // __I2C_H
