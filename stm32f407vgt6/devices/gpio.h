// Redundancy Prevention --------------------------------------------------------------------------
#ifndef GPIO_H_
#define GPIO_H_

// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "peripherals.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------
#define MODER_MASK      (0x03)
#define OTYPER_MASK     (0x01)
#define OSPEEDR_MASK    (0x03)
#define PUPDR_MASK      (0x03)

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// GPIO Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT MODER;       // Mode
   UINT OTYPER;      // Output Type
   UINT OSPEEDR;     // Output Speed
   UINT PUPDR;       // Pull-Up/Pull-Down
   UINT IDR;         // Input Data
   UINT ODR;         // Output Data
   UINT BSRR;        // Bit Set/Reset
   UINT LCKR;        // Configuration Lock
   UINT AFRL;        // Alternate Function Low
   UINT AFRH;        // Alternate Function High
} GPIORegistersStruct;

// Functions --------------------------------------------------------------------------------------
GPIORegistersStruct* GetGPIOController(
   GPIOPortEnum ePort_)
{
   switch(ePort_)
   {
      case GPIO_PORT_A:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOA;
      }
      case GPIO_PORT_B:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOB;
      }
      case GPIO_PORT_C:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOC;
      }
      case GPIO_PORT_D:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOD;
      }
      case GPIO_PORT_E:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOE;
      }
      case GPIO_PORT_F:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOF;
      }
      case GPIO_PORT_G:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOG;
      }
      case GPIO_PORT_H:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOH;
      }
      case GPIO_PORT_I:
      {
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOI;
      }
      default:
      {
         return NULL;
      }
   }
}

#endif // GPIO_H_



