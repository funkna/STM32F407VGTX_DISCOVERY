#ifndef STM32F407VGT6_H_
#define STM32F407VGT6_H_

//--------------------------------------------------------------
// Internal oscillator frequency
//--------------------------------------------------------------
#define HSI_RC_CLK_FREQ_MHZ      (16)
#define HSE_RC_CLK_FREQ_MHZ      (8)

//--------------------------------------------------------------
// Base addresses and sizes for memory blocks.
//--------------------------------------------------------------
#define MEMORY_BLOCK_SRAM2_SIZE                    (0x00004000UL)
#define MEMORY_BLOCK_SRAM2_ADDRESS                 (0x2001C000UL)
#define MEMORY_BLOCK_SRAM1_SIZE                    (0x0001C000UL)
#define MEMORY_BLOCK_SRAM1_ADDRESS                 (0x20000000UL)
#define MEMORY_BLOCK_OTP_SIZE                      (0x00007A10UL)
#define MEMORY_BLOCK_OTP_ADDRESS                   (0x1FFF0000UL)
#define MEMORY_BLOCK_CCM_SRAM_SIZE                 (0x00010000UL)
#define MEMORY_BLOCK_CCM_SRAM_ADDRESS              (0x10000000UL)
#define MEMORY_BLOCK_FLASH_SIZE                    (0x00100000UL)
#define MEMORY_BLOCK_FLASH_ADDRESS                 (0x08000000UL)

//--------------------------------------------------------------
// Base addresses and sizes for peripheral busses.
//--------------------------------------------------------------
#define BUS_CORTEX_M4_SIZE                         (0x00100000UL)
#define BUS_CORTEX_M4_ADDRESS                      (0xE0000000UL)
#define BUS_AHB3_SIZE                              (0x40001000UL)
#define BUS_AHB3_ADDRESS                           (0x60000000UL)
#define BUS_AHB2_SIZE                              (0x00060C00UL)
#define BUS_AHB2_ADDRESS                           (0x50000000UL)
#define BUS_AHB1_SIZE                              (0x00060000UL)
#define BUS_AHB1_ADDRESS                           (0x40020000UL)
#define BUS_APB2_SIZE                              (0x00005800UL)
#define BUS_APB2_ADDRESS                           (0x40010000UL)
#define BUS_APB1_SIZE                              (0x00008000UL)
#define BUS_APB1_ADDRESS                           (0x40000000UL)

//--------------------------------------------------------------
// Base addresses for ARM Cortex-M4 peripheral controllers.
//--------------------------------------------------------------
// #define PERIPHERAL_ADDRESS_FPU                     (UL)
// #define PERIPHERAL_ADDRESS_MPU                     (UL)
#define PERIPHERAL_ADDRESS_SYSTICK                 (0xE000E010UL)
// #define PERIPHERAL_ADDRESS_SCB                     (UL)
#define PERIPHERAL_ADDRESS_NVIC                    (0xE000E100UL)

