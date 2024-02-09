// Includes ---------------------------------------------------------------------------------------
#include "device/rcc/rcc.h"
#include "driver/rcc/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static RCCRegistersStruct* pstTheRCCController = NULL;
static BOOL bRCCInitialized = FALSE;

// Functions --------------------------------------------------------------------------------------
BOOL RCC_Initialize()
{
   if(!bRCCInitialized)
   {
      pstTheRCCController = GetRCCController();
      bRCCInitialized = (pstTheRCCController != NULL);
   }
   return bRCCInitialized;
}

BOOL RCC_EnablePeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_)
{
   if(pstTheRCCController == NULL)
   {
      return FALSE;
   }

   BOOL bEnabled = TRUE;
   switch(ePeripheral_)
   {
      case DAC:
         (*pstTheRCCController).APB1ENR |= APB1_DAC;
         break;
      case PWR:
         (*pstTheRCCController).APB1ENR |= APB1_PWR;
         break;
      case CAN2:
         (*pstTheRCCController).APB1ENR |= APB1_CAN2;
         break;
      case CAN1:
         (*pstTheRCCController).APB1ENR |= APB1_CAN1;
         break;
      case I2C3:
         (*pstTheRCCController).APB1ENR |= APB1_I2C3;
         break;
      case I2C2:
         (*pstTheRCCController).APB1ENR |= APB1_I2C2;
         break;
      case I2C1:
         (*pstTheRCCController).APB1ENR |= APB1_I2C1;
         break;
      case UART5:
         (*pstTheRCCController).APB1ENR |= APB1_UART5;
         break;
      case UART4:
         (*pstTheRCCController).APB1ENR |= APB1_UART4;
         break;
      case USART3:
         (*pstTheRCCController).APB1ENR |= APB1_USART3;
         break;
      case USART2:
         (*pstTheRCCController).APB1ENR |= APB1_USART2;
         break;
      case SPI3_I2S3:
         (*pstTheRCCController).APB1ENR |= APB1_SPI3;
         break;
      case SPI2_I2S2:
         (*pstTheRCCController).APB1ENR |= APB1_SPI2;
         break;
      case WWDG:
         (*pstTheRCCController).APB1ENR |= APB1_WWDG;
         break;
      case TIM14:
         (*pstTheRCCController).APB1ENR |= APB1_TIM14;
         break;
      case TIM13:
         (*pstTheRCCController).APB1ENR |= APB1_TIM13;
         break;
      case TIM12:
         (*pstTheRCCController).APB1ENR |= APB1_TIM12;
         break;
      case TIM7:
         (*pstTheRCCController).APB1ENR |= APB1_TIM7;
         break;
      case TIM6:
         (*pstTheRCCController).APB1ENR |= APB1_TIM6;
         break;
      case TIM5:
         (*pstTheRCCController).APB1ENR |= APB1_TIM5;
         break;
      case TIM4:
         (*pstTheRCCController).APB1ENR |= APB1_TIM4;
         break;
      case TIM3:
         (*pstTheRCCController).APB1ENR |= APB1_TIM3;
         break;
      case TIM2:
         (*pstTheRCCController).APB1ENR |= APB1_TIM2;
         break;
      case TIM11:
         (*pstTheRCCController).APB2ENR |= APB2_TIM11;
         break;
      case TIM10:
         (*pstTheRCCController).APB2ENR |= APB2_TIM10;
         break;
      case TIM9:
         (*pstTheRCCController).APB2ENR |= APB2_TIM9;
         break;
      case SYSCFG:
         (*pstTheRCCController).APB2ENR |= APB2_SYSCFG;
         break;
      case SPI1:
         (*pstTheRCCController).APB2ENR |= APB2_SPI1;
         break;
      case SDIO:
         (*pstTheRCCController).APB2ENR |= APB2_SDIO;
         break;
      case ADC3:
         (*pstTheRCCController).APB2ENR |= APB2_ADC3;
         break;
      case ADC2:
         (*pstTheRCCController).APB2ENR |= APB2_ADC2;
         break;
      case ADC1:
         (*pstTheRCCController).APB2ENR |= APB2_ADC1;
         break;
      case USART6:
         (*pstTheRCCController).APB2ENR |= APB2_USART6;
         break;
      case USART1:
         (*pstTheRCCController).APB2ENR |= APB2_USART1;
         break;
      case TIM8:
         (*pstTheRCCController).APB2ENR |= APB2_TIM8;
         break;
      case TIM1:
         (*pstTheRCCController).APB2ENR |= APB2_TIM1;
         break;
      case USB_OTG_HS:
         (*pstTheRCCController).AHB1ENR |= AHB1_OTGHS;
         break;
      case ETH_MAC:
         (*pstTheRCCController).AHB1ENR |= AHB1_ETHMAC;
         break;
      case DMA2:
         (*pstTheRCCController).AHB1ENR |= AHB1_DMA2;
         break;
      case DMA1:
         (*pstTheRCCController).AHB1ENR |= AHB1_DMA1;
         break;
      case CRC:
         (*pstTheRCCController).AHB1ENR |= AHB1_CRC;
         break;
      case GPIOI:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOI;
         break;
      case GPIOH:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOH;
         break;
      case GPIOG:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOG;
         break;
      case GPIOF:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOF;
         break;
      case GPIOE:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOE;
         break;
      case GPIOD:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOD;
         break;
      case GPIOC:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOC;
         break;
      case GPIOB:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOB;
         break;
      case GPIOA:
         (*pstTheRCCController).AHB1ENR |= AHB1_GPIOA;
         break;
      default:
         bEnabled = FALSE;
         break;
   }

   return bEnabled;
}


