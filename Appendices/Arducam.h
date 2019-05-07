/*****************************************************************************
* File Name: 	 Arducam.h
*
* Version: 		1.0
*
* Description:	This file holds all the function prototypes for the Arducam
*
* Author:		Chris Quesada
*******************************************************************************/

#ifndef ARDUCAM_H
#define ARDUCAM_H

#include "cy_pdl.h"
#include "cycfg.h"
#include "ImProc.h"

#define	RAWinit							(274UL)
#define	RAWres							(5UL)

/* --------------------SPI Command Addresses for Arducam----------------- */

#define TEST_SPI					(0x0)
#define TEST_VALUE					(0x59)
#define SET_FRAME_COUNT				(0x01)
#define FIFO_CONTROL				(0x04)
#define CAPTURE_FLAG				(0x41)
#define FIFO_READ_SINGLE				(0x3d)

/* ---------------SPI Command operations for Arducam--------------------- */
#define WRITE						(0x80)
#define READ						(0x00)
#define DUMMY						(0x00)

/* ------------------SPI Command Data for Arducam------------------------ */
#define CLEAR_FIFO_FLAG				(0x01)
#define CAPTURE						(0x02)
#define CAPTURE_COMPLETE			(0x08)

void MyCam_Test(uint16_t rxBuffer, uint16_t txBuffer);
void MyCam_Trigger(uint16_t rxBuffer, uint16_t txBuffer);
void MyCam_Init(void);
unsigned short* MyCam_Pixel_Read(uint16_t txBuffer, uint16_t *ptr_PD, int position, uint8 *BayerFilter);
void MyCam_Single_DUMMY_Read(uint16_t txBuffer, uint16_t *ptr_PD);
uint16_t  MyCam_Check_Capture_Status(uint16_t rxBuffer, uint16_t txBuffer);

#endif
