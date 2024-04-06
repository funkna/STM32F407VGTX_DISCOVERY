// Includes ---------------------------------------------------------------------------------------
#include "devices/rcc.h"
#include "drivers/rcc_driver.h"

// Defines ----------------------------------------------------------------------------------------
// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static RCCRegistersStruct* pstTheRCCRegisters = NULL;

// Functions --------------------------------------------------------------------------------------

//--------------------------------------------------------------
BOOL RCC_Initialize()
{
   pstTheRCCRegisters = GetRCCController();
   return (pstTheRCCRegisters != NULL);
}

//--------------------------------------------------------------
BOOL RCC_EnablePeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_)
{
   if(pstTheRCCRegisters == NULL)
   {
      return FALSE;
   }

   BOOL bEnabled = TRUE;
   switch(ePeripheral_)
   {
      case PERIPHERAL_DAC:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_DAC;
         break;
      }
      case PERIPHERAL_PWR:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_PWR;
         break;
      }
      case PERIPHERAL_CAN2:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_CAN2;
         break;
      }
      case PERIPHERAL_CAN1:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_CAN1;
         break;
      }
      case PERIPHERAL_I2C3:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_I2C3;
         break;
      }
      case PERIPHERAL_I2C2:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_I2C2;
         break;
      }
      case PERIPHERAL_I2C1:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_I2C1;
         break;
      }
      case PERIPHERAL_UART5:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_UART5;
         break;
      }
      case PERIPHERAL_UART4:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_UART4;
         break;
      }
      case PERIPHERAL_USART3:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_USART3;
         break;
      }
      case PERIPHERAL_USART2:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_USART2;
         break;
      }
      case PERIPHERAL_SPI3_I2S3:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_SPI3;
         break;
      }
      case PERIPHERAL_SPI2_I2S2:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_SPI2;
         break;
      }
      case PERIPHERAL_WWDG:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_WWDG;
         break;
      }
      case PERIPHERAL_TIM14:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM14;
         break;
      }
      case PERIPHERAL_TIM13:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM13;
         break;
      }
      case PERIPHERAL_TIM12:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM12;
         break;
      }
      case PERIPHERAL_TIM7:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM7;
         break;
      }
      case PERIPHERAL_TIM6:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM6;
         break;
      }
      case PERIPHERAL_TIM5:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM5;
         break;
      }
      case PERIPHERAL_TIM4:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM4;
         break;
      }
      case PERIPHERAL_TIM3:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM3;
         break;
      }
      case PERIPHERAL_TIM2:
      {
         (*pstTheRCCRegisters).APB1ENR |= APB1_TIM2;
         break;
      }
      case PERIPHERAL_TIM11:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_TIM11;
         break;
      }
      case PERIPHERAL_TIM10:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_TIM10;
         break;
      }
      case PERIPHERAL_TIM9:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_TIM9;
         break;
      }
      case PERIPHERAL_SYSCFG:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_SYSCFG;
         break;
      }
      case PERIPHERAL_SPI1:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_SPI1;
         break;
      }
      case PERIPHERAL_SDIO:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_SDIO;
         break;
      }
      case PERIPHERAL_ADC3:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_ADC3;
         break;
      }
      case PERIPHERAL_ADC2:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_ADC2;
         break;
      }
      case PERIPHERAL_ADC1:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_ADC1;
         break;
      }
      case PERIPHERAL_USART6:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_USART6;
         break;
      }
      case PERIPHERAL_USART1:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_USART1;
         break;
      }
      case PERIPHERAL_TIM8:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_TIM8;
         break;
      }
      case PERIPHERAL_TIM1:
      {
         (*pstTheRCCRegisters).APB2ENR |= APB2_TIM1;
         break;
      }
      case PERIPHERAL_USB_OTG_HS:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_OTGHS;
         break;
      }
      case PERIPHERAL_ETH_MAC:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_ETHMAC;
         break;
      }
      case PERIPHERAL_DMA2:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_DMA2;
         break;
      }
      case PERIPHERAL_DMA1:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_DMA1;
         break;
      }
      case PERIPHERAL_CRC:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_CRC;
         break;
      }
      case PERIPHERAL_GPIOI:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOI;
         break;
      }
      case PERIPHERAL_GPIOH:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOH;
         break;
      }
      case PERIPHERAL_GPIOG:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOG;
         break;
      }
      case PERIPHERAL_GPIOF:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOF;
         break;
      }
      case PERIPHERAL_GPIOE:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOE;
         break;
      }
      case PERIPHERAL_GPIOD:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOD;
         break;
      }
      case PERIPHERAL_GPIOC:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOC;
         break;
      }
      case PERIPHERAL_GPIOB:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOB;
         break;
      }
      case PERIPHERAL_GPIOA:
      {
         (*pstTheRCCRegisters).AHB1ENR |= AHB1_GPIOA;
         break;
      }
      default:
      {
         bEnabled = FALSE;
         break;
      }
   }

   return bEnabled;
}

