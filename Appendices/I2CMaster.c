/******************************************************************************
* File Name: 	I2CMaster.c
*
* Version: 		1.0
*
* Description: 	This file contains function definitions for I2C Master.
* 					- These functions were provided from Cypress and
* 					  were altered to fit the Smart Eraser application.
*
* Author:		Chris Quesada
*******************************************************************************/

#include "I2CMaster.h"
#include "Interface.h"

/******************************************************************************
*            Constants
******************************************************************************/
/* I2C slave address to communicate with */
#define I2C_SLAVE_ADDR        (0x3C)

/* Buffer and packet size */
#define RX_PACKET_SIZE  	  (3UL)

/* Buffer and packet size */
#define RX_PACKET_SIZE        (3UL)
#define BUFFER_SIZE           (PACKET_SIZE)

/* Command valid status */
#define STS_CMD_DONE          (0x00UL)
#define STS_CMD_FAIL          (0xFFUL)

/* Command valid status */
#define TRANSFER_ERROR        (0xFFUL)
#define READ_ERROR            (TRANSFER_ERROR)

/* Timeout */
#define LOOP_FOREVER          (0UL)
#define I2C_TIMEOUT           (100UL)

/*******************************************************************************
* Global variables
*******************************************************************************/
cy_stc_scb_i2c_context_t mI2C_context;

/*******************************************************************************
* Function Name: Write_I2C
****************************************************************************//**
*
* Buffer is assigned with data to be sent to slave.
* Low level PDL APIs are used to control I2C SCB to send data.
* Errors are handled depending on the return value from the appropriate function.
*
* \param buffer
*
* \param bufferSize
*
* \return
* returns the status after command is written to slave.
* TRANSFER_ERROR is returned if any error occurs.
* TRANSFER_CMPLT is returned if write is successful.
* \ref uint32
*
*******************************************************************************/
uint8 Write_I2C(uint8* buffer, uint32 bufferSize)
{
    uint8 status = TRANSFER_ERROR;
    cy_en_scb_i2c_status_t  errorStatus;

    /* Sends packets to slave using low level PDL library functions. */
    errorStatus = Cy_SCB_I2C_MasterSendStart(mI2C_HW, I2C_SLAVE_ADDR, CY_SCB_I2C_WRITE_XFER, I2C_TIMEOUT, &mI2C_context);
    if(errorStatus == CY_SCB_I2C_SUCCESS)
    {

        uint32 cnt = 0UL;

        /* Read data from the slave into the buffer */
        do
        {
            /* Write byte and receive ACK/NACK response */
            errorStatus = Cy_SCB_I2C_MasterWriteByte(mI2C_HW, buffer[cnt], I2C_TIMEOUT, &mI2C_context);
            ++cnt;
        }
        while((errorStatus == CY_SCB_I2C_SUCCESS) && (cnt < bufferSize));
    }

    /* Check status of transaction */
    if ((errorStatus == CY_SCB_I2C_SUCCESS)           ||
        (errorStatus == CY_SCB_I2C_MASTER_MANUAL_NAK) ||
        (errorStatus == CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK))
    {
        /* Send Stop condition on the bus */
        if (Cy_SCB_I2C_MasterSendStop(mI2C_HW, I2C_TIMEOUT, &mI2C_context) == CY_SCB_I2C_SUCCESS)
        {
            status = TRANSFER_CMPLT;
        }
    }

    return (status);
}

/*******************************************************************************
* Function Name: initI2CMaster
********************************************************************************
*
* This function initiates and enables master SCB
*
* \param None
*
* \return
* Status of initialization
*
*******************************************************************************/
uint32 initI2CMaster(void)
{
	/* Initialize the master I2C. */

    cy_en_scb_i2c_status_t initStatus;

	/* Configure component. */
	initStatus = Cy_SCB_I2C_Init(mI2C_HW, &mI2C_config, &mI2C_context);
	if(initStatus!=CY_SCB_I2C_SUCCESS)
	{
		return INIT_FAILURE;
	}

	/* Enable I2C master hardware. */
	Cy_SCB_I2C_Enable(mI2C_HW);
	return INIT_SUCCESS;
}
