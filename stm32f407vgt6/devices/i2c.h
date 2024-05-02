// Redundancy Prevention --------------------------------------------------------------------------
#ifndef I2C_H_
#define I2C_H_

// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "peripherals.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

//--------------------------------------------------------------
// I2C Controller Register Bitmasks
//--------------------------------------------------------------
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

// Typedefs ---------------------------------------------------------------------------------------

//--------------------------------------------------------------
// Inter-Integrated Circuit Controller Register Structure
//--------------------------------------------------------------
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

// Functions --------------------------------------------------------------------------------------
I2CRegistersStruct* GetI2CController(
   I2CControllerEnum eController_)
{
   switch(eController_)
   {
      case I2C1:
         return (I2CRegistersStruct*)PERIPHERAL_ADDRESS_I2C1;
      case I2C2:
         return (I2CRegistersStruct*)PERIPHERAL_ADDRESS_I2C2;
      case I2C3:
         return (I2CRegistersStruct*)PERIPHERAL_ADDRESS_I2C3;
      default:
         return NULL;
   }
}

#endif // I2C_H_
