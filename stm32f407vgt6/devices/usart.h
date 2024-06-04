// Redundancy Prevention --------------------------------------------------------------------------
#ifndef USART_H_
#define USART_H_

// Includes ---------------------------------------------------------------------------------------
#include "stm32f407vgt6.h"
#include "peripherals.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

//--------------------------------------------------------------
// USART Controller Register Bitmasks
//--------------------------------------------------------------
#define SR_CTS                (0x01UL << 9)
#define SR_LBD                (0x01UL << 8)
#define SR_TXE                (0x01UL << 7)
#define SR_TC                 (0x01UL << 6)
#define SR_RXNE               (0x01UL << 5)
#define SR_IDLE               (0x01UL << 4)
#define SR_ORE                (0x01UL << 3)
#define SR_NF                 (0x01UL << 2)
#define SR_FE                 (0x01UL << 1)
#define SR_PE                 (0x01UL << 0)
#define BRR_DIVMANT_OFFSET    (4)
#define BRR_DIVMANT           (0xFFFUL << BRR_DIVMANT_OFFSET)
#define BRR_DIVFRAC_OFFSET    (0)
#define BRR_DIVFRAC           (0x0FUL << BRR_DIVFRAC_OFFSET)
#define CR1_OVER8             (0x01UL << 15)
#define CR1_UE                (0x01UL << 13)
#define CR1_M                 (0x01UL << 12)
#define CR1_WAKE              (0x01UL << 11)
#define CR1_PCE               (0x01UL << 10)
#define CR1_PS                (0x01UL << 9)
#define CR1_PEIE              (0x01UL << 8)
#define CR1_TXEIE             (0x01UL << 7)
#define CR1_TCIE              (0x01UL << 6)
#define CR1_RXNEIE            (0x01UL << 5)
#define CR1_IDLEIE            (0x01UL << 4)
#define CR1_TE                (0x01UL << 3)
#define CR1_RE                (0x01UL << 2)
#define CR1_RWU               (0x01UL << 1)
#define CR1_SBK               (0x01UL << 0)
#define CR2_LINEN             (0x01UL << 14)
#define CR2_STOP_OFFSET       (12)
#define CR2_STOP              (0x03UL << CR2_STOP_OFFSET)
#define CR2_CLKEN             (0x01UL << 11)
#define CR2_CPOL              (0x01UL << 10)
#define CR2_CPHA              (0x01UL << 9)
#define CR2_LBCL              (0x01UL << 8)
#define CR2_LBDIE             (0x01UL << 6)
#define CR2_LBDL              (0x01UL << 5)
#define CR2_ADD               (0x0FUL << 0)
#define CR3_ONEBIT            (0x01UL << 11)
#define CR3_CTSIE             (0x01UL << 10)
#define CR3_CTSE              (0x01UL << 9)
#define CR3_RTSE              (0x01UL << 8)
#define CR3_DMAT              (0x01UL << 7)
#define CR3_DMAR              (0x01UL << 6)
#define CR3_SCEN              (0x01UL << 5)
#define CR3_NACK              (0x01UL << 4)
#define CR3_HDSEL             (0x01UL << 3)
#define CR3_IRLP              (0x01UL << 2)
#define CR3_IREN              (0x01UL << 1)
#define CR3_EIE               (0x01UL << 0)
#define GTPR_GT_OFFSET        (8)
#define GTPR_GT               (0xFFUL << GTPR_GT_OFFSET)
#define GTPR_PSC_OFFSET       (0)
#define GTPR_PSC              (0xFFUL << GTPR_PSC_OFFSET)


#define CR2_STOP_BITS_1       (0b00UL)
#define CR2_STOP_BITS_0_5     (0b01UL)
#define CR2_STOP_BITS_2       (0b10UL)
#define CR2_STOP_BITS_1_5     (0b11UL)

// Typedefs ---------------------------------------------------------------------------------------

//--------------------------------------------------------------
// Universal Synchronous Asynchronous Receiver Transmitter Controller Register Structure
//--------------------------------------------------------------
typedef volatile struct
{
   UINT SR;          // Status
   UINT DR;          // Data
   UINT BRR;         // Baud rate
   UINT CR1;         // Control
   UINT CR2;         // Control
   UINT CR3;         // Control
   UINT GTPR;        // Guard time and Prescaler
} USARTRegistersStruct;

// Functions --------------------------------------------------------------------------------------
USARTRegistersStruct* GetUSARTController(
   USARTControllerEnum eController_)
{
   switch(eController_)
   {
      case USART1:
         return (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART1;
      case USART2:
         return (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART2;
      case USART3:
         return (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART3;
      case USART4:
         return (USARTRegistersStruct*)PERIPHERAL_ADDRESS_UART4;
      case USART5:
         return (USARTRegistersStruct*)PERIPHERAL_ADDRESS_UART5;
      case USART6:
         return (USARTRegistersStruct*)PERIPHERAL_ADDRESS_USART6;
      default:
         return NULL;
   }
}

#endif // USART_H_
