// Includes ---------------------------------------------------------------------------------------
#include "devices/gpio.h"
#include "drivers/gpio_driver.h"
#include "drivers/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
#define NUM_CONFIG_BITS_MODE        (2)
#define NUM_CONFIG_BITS_OTYPE       (1)
#define NUM_CONFIG_BITS_OSPEED      (2)
#define NUM_CONFIG_BITS_PUPD        (2)
#define NUM_CONFIG_BITS_ALTFUNC     (4)
#define NUM_ALTFUNCS_PER_AFR        (8)

// Typedefs ---------------------------------------------------------------------------------------
typedef struct
{
   GPIORegistersStruct* pstRegisters;
   GPIOConfigurationStruct stConfiguration;
} GPIODeviceStruct;

// Statics, Externs & Globals ---------------------------------------------------------------------
static GPIODeviceStruct astTheGPIODevices[GPIO_PORT_MAX];

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum GPIOEnumToSTM32Enum(
   GPIOPortEnum ePort_)
{
   switch(ePort_)
   {
      case GPIO_PORT_A:
      {
         return PERIPHERAL_GPIOA;
      }
      case GPIO_PORT_B:
      {
         return PERIPHERAL_GPIOB;
      }
      case GPIO_PORT_C:
      {
         return PERIPHERAL_GPIOC;
      }
      case GPIO_PORT_D:
      {
         return PERIPHERAL_GPIOD;
      }
      case GPIO_PORT_E:
      {
         return PERIPHERAL_GPIOE;
      }
      case GPIO_PORT_F:
      {
         return PERIPHERAL_GPIOF;
      }
      case GPIO_PORT_G:
      {
         return PERIPHERAL_GPIOG;
      }
      case GPIO_PORT_H:
      {
         return PERIPHERAL_GPIOH;
      }
      case GPIO_PORT_I:
      {
         return PERIPHERAL_GPIOI;
      }
      default:
      {
         return PERIPHERAL_INVALID;
      }
   }
}

// -------------------------------------------------------------
BOOL GPIO_Initialize(
   GPIOPortEnum ePort_)
{
   BOOL bSuccess = FALSE;
   astTheGPIODevices[ePort_].pstRegisters = GetGPIOController(ePort_);
   if(astTheGPIODevices[ePort_].pstRegisters != NULL)
   {
      bSuccess = RCC_EnablePeripheralClock(GPIOEnumToSTM32Enum(ePort_));
   }
   return bSuccess;
}

// -------------------------------------------------------------
BOOL GPIO_Reset(
   GPIOPortEnum ePort_)
{
   return RCC_ResetPeripheralClock(GPIOEnumToSTM32Enum(ePort_));
}

// -------------------------------------------------------------
BOOL GPIO_SetConfig(
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

// -------------------------------------------------------------
GPIOConfigurationStruct* GPIO_GetConfig(
   GPIOPortEnum ePort_,
   GPIOPinEnum ePin_)
{
   if(astTheGPIODevices[ePort_].pstRegisters == NULL)
   {
      return NULL;
   }

   return &(astTheGPIODevices[ePort_].stConfiguration);
}

// -------------------------------------------------------------
BOOL GPIO_ReadPin(
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

// -------------------------------------------------------------
BOOL GPIO_WritePin(
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

// -------------------------------------------------------------
BOOL GPIO_TogglePin(
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
