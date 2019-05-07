/*****************************************************************************
* File Name: 	 Arducam.c
*
* Version: 		1.0
*
* Description:	This file holds all the function definitions for the Arducam
*
* Author:		Chris Quesada
*******************************************************************************/

#include <Arducam.h>
#include <SPImaster.h>
#include <I2CMaster.h>
#include <interface.h>
#include <ImProc.h>
#include <math.h>

struct sensor_reg
{
   uint16_t reg;
   uint8 val;
};

struct sensor_reg OV5642_1280x960_RAW[RAWinit] =
{
{0x00ff,0x01},
{0x3008,0x80},
{0x3103,0x93},
{0x3008,0x02},
{0x3017,0x7f},
{0x3018,0xf0},
{0x3615,0xf0},
{0x3000,0xF8},
{0x3001,0x48},
{0x3002,0x5c},
{0x3003,0x02},
{0x3005,0xB7},
{0x3006,0x43},
{0x3007,0x37},
{0x300f,0x06},
{0x3011,0x08},
{0x3010,0x20},
{0x3012,0x00},
{0x460c,0x22},
{0x3815,0x04},
{0x370c,0xA0},
{0x3602,0xFC},
{0x3612,0xFF},
{0x3634,0xC0},
{0x3613,0x00},
{0x3622,0x00},
{0x3603,0x27},
{0x4000,0x21},
{0x401D,0x02},
{0x3600,0x54},
{0x3605,0x04},
{0x3606,0x3F},
{0x5020,0x04},
{0x5197,0x01},
{0x5001,0xFF},
{0x5500,0x10},
{0x5502,0x00},
{0x5503,0x04},
{0x5504,0x00},
{0x5505,0x7F},
{0x5080,0x08},
{0x300E,0x18},
{0x4610,0x00},
{0x471D,0x05},
{0x4708,0x06},
{0x3710,0x10},
{0x3632,0x41},
{0x3631,0x01},
{0x501F,0x03},
{0x3604,0x40},
{0x4300,0x00},
{0x3824,0x11},
{0x5000,0x4F},
{0x3818,0xC1},
{0x3705,0xDB},
{0x370A,0x81},
{0x3621,0xC7},
{0x3800,0x03},
{0x3801,0xE8},
{0x3802,0x03},
{0x3803,0xE8},
{0x3804,0x38},
{0x3805,0x00},
{0x3806,0x03},
{0x3807,0xC0},
{0x3808,0x05},
{0x3809,0x00},
{0x380A,0x03},
{0x380B,0xC0},
{0x380C,0x0A},
{0x380D,0xF0},
{0x380E,0x03},
{0x380F,0xE8},
{0x3827,0x08},
{0x3810,0xC0},
{0x5683,0x00},
{0x5686,0x03},
{0x5687,0xC0},
{0x3A1A,0x04},
{0x3A13,0x30},
{0x3004,0xDF},
{0x350C,0x07},
{0x350D,0xD0},
{0x3500,0x35},
{0x3501,0x00},
{0x3502,0x00},
{0x350A,0x00},
{0x350B,0x00},
{0x3503,0x00},
{0x5682,0x05},
{0x3A0F,0x78},
{0x3A11,0xD0},
{0x3A1B,0x7A},
{0x3A1E,0x66},
{0x3A1F,0x40},
{0x3A10,0x68},
{0x3030,0x0B},
{0x3A01,0x04},
{0x3A02,0x00},
{0x3A03,0x78},
{0x3A04,0x00},
{0x3A05,0x30},
{0x3A14,0x00},
{0x3A15,0x64},
{0x3A16,0x00},
{0x3A17,0x89},
{0x3A18,0x00},
{0x3A19,0x70},
{0x3A00,0x78},
{0x3A08,0x12},
{0x3A09,0xC0},
{0x3A0A,0x0F},
{0x3A0B,0xA0},
{0x3A0D,0x04},
{0x3A0E,0x03},
{0x3C00,0x04},
{0x3C01,0xB4},
{0x5688,0xFD},
{0x5689,0xDF},
{0x568A,0xFE},
{0x568B,0xEF},
{0x568C,0xFE},
{0x568D,0xEF},
{0x568E,0xAA},
{0x568F,0xAA},
{0x589B,0x04},
{0x589A,0xC5},
{0x528A,0x00},
{0x528B,0x02},
{0x528C,0x08},
{0x528D,0x10},
{0x528E,0x20},
{0x528F,0x28},
{0x5290,0x30},
{0x5292,0x00},
{0x5293,0x00},
{0x5294,0x00},
{0x5295,0x02},
{0x5296,0x00},
{0x5297,0x08},
{0x5298,0x00},
{0x5299,0x10},
{0x529A,0x00},
{0x529B,0x20},
{0x529C,0x00},
{0x529D,0x28},
{0x529E,0x00},
{0x5282,0x00},
{0x529F,0x30},
{0x5300,0x00},
{0x5302,0x00},
{0x5303,0x7C},
{0x530C,0x00},
{0x530D,0x0C},
{0x530E,0x20},
{0x530F,0x80},
{0x5310,0x20},
{0x5311,0x80},
{0x5308,0x20},
{0x5309,0x40},
{0x5304,0x00},
{0x5305,0x30},
{0x5306,0x00},
{0x5307,0x80},
{0x5314,0x08},
{0x5315,0x20},
{0x5319,0x30},
{0x5316,0x10},
{0x5317,0x08},
{0x5318,0x02},
{0x5380,0x01},
{0x5381,0x20},
{0x5382,0x00},
{0x5383,0x4E},
{0x5384,0x00},
{0x5385,0x0F},
{0x5386,0x00},
{0x5387,0x00},
{0x5388,0x01},
{0x5389,0x15},
{0x538A,0x00},
{0x538B,0x31},
{0x538C,0x00},
{0x538D,0x00},
{0x538E,0x00},
{0x538F,0x0F},
{0x5390,0x00},
{0x5391,0xAB},
{0x5392,0x00},
{0x5393,0xA2},
{0x5394,0x08},
{0x5301,0x20},
{0x5480,0x14},
{0x5482,0x03},
{0x5483,0x57},
{0x5484,0x65},
{0x5485,0x71},
{0x5481,0x21},
{0x5486,0x7D},
{0x5487,0x87},
{0x5488,0x91},
{0x5489,0x9A},
{0x548A,0xAA},
{0x548B,0xB8},
{0x548C,0xCD},
{0x548D,0xDD},
{0x548E,0xEA},
{0x548F,0x10},
{0x5490,0x05},
{0x5491,0x00},
{0x5492,0x04},
{0x5493,0x20},
{0x5494,0x03},
{0x5495,0x60},
{0x5496,0x02},
{0x5497,0xB8},
{0x5498,0x02},
{0x5499,0x86},
{0x549A,0x02},
{0x549B,0x5B},
{0x549C,0x02},
{0x549D,0x3B},
{0x549E,0x02},
{0x549F,0x1C},
{0x54A0,0x02},
{0x54A1,0x04},
{0x54A2,0x01},
{0x54A3,0xED},
{0x54A4,0x01},
{0x54A5,0xC5},
{0x54A6,0x01},
{0x54A7,0xA5},
{0x54A8,0x01},
{0x54A9,0x6C},
{0x54AA,0x01},
{0x54AB,0x41},
{0x54AC,0x01},
{0x54AD,0x20},
{0x54AE,0x00},
{0x54AF,0x16},
{0x3406,0x00},
{0x5192,0x04},
{0x5191,0xF8},
{0x5193,0x70},
{0x5194,0xF0},
{0x5195,0xF0},
{0x518D,0x3D},
{0x518F,0x54},
{0x518E,0x3D},
{0x5190,0x54},
{0x518B,0xC0},
{0x518C,0xBD},
{0x5187,0x18},
{0x5188,0x18},
{0x5189,0x6E},
{0x518A,0x68},
{0x5186,0x1C},
{0x5181,0x50},
{0x5182,0x11},
{0x5183,0x14},
{0x5184,0x25},
{0x5185,0x24},
{0x5025,0x82},
{0x5583,0x40},
{0x5584,0x40},
{0x5580,0x02},
{0x3633,0x07},
{0x3702,0x10},
{0x3703,0xB2},
{0x3704,0x18},
{0x370B,0x40},
{0x370D,0x02},
{0x3620,0x52},

{0xffff,0xff},
};

