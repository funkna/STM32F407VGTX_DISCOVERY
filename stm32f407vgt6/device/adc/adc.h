// Redundancy Prevention --------------------------------------------------------------------------
#ifndef ADC_H_
#define ADC_H_

// Includes ---------------------------------------------------------------------------------------
#include "../stm32f407vgt6.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

// -------------------------------------------------------------
// ADC Controller Register Bitmasks
// -------------------------------------------------------------
#define SR_OVR                (0x01UL << 5)  // Overrun
#define SR_STRT               (0x01UL << 4)  // Regular Channel Start Flag
#define SR_JSTRT              (0x01UL << 3)  // Injected Channel Start Flag
#define SR_JEOC               (0x01UL << 2)  // Injected Channel End of Conversion
#define SR_EOC                (0x01UL << 1)  // Regular Channel End of Conversion
#define SR_AWD                (0x01UL << 0)  // Analog Watchdog Flag
#define CR1_OVRIE             (0x01UL << 26) // Overrun Interrupt Enable
#define CR1_RES               (0x03UL << 24) // Resolution[1:0]
#define CR1_AWDEN             (0x01UL << 23) // Analog Watchdog Eable on Regular Channels
#define CR1_JAWDEN            (0x01UL << 22) // Analog Watchdog Eable on Injected Channels
#define CR1_DISCNUM           (0x07UL << 13) // Discontinuous Mode Channel Count
#define CR1_JDISCEN           (0x01UL << 12) // Discontinuous Mode on Injected Channels
#define CR1_DISCEN            (0x01UL << 11) // Discontinuous Mode on Regular Channels
#define CR1_JAUTO             (0x01UL << 10) // Automatic Injected Group Conversion
#define CR1_AWDSGL            (0x01UL << 9)  // Enable the Watchdog on a Single Channel in Scan Mode
#define CR1_SCAN              (0x01UL << 8)  // Scan Mode
#define CR1_JEOCIE            (0x01UL << 7)  // Interrupt Enable for Injected Channels
#define CR1_AWDIE             (0x01UL << 6)  // Analog Watchdog Interrupt Enable
#define CR1_EOCIE             (0x01UL << 5)  // Interrupt Enable for EOC
#define CR1_AWDCH             (0x1FUL << 0)  // Analog Watchdog Channel Select Bits

// Typedefs ---------------------------------------------------------------------------------------

// -------------------------------------------------------------
// ADC Controller Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT SR;          // Status
   UINT CR1;         // Control 1
   UINT CR2;         // Control 2
   UINT SMPR1;       // Sample Time 1
   UINT SMPR2;       // Sample Time 2
   UINT JOFR1;       // Injected Channel Data Offset 1
   UINT JOFR2;       // Injected Channel Data Offset 2
   UINT JOFR3;       // Injected Channel Data Offset 3
   UINT JOFR4;       // Injected Channel Data Offset 4
   UINT HTR;         // Watchdog Higher Threshold
   UINT LTR;         // Watchdog Lower Threshold
   UINT SQR1;        // Regular Sequence 1
   UINT SQR2;        // Regular Sequence 2
   UINT SQR3;        // Regular Sequence 3
   UINT JSQR;        // Injected Sequence
   UINT JDR1;        // Injected Data 1
   UINT JDR2;        // Injected Data 2
   UINT JDR3;        // Injected Data 3
   UINT JDR4;        // Injected Data 4
   UINT DR;          // Data
} ADCRegistersStruct;

// -------------------------------------------------------------
// Common ADC Register Structure
// -------------------------------------------------------------
typedef volatile struct
{
   UINT CSR;         // Common Status
   UINT CCR;         // Common Control
   UINT CDR;         // Common Regular Data (Dual Mode & Triple Mode)
} ADCCommonStruct;

// Functions --------------------------------------------------------------------------------------

// Singleton instance(s) for ADC controller(s)
static ADCRegistersStruct* apstTheADCControllers[ADC_MAX] = {NULL};
ADCRegistersStruct* GetADCController(
   ADCControllerEnum eController_)
{
   if(eController_ >= ADC_MAX)
   {
      return NULL;
   }

   if(apstTheADCControllers[eController_] == NULL)
   {
      UINT uiControllerBase = 0;
      if(eController_ == ADC_ADC1)
      {
         uiControllerBase = PERIPHERAL_ADDRESS_ADC1;
      }
      else if(eController_ == ADC_ADC2)
      {
         uiControllerBase = PERIPHERAL_ADDRESS_ADC2;
      }
      else if(eController_ == ADC_ADC3)
      {
         uiControllerBase = PERIPHERAL_ADDRESS_ADC3;
      }
      else
      {
         return NULL;
      }
      apstTheADCControllers[eController_] = (ADCRegistersStruct*)uiControllerBase;
   }

   return apstTheADCControllers[eController_];
}

// Singleton instance(s) for ADC common controller(s)
static ADCCommonStruct* pstTheADCCommonController = NULL;
ADCCommonStruct* GetADCCommonController()
{
   if(pstTheADCCommonController == NULL)
   {
      pstTheADCCommonController = (ADCCommonStruct*)PERIPHERAL_ADDRESS_ADC_COMMON;
   }

   return pstTheADCCommonController;
}

#endif // ADC_H_