//--------------------------------------------------------------
BOOL RCC_ResetPeripheralClock(
   STM32F407VGT6_PeriperalEnum ePeripheral_)
{
   if(pstTheRCCRegisters == NULL)
   {
      return FALSE;
   }

   BOOL bReset = TRUE;
   switch(ePeripheral_)
   {
      case PERIPHERAL_DAC:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_DAC;
         break;
      }
      case PERIPHERAL_PWR:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_PWR;
         break;
      }
      case PERIPHERAL_CAN2:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_CAN2;
         break;
      }
      case PERIPHERAL_CAN1:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_CAN1;
         break;
      }
      case PERIPHERAL_I2C3:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_I2C3;
         break;
      }
      case PERIPHERAL_I2C2:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_I2C2;
         break;
      }
      case PERIPHERAL_I2C1:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_I2C1;
         break;
      }
      case PERIPHERAL_UART5:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_UART5;
         break;
      }
      case PERIPHERAL_UART4:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_UART4;
         break;
      }
      case PERIPHERAL_USART3:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_USART3;
         break;
      }
      case PERIPHERAL_USART2:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_USART2;
         break;
      }
      case PERIPHERAL_SPI3_I2S3:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_SPI3;
         break;
      }
      case PERIPHERAL_SPI2_I2S2:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_SPI2;
         break;
      }
      case PERIPHERAL_WWDG:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_WWDG;
         break;
      }
      case PERIPHERAL_TIM14:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM14;
         break;
      }
      case PERIPHERAL_TIM13:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM13;
         break;
      }
      case PERIPHERAL_TIM12:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM12;
         break;
      }
      case PERIPHERAL_TIM7:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM7;
         break;
      }
      case PERIPHERAL_TIM6:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM6;
         break;
      }
      case PERIPHERAL_TIM5:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM5;
         break;
      }
      case PERIPHERAL_TIM4:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM4;
         break;
      }
      case PERIPHERAL_TIM3:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM3;
         break;
      }
      case PERIPHERAL_TIM2:
      {
         (*pstTheRCCRegisters).APB1RSTR |= APB1_TIM2;
         break;
      }
      case PERIPHERAL_TIM11:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_TIM11;
         break;
      }
      case PERIPHERAL_TIM10:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_TIM10;
         break;
      }
      case PERIPHERAL_TIM9:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_TIM9;
         break;
      }
      case PERIPHERAL_SYSCFG:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_SYSCFG;
         break;
      }
      case PERIPHERAL_SPI1:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_SPI1;
         break;
      }
      case PERIPHERAL_SDIO:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_SDIO;
         break;
      }
      case PERIPHERAL_ADC3:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_ADC3;
         break;
      }
      case PERIPHERAL_ADC2:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_ADC2;
         break;
      }
      case PERIPHERAL_ADC1:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_ADC1;
         break;
      }
      case PERIPHERAL_USART6:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_USART6;
         break;
      }
      case PERIPHERAL_USART1:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_USART1;
         break;
      }
      case PERIPHERAL_TIM8:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_TIM8;
         break;
      }
      case PERIPHERAL_TIM1:
      {
         (*pstTheRCCRegisters).APB2RSTR |= APB2_TIM1;
         break;
      }
      case PERIPHERAL_USB_OTG_HS:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_OTGHS;
         break;
      }
      case PERIPHERAL_ETH_MAC:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_ETHMAC;
         break;
      }
      case PERIPHERAL_DMA2:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_DMA2;
         break;
      }
      case PERIPHERAL_DMA1:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_DMA1;
         break;
      }
      case PERIPHERAL_CRC:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_CRC;
         break;
      }
      case PERIPHERAL_GPIOI:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOI;
         break;
      }
      case PERIPHERAL_GPIOH:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOH;
         break;
      }
      case PERIPHERAL_GPIOG:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOG;
         break;
      }
      case PERIPHERAL_GPIOF:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOF;
         break;
      }
      case PERIPHERAL_GPIOE:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOE;
         break;
      }
      case PERIPHERAL_GPIOD:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOD;
         break;
      }
      case PERIPHERAL_GPIOC:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOC;
         break;
      }
      case PERIPHERAL_GPIOB:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOB;
         break;
      }
      case PERIPHERAL_GPIOA:
      {
         (*pstTheRCCRegisters).AHB1RSTR |= AHB1_GPIOA;
         break;
      }
      default:
      {
         bReset = FALSE;
         break;
      }
   }

   return bReset;
}