struct sensor_reg OV5642_320x240_RAW[RAWres] =
{
	/*
{0x3800,0x03},
{0x3801,0xE8},
{0x3802,0x03},
{0x3803,0xE8},
{0x3804,0x38},
{0x3805,0x00},
{0x3806,0x03},
{0x3807,0xC0},
*/
{0x3808,0x01},
{0x3809,0x40},
{0x380A,0x00},
{0x380B,0xf0},
{0xffff,0xff},
};



/******************************************************************************
* Function Name: MyCam_Test
*******************************************************************************
*
* Summary: 		Tests SPI communication between PSoC 6 and Arducam
*
* Parameters: 	uint16_t *rxBuffer,
* 				uint16_t *txBuffer
*
* Return:		Value in test register of Arducam (rxBuffer[0])
*
******************************************************************************/
void MyCam_Test(uint16_t rxBuffer, uint16_t txBuffer) {

	uint16_t response = 0;

	do {
	txBuffer = (((uint16_t)WRITE + (uint16_t)TEST_SPI) << 8) + (uint16_t)TEST_VALUE;
	Write_SPI(txBuffer);
	txBuffer = (((uint16_t)READ + (uint16_t)TEST_SPI) << 8) + (uint16_t)DUMMY;
	response = Write_SPI(txBuffer);
	} while ( response != TEST_VALUE);
}