//--------------------------------------------------------------
// Base addresses for STM32F407VGT6 peripheral controllers.
//--------------------------------------------------------------
#define PERIPHERAL_ADDRESS_FSMC_CR                 (0xA0000000UL)
#define PERIPHERAL_ADDRESS_FSMC_B4                 (0x90000000UL)
#define PERIPHERAL_ADDRESS_FSMC_B3                 (0x80000000UL)
#define PERIPHERAL_ADDRESS_FSMC_B2                 (0x70000000UL)
#define PERIPHERAL_ADDRESS_FSMC_B1                 (0x60000000UL)
#define PERIPHERAL_ADDRESS_RNG                     (0x50060800UL)
#define PERIPHERAL_ADDRESS_DCMI                    (0x50050000UL)
#define PERIPHERAL_ADDRESS_USB_OTG_FS              (0x50000000UL)
#define PERIPHERAL_ADDRESS_USB_OTG_HS              (0x40040000UL)
#define PERIPHERAL_ADDRESS_ETH_MAC                 (0x40028000UL)
#define PERIPHERAL_ADDRESS_DMA2                    (0x40026400UL)
#define PERIPHERAL_ADDRESS_DMA1                    (0x40026000UL)
#define PERIPHERAL_ADDRESS_BKPSRAM                 (0x40024000UL)
#define PERIPHERAL_ADDRESS_FLASH                   (0x40023C00UL)
#define PERIPHERAL_ADDRESS_RCC                     (0x40023800UL)
#define PERIPHERAL_ADDRESS_CRC                     (0x40023000UL)
#define PERIPHERAL_ADDRESS_GPIOI                   (0x40022000UL)
#define PERIPHERAL_ADDRESS_GPIOH                   (0x40021C00UL)
#define PERIPHERAL_ADDRESS_GPIOG                   (0x40021800UL)
#define PERIPHERAL_ADDRESS_GPIOF                   (0x40021400UL)
#define PERIPHERAL_ADDRESS_GPIOE                   (0x40021000UL)
#define PERIPHERAL_ADDRESS_GPIOD                   (0x40020C00UL)
#define PERIPHERAL_ADDRESS_GPIOC                   (0x40020800UL)
#define PERIPHERAL_ADDRESS_GPIOB                   (0x40020400UL)
#define PERIPHERAL_ADDRESS_GPIOA                   (0x40020000UL)
#define PERIPHERAL_ADDRESS_TIM11                   (0x40014800UL)
#define PERIPHERAL_ADDRESS_TIM10                   (0x40014400UL)
#define PERIPHERAL_ADDRESS_TIM9                    (0x40014000UL)
#define PERIPHERAL_ADDRESS_EXTI                    (0x40013C00UL)
#define PERIPHERAL_ADDRESS_SYSCFG                  (0x40013800UL)
#define PERIPHERAL_ADDRESS_SPI1                    (0x40013000UL)
#define PERIPHERAL_ADDRESS_SDIO                    (0x40012C00UL)
#define PERIPHERAL_ADDRESS_ADC_COMMON              (0x40012300UL)
#define PERIPHERAL_ADDRESS_ADC3                    (0x40012200UL)
#define PERIPHERAL_ADDRESS_ADC2                    (0x40012100UL)
#define PERIPHERAL_ADDRESS_ADC1                    (0x40012000UL)
#define PERIPHERAL_ADDRESS_USART6                  (0x40011400UL)
#define PERIPHERAL_ADDRESS_USART1                  (0x40011000UL)
#define PERIPHERAL_ADDRESS_TIM8                    (0x40010400UL)
#define PERIPHERAL_ADDRESS_TIM1                    (0x40010000UL)
#define PERIPHERAL_ADDRESS_DAC                     (0x40007400UL)
#define PERIPHERAL_ADDRESS_PWR                     (0x40007000UL)
#define PERIPHERAL_ADDRESS_CAN2                    (0x40006800UL)
#define PERIPHERAL_ADDRESS_CAN1                    (0x40006400UL)
#define PERIPHERAL_ADDRESS_I2C3                    (0x40005C00UL)
#define PERIPHERAL_ADDRESS_I2C2                    (0x40005800UL)
#define PERIPHERAL_ADDRESS_I2C1                    (0x40005400UL)
#define PERIPHERAL_ADDRESS_UART5                   (0x40005000UL)
#define PERIPHERAL_ADDRESS_UART4                   (0x40004C00UL)
#define PERIPHERAL_ADDRESS_USART3                  (0x40004800UL)
#define PERIPHERAL_ADDRESS_USART2                  (0x40004400UL)
#define PERIPHERAL_ADDRESS_I2S3EXT                 (0x40004000UL)
#define PERIPHERAL_ADDRESS_SPI3_I2S3               (0x40003C00UL)
#define PERIPHERAL_ADDRESS_SPI2_I2S2               (0x40003800UL)
#define PERIPHERAL_ADDRESS_I2S2EXT                 (0x40003400UL)
#define PERIPHERAL_ADDRESS_IWDG                    (0x40003000UL)
#define PERIPHERAL_ADDRESS_WWDG                    (0x40002C00UL)
#define PERIPHERAL_ADDRESS_RTC_BKP                 (0x40002800UL)
#define PERIPHERAL_ADDRESS_TIM14                   (0x40002000UL)
#define PERIPHERAL_ADDRESS_TIM13                   (0x40001C00UL)
#define PERIPHERAL_ADDRESS_TIM12                   (0x40001800UL)
#define PERIPHERAL_ADDRESS_TIM7                    (0x40001400UL)
#define PERIPHERAL_ADDRESS_TIM6                    (0x40001000UL)
#define PERIPHERAL_ADDRESS_TIM5                    (0x40000C00UL)
#define PERIPHERAL_ADDRESS_TIM4                    (0x40000800UL)
#define PERIPHERAL_ADDRESS_TIM3                    (0x40000400UL)
#define PERIPHERAL_ADDRESS_TIM2                    (0x40000000UL)

#endif // STM32F407VGT6_H_
