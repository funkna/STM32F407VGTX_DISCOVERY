// Redundancy Prevention --------------------------------------------------------------------------
#ifndef RCC_H_
#define RCC_H_

// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "peripherals.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

//--------------------------------------------------------------
// RCC Controller Register Bitmasks
//--------------------------------------------------------------
#define CFGR_MCO2             (0x03UL << 30)
#define CFGR_MCO2PRE          (0x07UL << 27)
#define CFGR_MCO1PRE          (0x07UL << 24)
#define CFGR_I2SSRC           (0x01UL << 23)
#define CFGR_MCO1             (0x03UL << 21)
#define CFGR_RTCPRE           (0x1FUL << 16)
#define CFGR_PPRE2            (0x07UL << 13)
#define CFGR_PPRE1            (0x07UL << 10)
#define CFGR_PPRE1_OFFSET     (10)
#define CFGR_HPRE             (0x0FUL << 4)
#define CFGR_HPRE_OFFSET      (4)
#define CFGR_SWS              (0x03UL << 2)
#define CFGR_SWS_OFFSET       (2)
#define CFGR_SW               (0x03UL << 0)

#define APB1_DAC              (0x01UL << 29)
#define APB1_PWR              (0x01UL << 28)
#define APB1_CAN2             (0x01UL << 26)
#define APB1_CAN1             (0x01UL << 25)
#define APB1_I2C3             (0x01UL << 23)
#define APB1_I2C2             (0x01UL << 22)
#define APB1_I2C1             (0x01UL << 21)
#define APB1_UART5            (0x01UL << 20)
#define APB1_UART4            (0x01UL << 19)
#define APB1_USART3           (0x01UL << 18)
#define APB1_USART2           (0x01UL << 17)
#define APB1_SPI3             (0x01UL << 15)
#define APB1_SPI2             (0x01UL << 14)
#define APB1_WWDG             (0x01UL << 11)
#define APB1_TIM14            (0x01UL << 8)
#define APB1_TIM13            (0x01UL << 7)
#define APB1_TIM12            (0x01UL << 6)
#define APB1_TIM7             (0x01UL << 5)
#define APB1_TIM6             (0x01UL << 4)
#define APB1_TIM5             (0x01UL << 3)
#define APB1_TIM4             (0x01UL << 2)
#define APB1_TIM3             (0x01UL << 1)
#define APB1_TIM2             (0x01UL << 0)

#define APB2_TIM11            (0x01UL << 18)
#define APB2_TIM10            (0x01UL << 17)
#define APB2_TIM9             (0x01UL << 16)
#define APB2_SYSCFG           (0x01UL << 14)
#define APB2_SPI1             (0x01UL << 12)
#define APB2_SDIO             (0x01UL << 11)
#define APB2_ADC3             (0x01UL << 10)
#define APB2_ADC2             (0x01UL << 9)
#define APB2_ADC1             (0x01UL << 8)
#define APB2_USART6           (0x01UL << 5)
#define APB2_USART1           (0x01UL << 4)
#define APB2_TIM8             (0x01UL << 1)
#define APB2_TIM1             (0x01UL << 0)

#define AHB1_OTGHS            (0x01UL << 29)
#define AHB1_ETHMAC           (0x01UL << 25)
#define AHB1_DMA2             (0x01UL << 22)
#define AHB1_DMA1             (0x01UL << 21)
#define AHB1_CRC              (0x01UL << 12)
#define AHB1_GPIOI            (0x01UL << 8)
#define AHB1_GPIOH            (0x01UL << 7)
#define AHB1_GPIOG            (0x01UL << 6)
#define AHB1_GPIOF            (0x01UL << 5)
#define AHB1_GPIOE            (0x01UL << 4)
#define AHB1_GPIOD            (0x01UL << 3)
#define AHB1_GPIOC            (0x01UL << 2)
#define AHB1_GPIOB            (0x01UL << 1)
#define AHB1_GPIOA            (0x01UL << 0)

#define AHB2_OTGFS            (0x01UL << 7)
#define AHB2_RNG              (0x01UL << 6)
#define AHB2_HASH             (0x01UL << 5)
#define AHB2_CRYP             (0x01UL << 4)
#define AHB2_DCMI             (0x01UL << 0)

#define AHB3_FSMC             (0x01UL << 0)

// Typedefs ---------------------------------------------------------------------------------------

//--------------------------------------------------------------
// Reset & Clock Control Controller Register Structure
//--------------------------------------------------------------
typedef volatile struct
{
   UINT CR;             // Clock control
   UINT PLLCFGR;        // PLL configuration
   UINT CFGR;           // Clock configuration
   UINT CIR;            // Clock interrupt
   UINT AHB1RSTR;       // AHB1 peripheral reset
   UINT AHB2RSTR;       // AHB2 peripheral reset
   UINT AHB3RSTR;       // AHB3 peripheral reset
   UINT RESERVED1;
   UINT APB1RSTR;       // APB1 peripheral reset
   UINT APB2RSTR;       // APB2 peripheral reset
   UINT RESERVED2;
   UINT RESERVED3;
   UINT AHB1ENR;        // AHB1 peripheral clock enable
   UINT AHB2ENR;        // AHB2 peripheral clock enable
   UINT AHB3ENR;        // AHB3 peripheral clock enable
   UINT RESERVED4;
   UINT APB1ENR;        // APB1 peripheral clock enable
   UINT APB2ENR;        // APB2 peripheral clock enable
   UINT RESERVED5;
   UINT RESERVED6;
   UINT AHB1LPENR;      // AHB1 peripheral clock low-power enable
   UINT AHB2LPENR;      // AHB2 peripheral clock low-power enable
   UINT AHB3LPENR;      // AHB3 peripheral clock low-power enable
   UINT RESERVED7;
   UINT APB1LPENR;      // APB1 peripheral clock low-power enable
   UINT APB2LPENR;      // APB2 peripheral clock low-power enable
   UINT RESERVED8;
   UINT RESERVED9;
   UINT BDCR;           // Backup domain control
   UINT CSR;            // Clock control & status
   UINT RESERVED10;
   UINT RESERVED11;
   UINT SSCGR;          // Spread spectrum clock generation
   UINT PLLI2SCFGR;     // PLLI2S configuration
} RCCRegistersStruct;

// Functions --------------------------------------------------------------------------------------
RCCRegistersStruct* GetRCCController()
{
   return (RCCRegistersStruct*)PERIPHERAL_ADDRESS_RCC;
}

#endif // RCC_H_