/******************************************************************************
* Function Name: MyCam_Trigger
*******************************************************************************
*
* Summary: 		Clears FIFO Flag and Sends trigger signal to have camera
* 				capture image.
*
* Parameters: 	uint16_t *rxBuffer,
* 				uint16_t *txBuffer
*
* Return:		none
*
******************************************************************************/
void MyCam_Trigger(uint16_t rxBuffer, uint16_t txBuffer) {

	txBuffer = (((uint16_t)WRITE + (uint16_t)FIFO_CONTROL) << 8) + (uint16_t)CLEAR_FIFO_FLAG;
	Write_SPI(txBuffer);
	Cy_SysLib_Delay(0.5);

	txBuffer = (((uint16_t)WRITE + (uint16_t)FIFO_CONTROL) << 8) + (uint16_t)CLEAR_FIFO_FLAG;
	Write_SPI(txBuffer);
	Cy_SysLib_Delay(0.5);

	txBuffer = (((uint16_t)WRITE + (uint16_t)FIFO_CONTROL) << 8) + (uint16_t)CAPTURE;
	Write_SPI(txBuffer);
	Cy_SysLib_Delay(0.5);
}

/******************************************************************************
* Function Name: MyCam_Check_Capture_Status
*******************************************************************************
*
* Summary: 		Check capture flag to see if capture is complete
*
* Parameters: 	uint16_t *rxBuffer,
* 				uint16_t *txBuffer
*
* Return:		none
*
******************************************************************************/
uint16_t MyCam_Check_Capture_Status(uint16_t rxBuffer, uint16_t txBuffer) {

	uint16_t response = 0;

	txBuffer = (((uint16_t)READ + (uint16_t)CAPTURE_FLAG) << 8) + (uint16_t)DUMMY;
	response = Write_SPI(txBuffer);

	return response;
}
/******************************************************************************
* Function Name: MyCam_Single_FIFO_Read
*******************************************************************************
*
* Summary: 		Reads 2 bytes of data from cam and them attempts to demosaic
* 				the raw data, still in development
*
* Parameters: 	uint16_t *rxBuffer,
* 				uint16_t *txBuffer
*
* Return:		none
*
******************************************************************************/
unsigned short* MyCam_Pixel_Read(uint16_t txBuffer, uint16_t *ptr_PD, int position, uint8 *BayerFilter) {

		uint16_t Red = 0;
		uint16_t Green1 = 0;
		uint16_t Green2 = 0;
		uint16_t Blue = 0;
		uint8 *start = BayerFilter;
		int j = 0;
		int k = 0;


		if (position == 0) {
			for (int j = 0; j < 1; j++) {
				for (int k = 0; k < Length; k++) {
				txBuffer = (((uint16_t)READ + (uint16_t)FIFO_READ_SINGLE) << 8) + (uint16_t)DUMMY;
				*BayerFilter = Write_SPI(txBuffer);
				BayerFilter = BayerFilter + 1;
				}
			}
			for (int k = 0; k < Length - 1; k++) {
				if (k % 2 == 0) {
					Blue 	= *BayerFilter >> 3;
					Green1 	= (*BayerFilter + 1) >> 2 << 5;
					Green2 	= (*BayerFilter + Length) >> 2 << 5;
					Red 	= (*BayerFilter + Length + 1) >> 3 << 11;
					*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
					ptr_PD = ptr_PD + 1;
					BayerFilter = BayerFilter + 1;
					}
				else if (k % 2 != 0) {
					Green1 	= *BayerFilter >> 2 << 5;
					Blue 	= (*BayerFilter + 1) >> 3;
					Red 	= (*BayerFilter + Length) >> 3 << 11;
					Green2 	= (*BayerFilter + Length + 1) >> 2 << 5;
					*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
					ptr_PD = ptr_PD + 1;
					BayerFilter = BayerFilter + 1;
					}
				}
		ptr_PD = ptr_PD + 1;
		BayerFilter = BayerFilter + 1;
		Green1 	= *BayerFilter >> 2 << 5;
		Blue 	= (*BayerFilter - 1) >> 3;
		Red 	= (*BayerFilter - Length) >> 3 << 11;
		Green2 	= (*BayerFilter - Length - 1) >> 2 << 5;
		*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
		}

		else if (position == 1) {

			for (k = 0; k < Length; k++) {
				*BayerFilter = *BayerFilter + Length;
				BayerFilter = BayerFilter + 1;
			}

			for (int k = 0; k < Length; k++) {
				txBuffer = (((uint16_t)READ + (uint16_t)FIFO_READ_SINGLE) << 8) + (uint16_t)DUMMY;
				*BayerFilter = Write_SPI(txBuffer);
				BayerFilter = BayerFilter + 1;
			}

			BayerFilter = start;

			for (int k = 0; k < Length - 1; k++) {
				if (k % 2 == 0) {
					Blue 	= *BayerFilter >> 3;
					Green1 	= (*BayerFilter + 1) >> 2 << 5;
					Green2 	= (*BayerFilter + Length) >> 2 << 5;
					Red 	= (*BayerFilter + Length + 1) >> 3 << 11;
					*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
					ptr_PD = ptr_PD + 1;
					BayerFilter = BayerFilter + 1;
					}
				else if (k % 2 != 0) {
					Green1 	= *BayerFilter >> 2 << 5;
					Blue 	= (*BayerFilter + 1) >> 3;
					Red 	= (*BayerFilter + Length) >> 3 << 11;
					Green2 	= (*BayerFilter + Length + 1) >> 2 << 5;
					*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
					ptr_PD = ptr_PD + 1;
					BayerFilter = BayerFilter + 1;
					}
				}
		ptr_PD = ptr_PD + 1;
		BayerFilter = BayerFilter + 1;
		Green1 	= *BayerFilter >> 2 << 5;
		Blue 	= (*BayerFilter - 1) >> 3 << 11;
		Red 	= (*BayerFilter - Length) >> 3 << 11;
		Green2 	= (*BayerFilter - Length - 1) >> 2 << 5;
		*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
		}

		else if (position == 2) {

			for (k = 0; k < Length; k++) {
				*BayerFilter = *BayerFilter + Length;
				BayerFilter = BayerFilter + 1;
			}

			for (int k = 0; k < Length; k++) {
				txBuffer = (((uint16_t)READ + (uint16_t)FIFO_READ_SINGLE) << 8) + (uint16_t)DUMMY;
				*BayerFilter = Write_SPI(txBuffer);
				BayerFilter = BayerFilter + 1;
			}

			BayerFilter = start;

			for (int k = 0; k < Length - 1; k++) {
				if (k % 2 == 0) {
					Green1 	= *BayerFilter >> 2 << 5;
					Red 	= (*BayerFilter + 1) >> 3 << 11;
					Blue 	= (*BayerFilter + Length)>> 3;
					Green2 	= (*BayerFilter + Length + 1)>> 2 << 5;
					*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
					ptr_PD = ptr_PD + 1;
					BayerFilter = BayerFilter + 1;
					}
				else if (k % 2 != 0) {
					Red 	= *BayerFilter >> 3 << 11;
					Green1 	= (*BayerFilter + 1) >> 2 << 5;
					Green2 	= (*BayerFilter + Length) >> 2 << 5;
					Blue 	= (*BayerFilter + Length + 1) >> 3;
					*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
					ptr_PD = ptr_PD + 1;
					BayerFilter = BayerFilter + 1;
					}
				}
		ptr_PD = ptr_PD + 1;
		BayerFilter = BayerFilter + 1;
		Red 	= *BayerFilter >> 3 << 11;
		Green1 	= (*BayerFilter - 1) >> 2 << 5;
		Green2 	= (*BayerFilter - Length) >> 2 << 5;
		Blue 	= (*BayerFilter - Length - 1) >> 3;
		*ptr_PD = Blue + ((Green1 + Green2) / 2) + Red;
		}
		return ptr_PD;
}

