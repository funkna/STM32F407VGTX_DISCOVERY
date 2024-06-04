#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

//--------------------------------------------------------------
// Enumerations for all peripherals.
//--------------------------------------------------------------
typedef enum
{
   PERIPHERAL_INVALID,
   PERIPHERAL_ADC1,
   PERIPHERAL_ADC2,
   PERIPHERAL_ADC3,
   PERIPHERAL_ADC_COMMON,
   PERIPHERAL_BKPSRAM,
   PERIPHERAL_CAN1,
   PERIPHERAL_CAN2,
   PERIPHERAL_CRC,
   PERIPHERAL_DAC,
   PERIPHERAL_DCMI,
   PERIPHERAL_DMA1,
   PERIPHERAL_DMA2,
   PERIPHERAL_ETH_MAC,
   PERIPHERAL_EXTI,
   PERIPHERAL_FLASH,
   PERIPHERAL_FSMC_B1,
   PERIPHERAL_FSMC_B2,
   PERIPHERAL_FSMC_B3,
   PERIPHERAL_FSMC_B4,
   PERIPHERAL_FSMC_CR,
   PERIPHERAL_GPIOA,
   PERIPHERAL_GPIOB,
   PERIPHERAL_GPIOC,
   PERIPHERAL_GPIOD,
   PERIPHERAL_GPIOE,
   PERIPHERAL_GPIOF,
   PERIPHERAL_GPIOG,
   PERIPHERAL_GPIOH,
   PERIPHERAL_GPIOI,
   PERIPHERAL_I2C1,
   PERIPHERAL_I2C2,
   PERIPHERAL_I2C3,
   PERIPHERAL_I2S2EXT,
   PERIPHERAL_I2S3EXT,
   PERIPHERAL_IWDG,
   PERIPHERAL_PWR,
   PERIPHERAL_RCC,
   PERIPHERAL_RNG,
   PERIPHERAL_RTC_BKP,
   PERIPHERAL_SDIO,
   PERIPHERAL_SPI1,
   PERIPHERAL_SPI2_I2S2,
   PERIPHERAL_SPI3_I2S3,
   PERIPHERAL_SYSCFG,
   PERIPHERAL_TIM1,
   PERIPHERAL_TIM2,
   PERIPHERAL_TIM3,
   PERIPHERAL_TIM4,
   PERIPHERAL_TIM5,
   PERIPHERAL_TIM6,
   PERIPHERAL_TIM7,
   PERIPHERAL_TIM8,
   PERIPHERAL_TIM9,
   PERIPHERAL_TIM10,
   PERIPHERAL_TIM11,
   PERIPHERAL_TIM12,
   PERIPHERAL_TIM13,
   PERIPHERAL_TIM14,
   PERIPHERAL_USART1,
   PERIPHERAL_USART2,
   PERIPHERAL_USART3,
   PERIPHERAL_UART4,
   PERIPHERAL_UART5,
   PERIPHERAL_USART6,
   PERIPHERAL_USB_OTG_FS,
   PERIPHERAL_USB_OTG_HS,
   PERIPHERAL_WWDG,
   STM32F407VGT6_PERIPHERAL_MAX
} STM32F407VGT6_PeriperalEnum;

// -------------------------------------------------------------
// ADC Controller Enumeration
// -------------------------------------------------------------
typedef enum
{
   ADC1 = 0,
   ADC2,
   ADC3,
   ADC_MAX
} ADCControllerEnum;

// -------------------------------------------------------------
// GPIO Port Enumeration
// -------------------------------------------------------------
typedef enum
{
   GPIO_PORT_A = 0,
   GPIO_PORT_B,
   GPIO_PORT_C,
   GPIO_PORT_D,
   GPIO_PORT_E,
   GPIO_PORT_F,
   GPIO_PORT_G,
   GPIO_PORT_H,
   GPIO_PORT_I,
   GPIO_PORT_MAX
} GPIOPortEnum;

// -------------------------------------------------------------
// GPIO Pin Enumeration
// -------------------------------------------------------------
typedef enum
{
   GPIO_PIN_0 = 0,
   GPIO_PIN_1,
   GPIO_PIN_2,
   GPIO_PIN_3,
   GPIO_PIN_4,
   GPIO_PIN_5,
   GPIO_PIN_6,
   GPIO_PIN_7,
   GPIO_PIN_8,
   GPIO_PIN_9,
   GPIO_PIN_10,
   GPIO_PIN_11,
   GPIO_PIN_12,
   GPIO_PIN_13,
   GPIO_PIN_14,
   GPIO_PIN_15,
   GPIO_PIN_MAX,
   GPIO_PIN_NONE= 0xFFFFFFFF
} GPIOPinEnum;

// -------------------------------------------------------------
// I2C Controller Enumeration
// -------------------------------------------------------------
typedef enum
{
   I2C1 = 0,
   I2C2,
   I2C3,
   I2C_MAX
} I2CControllerEnum;

// -------------------------------------------------------------
// SPI Controller Enumeration
// -------------------------------------------------------------
typedef enum
{
   SPI1 = 0,
   SPI2,
   SPI3,
   SPI_MAX
} SPIControllerEnum;

// -------------------------------------------------------------
// USART Controller Enumeration
// -------------------------------------------------------------
typedef enum
{
   USART1 = 0,
   USART2,
   USART3,
   USART4,
   USART5,
   USART6,
   USART_MAX
} USARTControllerEnum;

#endif // PERIPHERALS_H_