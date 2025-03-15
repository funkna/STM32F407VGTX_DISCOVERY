//------------------------------------------------------------------------------
//! \file gpio.c
//! \brief General Purpose Input/Output driver implementation.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "gpio.h"
#include "rcc.h"
#include <string.h>

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define NUM_CONFIG_BITS_MODE        (2)
#define NUM_CONFIG_BITS_OTYPE       (1)
#define NUM_CONFIG_BITS_OSPEED      (2)
#define NUM_CONFIG_BITS_PUPD        (2)
#define NUM_CONFIG_BITS_ALTFUNC     (4)
#define NUM_ALTFUNCS_PER_AFR        (8)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief GPIO Device description
//------------------------------------------------------------------------------
typedef struct
{
   GPIORegistersStruct* pstRegisters;
   GPIOConfigurationStruct stConfiguration;
} GPIODeviceStruct;

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------
static GPIODeviceStruct astTheGPIODevices[GPIO_PORT_MAX];

static STM32F407VGT6_PeriperalEnum aeTheGPIOPeripherals[GPIO_PORT_MAX] = {
   PERIPHERAL_GPIOA,
   PERIPHERAL_GPIOB,
   PERIPHERAL_GPIOC,
   PERIPHERAL_GPIOD,
   PERIPHERAL_GPIOE,
   PERIPHERAL_GPIOF,
   PERIPHERAL_GPIOG,
   PERIPHERAL_GPIOH,
   PERIPHERAL_GPIOI
};

static GPIORegistersStruct* apstTheGPIOControllers[GPIO_PORT_MAX] = {
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOA,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOB,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOC,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOD,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOE,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOF,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOG,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOH,
   (GPIORegistersStruct*)PERIPHERAL_ADDRESS_GPIOI
};

//------------------------------------------------------------------------------
BOOL
GPIO_Initialize(
   GPIOPortEnum ePort_)
{
   astTheGPIODevices[ePort_].pstRegisters = apstTheGPIOControllers[ePort_];
   if(astTheGPIODevices[ePort_].pstRegisters != NULL)
   {
      return RCC_EnablePeripheralClock(aeTheGPIOPeripherals[ePort_]);
   }

   return FALSE;
}

//------------------------------------------------------------------------------
BOOL
GPIO_Reset(
   GPIOPortEnum ePort_)
{
   return RCC_ResetPeripheralClock(aeTheGPIOPeripherals[ePort_]);
}

//------------------------------------------------------------------------------
BOOL
GPIO_SetConfig(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_,
   const GPIOConfigurationStruct* pstConfiguration_)
{
   if((astTheGPIODevices[ePort_].pstRegisters == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   UINT uiModeValue = (UINT)pstConfiguration_->eMode << (NUM_CONFIG_BITS_MODE * ePin_);
   UINT uiOutputTypeValue = (UINT)pstConfiguration_->eOutputType << (NUM_CONFIG_BITS_OTYPE * ePin_);
   UINT uiSpeedValue = (UINT)pstConfiguration_->eSpeed << (NUM_CONFIG_BITS_OSPEED * ePin_);
   UINT uiPUPDValue = (UINT)pstConfiguration_->ePUPD << (NUM_CONFIG_BITS_PUPD * ePin_);
   UINT uiAltFuncValue = (UINT)pstConfiguration_->eAlternateFunction << (NUM_CONFIG_BITS_ALTFUNC * (ePin_ % NUM_ALTFUNCS_PER_AFR));

   astTheGPIODevices[ePort_].pstRegisters->MODER |= uiModeValue;
   astTheGPIODevices[ePort_].pstRegisters->OTYPER |= uiOutputTypeValue;
   astTheGPIODevices[ePort_].pstRegisters->OSPEEDR |= uiSpeedValue;
   astTheGPIODevices[ePort_].pstRegisters->PUPDR |= uiPUPDValue;

   if(ePin_ < GPIO_PIN_8)
   {
      astTheGPIODevices[ePort_].pstRegisters->AFRL |= uiAltFuncValue;
   }
   else
   {
      astTheGPIODevices[ePort_].pstRegisters->AFRH |= uiAltFuncValue;
   }

   memcpy(&(astTheGPIODevices[ePort_].stConfiguration), pstConfiguration_, sizeof(GPIOConfigurationStruct));

   return TRUE;
}

//------------------------------------------------------------------------------
BOOL
GPIO_ReadPin(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_,
   GPIOStateEnum* peState_)
{
   if((astTheGPIODevices[ePort_].pstRegisters == NULL) ||
      (peState_ == NULL))
   {
      return FALSE;
   }

   *peState_ = (astTheGPIODevices[ePort_].pstRegisters->IDR >> ePin_) & GPIO_HI;
   return TRUE;
}

//------------------------------------------------------------------------------
BOOL
GPIO_WritePin(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_,
   GPIOStateEnum eState_)
{
   if(astTheGPIODevices[ePort_].pstRegisters == NULL)
   {
      return FALSE;
   }

   if(eState_ == GPIO_LO)
   {
      astTheGPIODevices[ePort_].pstRegisters->ODR &= ~(0x01UL << ePin_);
   }
   else
   {
      astTheGPIODevices[ePort_].pstRegisters->ODR |= (0x01UL << ePin_);
   }

   return TRUE;
}

//------------------------------------------------------------------------------
BOOL
GPIO_TogglePin(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   if(astTheGPIODevices[ePort_].pstRegisters == NULL)
   {
      return FALSE;
   }

   astTheGPIODevices[ePort_].pstRegisters->ODR ^= (0x01UL << ePin_);

   return FALSE;
}
