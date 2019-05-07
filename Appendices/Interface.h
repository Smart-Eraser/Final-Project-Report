/******************************************************************************
* File Name: 	SPIMaster.c
*
* Version: 		1.0
*
* Description: 	This file contains macros for various files.
* 					- This file was provided by Cypress and modified to fiy
* 					  the Smart Eraser System.
*
* Author:		Chris Quesada
*******************************************************************************/
#ifndef SOURCE_INTERFACE_H_
#define SOURCE_INTERFACE_H_

#include "cy_pdl.h"
#include "cycfg.h"

/* I2C & SPI statuses */
#define INIT_SUCCESS 			(0UL)
#define INIT_FAILURE 			(1UL)

/* Communication status */
#define TRANSFER_COMPLETE 		(0)
#define TRANSFER_FAILURE		(1)
#define TRANSFER_IN_PROGRESS	(2)
#define IDLE					(3)

/* Element index in the packet */
#define PACKET_CMD_POS        	(0UL)
#define PACKET_DAT_POS        	(1UL)

void handle_error(void);

#endif
