/******************************************************************************
* File Name: 	SPIMaster.c
*
* Version: 		1.0
*
* Description: 	This file contains function definitions for SPI Master.
* 					- These functions were provided from Cypress and
* 					  were altered to fit the Smart Eraser application.
*
* Author:		Chris Quesada
*******************************************************************************/
#include "SPIMaster.h"
#include "Interface.h"
#include "stdio.h"

/******************************************************************************
* Function Name: initMaster
*******************************************************************************
*
* Summary: 		This function initializes the SPI Master based on the
* 				configuration done in design.modus file.
*
* Parameters: 	None
*
* Return:		(uint32) INIT_SUCCESS or INIT_FAILURE
*
******************************************************************************/
uint32 initSPIMaster(void)
{
    cy_en_scb_spi_status_t initStatus;

	/* Configure SPI block */
	initStatus = Cy_SCB_SPI_Init(mSPI_HW, &mSPI_config, NULL);

	/* If the initialization fails, return failure status */
	if(initStatus != CY_SCB_SPI_SUCCESS)
	{
		return(INIT_FAILURE);
	}

	/* Set active slave select to line 0 */
	Cy_SCB_SPI_SetActiveSlaveSelect(mSPI_HW, CY_SCB_SPI_SLAVE_SELECT0);

	/* Enable SPI master block. */
	Cy_SCB_SPI_Enable(mSPI_HW);

	/* Initialization completed */

	return(INIT_SUCCESS);
}


/******************************************************************************
* Function Name: Write_SPI
*******************************************************************************
*
* Summary:		This function sends the data to the slave. Note that the below
* 				function is blocking until all the bytes are transferred.
*
* Parameters:  	(uint32 *) txBuffer - Pointer to the transmit buffer
* 				(uint32) transferSize - Number of bytes to be transmitted
*
* Return:		None
*
******************************************************************************/

uint16_t Write_SPI(uint16_t data)
{
	uint16_t readData;

	/* ----------------Send read command to the camera--------------------- */
	Cy_SCB_SPI_Write(mSPI_HW, data);

	/* -------Wait for RX buffer to get filled with 2 bytes of data----- */
	while ( CY_SCB_SPI_RX_NOT_EMPTY != (Cy_SCB_SPI_GetRxFifoStatus(mSPI_HW) & CY_SCB_SPI_RX_NOT_EMPTY)) {}

	readData = Cy_SCB_SPI_Read(mSPI_HW);

	 /* -----------------Clear the RX and TX buffers----------------- */
	Cy_SCB_SPI_ClearTxFifo(mSPI_HW);
	Cy_SCB_SPI_ClearRxFifo(mSPI_HW);
	Cy_SCB_SPI_ClearRxFifoStatus(mSPI_HW, CY_SCB_SPI_RX_NOT_EMPTY);

	return(readData);
}


/* [] END OF FILE */

