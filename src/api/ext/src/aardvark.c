// Includes ---------------------------------------------------------------------------------------
#include "ext/aardvark.h"
#include "drivers/i2c_driver.h"

// Defines ----------------------------------------------------------------------------------------
#define AARDVARK_I2C_PORT_EXPANDER_ADDRESS   (0x38) // This can be configured by the hardware jumper.
#define AARDVARK_I2C_CMD_INPUT_REGISTER      (0x00)
#define AARDVARK_I2C_CMD_OUTPUT_REGISTER     (0x01)
#define AARDVARK_I2C_CMD_POLARITY_REGISTER   (0x02)
#define AARDVARK_I2C_CMD_CONFIG_REGISTER     (0x03)
#define AARDVARK_I2C_PORT_ALL_PINS           (0xFF)

// Typedefs ---------------------------------------------------------------------------------------
// Statics, Externs & Globals ---------------------------------------------------------------------
static const UINT uiCONFIG_COMMAND_LENGTH = 2;
static UCHAR aucConfigureIODirectionCommand[] = {
   AARDVARK_I2C_CMD_CONFIG_REGISTER,
   ~AARDVARK_I2C_PORT_ALL_PINS
};

static const UINT uiWRITE_OUTPUT_COMMAND_LENGTH = 2;
static UCHAR aucWriteIODirectionCommand[] = {
   AARDVARK_I2C_CMD_OUTPUT_REGISTER,
   0 // At the time of a write, replace with the right command value.
};

static const UINT uiREAD_OUTPUT_COMMAND_LENGTH = 1;
static UCHAR aucReadIODirectionCommand[] = {
   AARDVARK_I2C_CMD_OUTPUT_REGISTER
};

// Functions --------------------------------------------------------------------------------------

// -------------------------------------------------------------
BOOL InitializeAardvark(void)
{
   return I2C_WriteData(I2C1, I2CMODE_MASTER, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucConfigureIODirectionCommand[0], uiCONFIG_COMMAND_LENGTH);
   // return I2C_MasterTransfer(I2C1, I2CTRANSFER_WRITE, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucConfigureIODirectionCommand[0], uiCONFIG_COMMAND_LENGTH);
}

// -------------------------------------------------------------
BOOL WriteOutputAardvark(
   UCHAR ucValue_)
{
   aucWriteIODirectionCommand[1] = ucValue_;

   // return I2C_WriteData(I2C1, I2CMODE_MASTER, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucWriteIODirectionCommand[0], uiWRITE_OUTPUT_COMMAND_LENGTH);
   return I2C_MasterTransfer(I2C1, I2CTRANSFER_WRITE, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucWriteIODirectionCommand[0], uiWRITE_OUTPUT_COMMAND_LENGTH);
}

// -------------------------------------------------------------
BOOL ReadOutputAardvark(
   UCHAR* pucValue_)
{
   if(pucValue_ == NULL)
   {
      return FALSE;
   }

   // Utilizing repeated START here, but alternatively an entirely different I2C Write transaction could be performed here.
   return I2C_ReadData(I2C1, I2CMODE_MASTER, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucReadIODirectionCommand[0], uiREAD_OUTPUT_COMMAND_LENGTH, pucValue_, 1);
   // BOOL bSuccess = I2C_MasterTransfer(I2C1, I2CTRANSFER_WRITE, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, &aucReadIODirectionCommand[0], uiREAD_OUTPUT_COMMAND_LENGTH);
   // bSuccess |= I2C_MasterTransfer(I2C1, I2CTRANSFER_READ, AARDVARK_I2C_PORT_EXPANDER_ADDRESS, pucValue_, 1);
   // return bSuccess;
}
