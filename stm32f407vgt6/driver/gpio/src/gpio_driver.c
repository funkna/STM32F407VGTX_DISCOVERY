// Includes ---------------------------------------------------------------------------------------
#include "device/gpio/gpio.h"
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static GPIORegistersStruct* apstTheGPIOPorts[GPIO_MAX] = {NULL};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum GPIOEnumToSTM32Enum(
   GPIOPortEnum eGPIOPort_)
{
   switch(eGPIOPort_)
   {
      case GPIO_GPIOA:
         return GPIOA;
         break;
      case GPIO_GPIOB:
         return GPIOB;
         break;
      case GPIO_GPIOC:
         return GPIOC;
         break;
      case GPIO_GPIOD:
         return GPIOD;
         break;
      case GPIO_GPIOE:
         return GPIOE;
         break;
      case GPIO_GPIOF:
         return GPIOF;
         break;
      case GPIO_GPIOG:
         return GPIOG;
         break;
      case GPIO_GPIOH:
         return GPIOH;
         break;
      case GPIO_GPIOI:
         return GPIOI;
         break;
      default:
         return INVALID;
   }
}

// -------------------------------------------------------------
BOOL GPIO_Initialize(
   GPIOPortEnum eGPIOPort_)
{
   if(apstTheGPIOPorts[eGPIOPort_] == NULL)
   {
      STM32F407VGT6_PeriperalEnum ePeripheral = GPIOEnumToSTM32Enum(eGPIOPort_);
      apstTheGPIOPorts[eGPIOPort_] = GetGPIOController(eGPIOPort_);
      if((apstTheGPIOPorts[eGPIOPort_] == NULL) ||
         (!RCC_EnablePeripheralClock(ePeripheral)))
      {
         (void)GPIO_Deinitialize(eGPIOPort_);
         return FALSE;
      }
   }
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_Deinitialize(
   GPIOPortEnum eGPIOPort_)
{
   STM32F407VGT6_PeriperalEnum ePeripheral = GPIOEnumToSTM32Enum(eGPIOPort_);
   apstTheGPIOPorts[eGPIOPort_] = NULL;
   return RCC_ResetPeripheralClock(ePeripheral);
}

// -------------------------------------------------------------
BOOL GPIO_SetConfig(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   const GPIOPinConfigurationStruct* pstConfiguration_)
{
   if((apstTheGPIOPorts[eGPIOPort_] == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   (*apstTheGPIOPorts[eGPIOPort_]).MODER |= ((UINT)pstConfiguration_->eMode << (2 * ePin_));
   (*apstTheGPIOPorts[eGPIOPort_]).OTYPER |= ((UINT)pstConfiguration_->eOutputType << ePin_);
   (*apstTheGPIOPorts[eGPIOPort_]).OSPEEDR |= ((UINT)pstConfiguration_->eSpeed << (2 * ePin_));
   (*apstTheGPIOPorts[eGPIOPort_]).PUPDR |= ((UINT)pstConfiguration_->ePUPD << (2 * ePin_));
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_GetConfig(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   GPIOPinConfigurationStruct* pstConfiguration_)
{
   if((apstTheGPIOPorts[eGPIOPort_] == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   pstConfiguration_->eMode = (GPIOPinModeEnum)(((*apstTheGPIOPorts[eGPIOPort_]).MODER >> (2 * ePin_)) & MODER_MASK);
   pstConfiguration_->eOutputType = (GPIOOutputTypeEnum)(((*apstTheGPIOPorts[eGPIOPort_]).OTYPER >> ePin_) & OTYPER_MASK);
   pstConfiguration_->eSpeed = (GPIOSpeedEnum)(((*apstTheGPIOPorts[eGPIOPort_]).OSPEEDR >> (2 * ePin_)) & OSPEEDR_MASK);
   pstConfiguration_->ePUPD = (GPIOPUPDEnum)(((*apstTheGPIOPorts[eGPIOPort_]).PUPDR >> (2 * ePin_)) & PUPDR_MASK);
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_ReadPin(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   GPIOStateEnum* peState_)
{
   if((apstTheGPIOPorts[eGPIOPort_] == NULL) ||
      (peState_ == NULL))
   {
      return FALSE;
   }

   *peState_ = ((*apstTheGPIOPorts[eGPIOPort_]).IDR >> ePin_) & GPIO_HI;

   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_WritePin(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_,
   GPIOStateEnum eState_)
{
   if(apstTheGPIOPorts[eGPIOPort_] == NULL)
   {
      return FALSE;
   }

   if(eState_ == GPIO_LO)
   {
      (*apstTheGPIOPorts[eGPIOPort_]).ODR &= ~(0x01UL << ePin_);
   }
   else
   {
      (*apstTheGPIOPorts[eGPIOPort_]).ODR |= (0x01UL << ePin_);
   }

   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_TogglePin(
   GPIOPortEnum eGPIOPort_,
   GPIOPinEnum ePin_)
{
   if(apstTheGPIOPorts[eGPIOPort_] == NULL)
   {
      return FALSE;
   }

   (*apstTheGPIOPorts[eGPIOPort_]).ODR ^= (0x01UL << ePin_);

   return FALSE;
}