BOOL RCC_ResetPeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_)
{
   if(pstTheRCCController == NULL)
   {
      return FALSE;
   }

   BOOL bReset = TRUE;
   switch(ePeripheral_)
   {
      case DAC:
         (*pstTheRCCController).APB1RSTR |= APB1_DAC;
         break;
      case PWR:
         (*pstTheRCCController).APB1RSTR |= APB1_PWR;
         break;
      case CAN2:
         (*pstTheRCCController).APB1RSTR |= APB1_CAN2;
         break;
      case CAN1:
         (*pstTheRCCController).APB1RSTR |= APB1_CAN1;
         break;
      case I2C3:
         (*pstTheRCCController).APB1RSTR |= APB1_I2C3;
         break;
      case I2C2:
         (*pstTheRCCController).APB1RSTR |= APB1_I2C2;
         break;
      case I2C1:
         (*pstTheRCCController).APB1RSTR |= APB1_I2C1;
         break;
      case UART5:
         (*pstTheRCCController).APB1RSTR |= APB1_UART5;
         break;
      case UART4:
         (*pstTheRCCController).APB1RSTR |= APB1_UART4;
         break;
      case USART3:
         (*pstTheRCCController).APB1RSTR |= APB1_USART3;
         break;
      case USART2:
         (*pstTheRCCController).APB1RSTR |= APB1_USART2;
         break;
      case SPI3_I2S3:
         (*pstTheRCCController).APB1RSTR |= APB1_SPI3;
         break;
      case SPI2_I2S2:
         (*pstTheRCCController).APB1RSTR |= APB1_SPI2;
         break;
      case WWDG:
         (*pstTheRCCController).APB1RSTR |= APB1_WWDG;
         break;
      case TIM14:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM14;
         break;
      case TIM13:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM13;
         break;
      case TIM12:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM12;
         break;
      case TIM7:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM7;
         break;
      case TIM6:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM6;
         break;
      case TIM5:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM5;
         break;
      case TIM4:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM4;
         break;
      case TIM3:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM3;
         break;
      case TIM2:
         (*pstTheRCCController).APB1RSTR |= APB1_TIM2;
         break;
      case TIM11:
         (*pstTheRCCController).APB2RSTR |= APB2_TIM11;
         break;
      case TIM10:
         (*pstTheRCCController).APB2RSTR |= APB2_TIM10;
         break;
      case TIM9:
         (*pstTheRCCController).APB2RSTR |= APB2_TIM9;
         break;
      case SYSCFG:
         (*pstTheRCCController).APB2RSTR |= APB2_SYSCFG;
         break;
      case SPI1:
         (*pstTheRCCController).APB2RSTR |= APB2_SPI1;
         break;
      case SDIO:
         (*pstTheRCCController).APB2RSTR |= APB2_SDIO;
         break;
      case ADC3:
         (*pstTheRCCController).APB2RSTR |= APB2_ADC3;
         break;
      case ADC2:
         (*pstTheRCCController).APB2RSTR |= APB2_ADC2;
         break;
      case ADC1:
         (*pstTheRCCController).APB2RSTR |= APB2_ADC1;
         break;
      case USART6:
         (*pstTheRCCController).APB2RSTR |= APB2_USART6;
         break;
      case USART1:
         (*pstTheRCCController).APB2RSTR |= APB2_USART1;
         break;
      case TIM8:
         (*pstTheRCCController).APB2RSTR |= APB2_TIM8;
         break;
      case TIM1:
         (*pstTheRCCController).APB2RSTR |= APB2_TIM1;
         break;
      case USB_OTG_HS:
         (*pstTheRCCController).AHB1RSTR |= AHB1_OTGHS;
         break;
      case ETH_MAC:
         (*pstTheRCCController).AHB1RSTR |= AHB1_ETHMAC;
         break;
      case DMA2:
         (*pstTheRCCController).AHB1RSTR |= AHB1_DMA2;
         break;
      case DMA1:
         (*pstTheRCCController).AHB1RSTR |= AHB1_DMA1;
         break;
      case CRC:
         (*pstTheRCCController).AHB1RSTR |= AHB1_CRC;
         break;
      case GPIOI:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOI;
         break;
      case GPIOH:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOH;
         break;
      case GPIOG:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOG;
         break;
      case GPIOF:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOF;
         break;
      case GPIOE:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOE;
         break;
      case GPIOD:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOD;
         break;
      case GPIOC:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOC;
         break;
      case GPIOB:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOB;
         break;
      case GPIOA:
         (*pstTheRCCController).AHB1RSTR |= AHB1_GPIOA;
         break;
      default:
         bReset = FALSE;
         break;
   }

   return bReset;
}
