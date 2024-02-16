// Includes ---------------------------------------------------------------------------------------
#include "device/gpio/gpio.h"
#include "driver/gpio/gpio_driver.h"
#include "driver/rcc/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static GPIORegistersStruct* apstTheGPIOControllers[GPIO_MAX] = {NULL};

// Functions --------------------------------------------------------------------------------------
static STM32F407VGT6_PeriperalEnum GPIOEnumToSTM32Enum(
   GPIOControllerEnum eGPIOController_)
{
   switch(eGPIOController_)
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
   GPIOControllerEnum eGPIOController_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      STM32F407VGT6_PeriperalEnum ePeripheral = GPIOEnumToSTM32Enum(eGPIOController_);
      apstTheGPIOControllers[eGPIOController_] = GetGPIOController(eGPIOController_);
      if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
         (!RCC_EnablePeripheralClock(ePeripheral)))
      {
         return GPIO_Deinitialize(eGPIOController_);
      }
   }
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_Deinitialize(
   GPIOControllerEnum eGPIOController_)
{
   STM32F407VGT6_PeriperalEnum ePeripheral = GPIOEnumToSTM32Enum(eGPIOController_);
   return RCC_ResetPeripheralClock(ePeripheral);
}

// -------------------------------------------------------------
BOOL GPIO_SetConfig(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   const GPIOPinConfigurationStruct* pstConfiguration_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_SetConfigPinMode(eGPIOController_, ePin_, pstConfiguration_->eMode);
   bSuccess &= GPIO_SetConfigPinOutputType(eGPIOController_, ePin_, pstConfiguration_->eOutputType);
   bSuccess &= GPIO_SetConfigPinSpeed(eGPIOController_, ePin_, pstConfiguration_->eSpeed);
   bSuccess &= GPIO_SetConfigPinPUPD(eGPIOController_, ePin_, pstConfiguration_->ePUPD);
   return bSuccess;
}

// -------------------------------------------------------------
BOOL GPIO_GetConfig(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPinConfigurationStruct* pstConfiguration_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (pstConfiguration_ == NULL))
   {
      return FALSE;
   }

   BOOL bSuccess = TRUE;
   bSuccess &= GPIO_GetConfigPinMode(eGPIOController_, ePin_, &pstConfiguration_->eMode);
   bSuccess &= GPIO_GetConfigPinOutputType(eGPIOController_, ePin_, &pstConfiguration_->eOutputType);
   bSuccess &= GPIO_GetConfigPinSpeed(eGPIOController_, ePin_, &pstConfiguration_->eSpeed);
   bSuccess &= GPIO_GetConfigPinPUPD(eGPIOController_, ePin_, &pstConfiguration_->ePUPD);
   return bSuccess;
}

// -------------------------------------------------------------
BOOL GPIO_SetConfigPinMode(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPinModeEnum eMode_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      return FALSE;
   }

   UINT uiRegVal = ((UINT)eMode_ << (2 * ePin_));
   (*apstTheGPIOControllers[eGPIOController_]).MODER |= uiRegVal;
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_GetConfigPinMode(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPinModeEnum* peMode_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (peMode_ == NULL))
   {
      return FALSE;
   }

   UINT uiRegVal = (*apstTheGPIOControllers[eGPIOController_]).MODER;
   *peMode_ = (GPIOPinModeEnum)((uiRegVal >> (2 * ePin_)) & MODER_MASK);
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_SetConfigPinOutputType(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOOutputTypeEnum eOutputType_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      return FALSE;
   }

   UINT uiRegVal = ((UINT)eOutputType_ << ePin_);
   (*apstTheGPIOControllers[eGPIOController_]).OTYPER |= uiRegVal;
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_GetConfigPinOutputType(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOOutputTypeEnum* peOutputType_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (peOutputType_ == NULL))
   {
      return FALSE;
   }

   UINT uiRegVal = (*apstTheGPIOControllers[eGPIOController_]).OTYPER;
   *peOutputType_ = (GPIOOutputTypeEnum)((uiRegVal >> ePin_) & OTYPER_MASK);
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_SetConfigPinSpeed(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOSpeedEnum eSpeed_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      return FALSE;
   }

   UINT uiRegVal = ((UINT)eSpeed_ << (2 * ePin_));
   (*apstTheGPIOControllers[eGPIOController_]).OSPEEDR |= uiRegVal;
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_GetConfigPinSpeed(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOSpeedEnum* peSpeed_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (peSpeed_ == NULL))
   {
      return FALSE;
   }

   UINT uiRegVal = (*apstTheGPIOControllers[eGPIOController_]).OSPEEDR;
   *peSpeed_ = (GPIOSpeedEnum)((uiRegVal >> (2 * ePin_)) & OSPEEDR_MASK);
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_SetConfigPinPUPD(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPUPDEnum ePUPD_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      return FALSE;
   }

   UINT uiRegVal = ((UINT)ePUPD_ << (2 * ePin_));
   (*apstTheGPIOControllers[eGPIOController_]).PUPDR |= uiRegVal;
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_GetConfigPinPUPD(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOPUPDEnum* pePUPD_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (pePUPD_ == NULL))
   {
      return FALSE;
   }

   UINT uiRegVal = (*apstTheGPIOControllers[eGPIOController_]).PUPDR;
   *pePUPD_ = (GPIOPUPDEnum)((uiRegVal >> (2 * ePin_)) & PUPDR_MASK);
   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_ReadPin(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOStateEnum* peState_)
{
   if((apstTheGPIOControllers[eGPIOController_] == NULL) ||
      (peState_ == NULL))
   {
      return FALSE;
   }

   *peState_ = ((*apstTheGPIOControllers[eGPIOController_]).ODR >> ePin_) & GPIO_HI;

   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_WritePin(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_,
   GPIOStateEnum eState_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      return FALSE;
   }

   if(eState_ == GPIO_LO)
   {
      (*apstTheGPIOControllers[eGPIOController_]).ODR &= ~(0x01UL << ePin_);
   }
   else
   {
      (*apstTheGPIOControllers[eGPIOController_]).ODR |= (0x01UL << ePin_);
   }

   return TRUE;
}

// -------------------------------------------------------------
BOOL GPIO_TogglePin(
   GPIOControllerEnum eGPIOController_,
   GPIOPinEnum ePin_)
{
   if(apstTheGPIOControllers[eGPIOController_] == NULL)
   {
      return FALSE;
   }

   (*apstTheGPIOControllers[eGPIOController_]).ODR ^= (0x01UL << ePin_);

   return FALSE;
}
