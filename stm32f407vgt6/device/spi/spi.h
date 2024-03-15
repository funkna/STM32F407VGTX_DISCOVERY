// Redundancy Prevention --------------------------------------------------------------------------
#ifndef SPI_H_
#define SPI_H_

// Includes ---------------------------------------------------------------------------------------
#include "../stm32f407vgt6.h"
#include "types.h"

// Defines ----------------------------------------------------------------------------------------

//--------------------------------------------------------------
// SPI Controller Register Bitmasks
//--------------------------------------------------------------
#define CR1_BIDIMODE          (0x01UL << 15) // Bidirectional data mode enable
#define CR1_BIDIOE            (0x01UL << 14) // Output enable in bidirectional mode
#define CR1_CRCEN             (0x01UL << 13) // Hardware CRC calculation enable
#define CR1_CRCNEXT           (0x01UL << 12) // CRC transfer next
#define CR1_DFF               (0x01UL << 11) // Data frame format
#define CR1_RXONLY            (0x01UL << 10) // Receive only
#define CR1_SSM               (0x01UL << 9)  // Software slave management
#define CR1_SSI               (0x01UL << 8)  // Internal slave select
#define CR1_LSBFIRST          (0x01UL << 7)  // Frame format
#define CR1_SPE               (0x01UL << 6)  // SPI enable
#define CR1_BR_OFFSET         (3)
#define CR1_BR                (0x07UL << CR1_BR_OFFSET)  // Baud rate control
#define CR1_MSTR              (0x01UL << 2)  // Master selection
#define CR1_CPOL              (0x01UL << 1)  // Clock polarity
#define CR1_CPHA              (0x01UL << 0)  // Clock phase
#define CR2_TXEIE             (0x01UL << 7)  // Tx buffer empty interrupt enable
#define CR2_RXNEIE            (0x01UL << 6)  // Rx buffer empty interrupt enable
#define CR2_ERRIE             (0x01UL << 5)  // Error interrupt enable
#define CR2_FRF               (0x01UL << 4)  // Frame format
#define CR2_SSOE              (0x01UL << 2)  // SS output enable
#define CR2_TXDMAEN           (0x01UL << 1)  // Tx buffer DMA enable
#define CR2_RXDMAEN           (0x01UL << 0)  // Rx buffer DMA enable
#define SR_FRE                (0x01UL << 8)  // Frame format error
#define SR_BSY                (0x01UL << 7)  // Busy flag
#define SR_OVR                (0x01UL << 6)  // Overrun flag
#define SR_MODF               (0x01UL << 5)  // Mode fault
#define SR_CRCERR             (0x01UL << 4)  // CRC error flag
#define SR_UDR                (0x01UL << 3)  // Underrun flag
#define SR_CHSIDE             (0x01UL << 2)  // Channel side
#define SR_TXE                (0x01UL << 1)  // Transmit buffer empty
#define SR_RXNE               (0x01UL << 0)  // Receive buffer not empty

#define CR1_BR_PCLK_DIV2      (0b000UL)
#define CR1_BR_PCLK_DIV4      (0b001UL)
#define CR1_BR_PCLK_DIV8      (0b010UL)
#define CR1_BR_PCLK_DIV16     (0b011UL)
#define CR1_BR_PCLK_DIV32     (0b100UL)
#define CR1_BR_PCLK_DIV64     (0b101UL)
#define CR1_BR_PCLK_DIV128    (0b110UL)
#define CR1_BR_PCLK_DIV256    (0b111UL)

// Typedefs ---------------------------------------------------------------------------------------

//--------------------------------------------------------------
// Serial Peripheral Interface Controller Register Structure
//--------------------------------------------------------------
typedef volatile struct
{
   UINT CR1;         // Control (Not used in I2S mode)
   UINT CR2;         // Control
   UINT SR;          // Status
   UINT DR;          // Data
   UINT CRCPR;       // CRC polynomial
   UINT RXCRCR;      // RX CRC
   UINT TXCRCR;      // TX CRC
   UINT I2SCFGR;     // I2S configuration
   UINT I2SPR;       // I2S prescalar
} SPIRegistersStruct;

// Functions --------------------------------------------------------------------------------------
SPIRegistersStruct* GetSPIController(
   SPIControllerEnum eController_)
{
   switch(eController_)
   {
      case SPI_SPI1:
         return (SPIRegistersStruct*)PERIPHERAL_ADDRESS_SPI1;
      case SPI_SPI2:
         return (SPIRegistersStruct*)PERIPHERAL_ADDRESS_SPI2_I2S2;
      case SPI_SPI3:
         return (SPIRegistersStruct*)PERIPHERAL_ADDRESS_SPI3_I2S3;
      default:
         return NULL;
   }
}

#endif // SPI_H_
