// Redundancy Prevention --------------------------------------------------------------------------
#ifndef GPIO_H_
#define GPIO_H_

// Includes ---------------------------------------------------------------------------------------
#include "../stm32f407vgt6.h"
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
   UINT MODER;
   UINT OTYPER;
   UINT OSPEEDR;
   UINT PUPDR;
   UINT IDR;
   UINT ODR;
   UINT BSRR;
   UINT LCKR;
   UINT AFRL;
   UINT AFRH;
} GPIORegistersStruct;

// Functions --------------------------------------------------------------------------------------

GPIORegistersStruct* GetGPIOController(
   GPIOControllerEnum eController_)
{
   switch(eController_)
   {
      case GPIO_GPIOA:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOA;
      case GPIO_GPIOB:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOB;
      case GPIO_GPIOC:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOC;
      case GPIO_GPIOD:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOD;
      case GPIO_GPIOE:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOE;
      case GPIO_GPIOF:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOF;
      case GPIO_GPIOG:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOG;
      case GPIO_GPIOH:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOH;
      case GPIO_GPIOI:
         return (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOI;
      default:
         return NULL;
   }
}

#endif // GPIO_H_



