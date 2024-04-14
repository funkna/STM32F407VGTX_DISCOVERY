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
#define CR1_PE                (0x01UL << 0)  // I2C enable

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
