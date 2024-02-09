#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

//--------------------------------------------------------------
// Enumerations for all peripherals.
//--------------------------------------------------------------
typedef enum
{
   INVALID,
   ADC1, ADC2, ADC3, ADC_COMMON,
   BKPSRAM,
   CAN1, CAN2,
   CRC,
   DAC,
   DCMI,
   DMA1, DMA2,
   ETH_MAC,
   EXTI,
   FLASH,
   FSMC_B1, FSMC_B2, FSMC_B3, FSMC_B4, FSMC_CR,
   GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI,
   I2C1, I2C2, I2C3,
   I2S2EXT, I2S3EXT,
   IWDG,
   PWR,
   RCC,
   RNG,
   RTC_BKP,
   SDIO,
   SPI1, SPI2_I2S2, SPI3_I2S3,
   SYSCFG,
   TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, TIM8, TIM9, TIM10, TIM11, TIM12, TIM13, TIM14,
   USART1, USART2, USART3, UART4, UART5, USART6,
   USB_OTG_FS, USB_OTG_HS,
   WWDG,
   STM32F407VGT6_PERIPHERAL_MAX
} STM32F407VGT6_PeriperalEnum;

// -------------------------------------------------------------
// ADC Controller Enumeration
// -------------------------------------------------------------
typedef enum
{
   ADC_ADC1 = 0,
   ADC_ADC2,
   ADC_ADC3,
   ADC_MAX
} ADCControllerEnum;

// -------------------------------------------------------------
// GPIO Controller Enumeration
// -------------------------------------------------------------
typedef enum
{
   GPIO_GPIOA = 0,
   GPIO_GPIOB,
   GPIO_GPIOC,
   GPIO_GPIOD,
   GPIO_GPIOE,
   GPIO_GPIOF,
   GPIO_GPIOG,
   GPIO_GPIOH,
   GPIO_GPIOI,
   GPIO_MAX
} GPIOControllerEnum;

#endif // PERIPHERALS_H_