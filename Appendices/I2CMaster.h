/*****************************************************************************
* File Name: 	 I2Cmaster.h
*
* Version: 		1.0
*
* Description: 	This file contains function prototypes for I2C Master.
* 					- These functions were provided from Cypress and
* 					  were altered to fit the Smart Eraser application.
*
* Author:		Chris Quesada
*******************************************************************************/
#ifndef SOURCE_I2CMASTER_H_
#define SOURCE_I2CMASTER_H_

#include "cy_pdl.h"
#include "cycfg.h"

/*******************************************************************************
* Constants
*******************************************************************************/
#define TRANSFER_CMPLT        		(0x00UL)
#define READ_CMPLT            		(TRANSFER_CMPLT)
#define NUMBER_OF_I2C_ELEMENTS		(3UL)
#define SIZE_OF_I2C_ELEMENT			(8UL)
#define SIZE_OF_I2C_PACKET			(NUMBER_OF_I2C_ELEMENTS * SIZE_OF_I2C_ELEMENT)
/* Packet positions */

#define I2C_ADDRESS        	  		(0UL)
#define I2C_CONFIG			  		(1UL)

/*******************************************************************************
* Function prototype
*******************************************************************************/
uint8 Write_I2C(uint8* buffer, uint32 bufferSize);
uint32 initI2CMaster(void);

#endif /* SOURCE_I2CMASTER_H_ */