/******************************************************************************
* Function Name: MyCam_Single_Dummy_Read
*******************************************************************************
*
* Summary: 		Handles the first dummy byte of RGB565 data
*
* Parameters: 	uint16_t *rxBuffer,
* 				uint16_t *txBuffer
*
* Return:		none
*
******************************************************************************/
void MyCam_Single_DUMMY_Read(uint16_t txBuffer, uint16_t *ptr_PD) {
	 Write_SPI(txBuffer);
}

/******************************************************************************
* Function Name: MyCamInit
*******************************************************************************
*
* Summary: 		Initializes camera sensor to RGB565 320x240
*
* Parameters: 	None
*
* Return:		None
*
******************************************************************************/

void MyCam_Init(void) {

	int k 									= 0;
	uint8 buffer[NUMBER_OF_I2C_ELEMENTS] 	= {0};

	for (k = 0; k < RAWinit; k++) {
		buffer[0] =	OV5642_1280x960_RAW[k].reg >> 8;
		buffer[1] = OV5642_1280x960_RAW[k].reg;
		buffer[2] = OV5642_1280x960_RAW[k].val;
		Write_I2C(buffer, NUMBER_OF_I2C_ELEMENTS);
	}
	Cy_SysLib_Delay(1000);

	for (k = 0; k < RAWres; k++) {
		buffer[0] =	OV5642_320x240_RAW[k].reg >> 8;
		buffer[1] = OV5642_320x240_RAW[k].reg;
		buffer[2] = OV5642_320x240_RAW[k].val;
		Write_I2C(buffer, NUMBER_OF_I2C_ELEMENTS);
	}
	Cy_SysLib_Delay(250);
};

/******************************************************************************
* Function Name: handle_error
*******************************************************************************
*
* Summary: 		This is a blocking function. It disables the interrupt and waits
* 				in an infinite loop. This function is called when an error is
* 				encountered during initialization of the blocks or during
* 				SPI communication. This was provided by Cypress
*
* Parameters: 	None
*
* Return:		None
*
******************************************************************************/
void handle_error(void)
{
	 /* Disable all interrupts. */
	__disable_irq();

	/* Infinite loop. */
	while(1u) {}
}
