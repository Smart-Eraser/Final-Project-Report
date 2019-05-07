/*****************************************************************************
* File Name: 	 main.c
*
* Version: 		1.0
*
* Description:	Uses SPI and I2C communication to receive image form Arducam,
* 				process the image to find edges, translates detected edges to
* 				coordinates for stepper motors, and	sends coordinate information
* 				to HUZZAH32 server via UART communication.
*
*    			This code was modified from a template provided by Cypress
*    			Semiconductor Corporation -> TFTemWin example
*
* Author:		Chris Quesada
*******************************************************************************/
#include "cy_pdl.h"
#include "cycfg.h"
#include "GUI.h"
#include "cycfg_qspi_memslot.h"
#include "cy_smif.h"
#include <Interface.h>
#include <SPIMaster.h>
#include <I2CMaster.h>
#include <stdbool.h>
#include <time.h>
#include <ImProc.h>
#include <math.h>
#include <Arducam.h>

/*****************************************************************************
* Global constants
*****************************************************************************/

#define NUMBER_OF_PAGES    			(1u)
#define BTN_PRESSED             	(0u)
#define BTN_RELEASED            	(1u)

/************************ Function Prototypes ********************************/
int  Trigger_Capture(void);
void Process_Image(void);
void (*PageArray[NUMBER_OF_PAGES])(void) = {Process_Image, /*func1, func2, func3.....*/};

/******************************************************************************/

/* Reference to bitmap test image */
extern GUI_CONST_STORAGE GUI_BITMAP bmExampleImage;


/*******************************************************************************
* Function Name: void ShowStartupScreen(void)
********************************************************************************
*
* Summary: 		This function displays the startup screen. This was provided by
* 		   		Cypress.
*
* Parameters:	None
*
* Return:		None
*
*******************************************************************************/
void ShowStartupScreen(void)
{
    /* Set font size, foreground and background colors */
    GUI_SetFont(GUI_FONT_24B_1);
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_BLACK);

    /* Clear the screen */
    GUI_Clear();

    /* Print the text CYPRESS EMWIN GRAPHICS DEMO TFT DISPLAY */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Smart Eraser", 160, 80);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Version 1.0", 160, 100);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Initializing....", 160, 120);
}

/*******************************************************************************
* Function Name: void ShowInstructionsScreen(void)
********************************************************************************
*
* Summary: 		This function shows screen with instructions to press SW2 to
*          		scroll through various display pages. This was provided by
* 		   		Cypress.
*
* Parameters:	None
*
* Return:		None
*
*******************************************************************************/
void ShowInstructionsScreen(void)
{
    /* Set font size, background color and text mode */
    GUI_SetFont(GUI_FONT_24_1);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display instructions text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("PRESS SW2 ON THE KIT", 160, 90);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("TO CAPTURE IMAGE", 160, 110);
}

/*******************************************************************************
* Function Name: Trigger_Capture(void)
********************************************************************************
*
* Summary: 		This functions sends a trigger command to the Arducam module
* 				via SPI
*
* Parameters:	None
*
* Return:		int status
*
*******************************************************************************/
int Trigger_Capture(void)
{
	/* Buffer to hold command packet to be sent to the slave by the master */
	uint16_t  txBuffer 	= {0};

	/* Buffer to save the received data by the slave */
	uint16_t  rxBuffer 	= {0};

	MyCam_Test(rxBuffer, txBuffer);
	MyCam_Trigger(rxBuffer, txBuffer);

	return 0;
}

/*******************************************************************************
* Function Name: Process_Image(void)
********************************************************************************
*
* Summary: 		This function takes an image, converts it to grayscale, detects
* 				edges, implements square detection on detected edges, sends
* 				results to HUZZAH32 via UART
*
* Parameters:	None
*
* Return:		None
*
*******************************************************************************/
void Process_Image(void)
{
	int				flag							= 0;
	int 			k								= 0;
	uint16_t  		txBuffer 						= {0};
	uint16_t  		rxBuffer 						= {0};
	uint16_t		Dummy[1]						= {0};
	uint16_t		*ptr_Dmmy						= &Dummy;
	uint16_t		Pixel_Data[Length*Height] 		= {0};						// Will hold processed pixels
	uint16_t		Gray_Data[Length*Height] 		= {0};						// Will hold grayscale pixels to be run through Sobel edge detection
	uint16_t 	    *ptr_PD 						= &Pixel_Data;				// Pointer to processed pixels array
	uint16_t		*ptr_GD							= &Gray_Data;				// Pointer to grayscale pixels array
	uint16_t 	    *ptr_Image_PD 					= bmExampleImage.pData;		// Pointer to Pre-loaded image for image processing testing
	//uint16_t 	    *ptr_Image_PD 					= &Pixel_Data;				// Pointer to Pre-loaded image for image processing testing
	int				start 							= 0;
	int 			middle							= 0;
	int				middleGStart 					= 1;
	int				middleBStart 					= 2;
	uint8 BayerFilter[2][Length]					= {0};


	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_DrawBitmap(&bmExampleImage, 0, 0);

//-------------------------- STILL IN DEVELOPEMENT----------------------------//

	/* ---------------------------Initializations---------------------------- */
	/*MyCam_Init();
	Trigger_Capture();

	while (flag != CAPTURE_COMPLETE) {
	flag = MyCam_Check_Capture_Status(rxBuffer, txBuffer);
	}

	Cy_SysLib_Delay(1000);

	GUI_BITMAP Image = {
	  (unsigned int)Length, 				// xSize
	  (unsigned int)Height,  				// ySize
	  640, 									// BytesPerLine
	  16, 									// BitsPerPixel
	  (unsigned char *)Pixel_Data,  		// Pointer to picture data
	  NULL,  								// Pointer to palette
	  GUI_DRAW_BMPM565,						// Specifies RGB format
	};

	Cy_SysLib_Delay(1000);

	MyCam_Pixel_Read(txBuffer, ptr_PD, start, &BayerFilter);
	middle = middleGStart;

	for (k = 0; k < Height - 1; k++) {
		ptr_PD = MyCam_Pixel_Read(txBuffer, ptr_PD, middle, &BayerFilter);
		if (middle == middleGStart)
			middle = middleBStart;
		else if (middle == middleBStart)
			middle = middleGStart;
	}

	ptr_PD = &Pixel_Data;
	GUI_DrawBitmap(&Image, 0, 0);
	Cy_SysLib_Delay(750);

	for (k = 0; k < Height - 1; k++) {
		ptr_PD = MyCam_Pixel_Read(txBuffer, ptr_PD, middle, &BayerFilter);
		if (middle == middleGStart)
			middle = middleBStart;
		else if (middle == middleBStart)
			middle = middleGStart;
	}

	ptr_PD = &Pixel_Data;
	GUI_DrawBitmap(&Image, 0, 80);
	Cy_SysLib_Delay(750);

	for (k = 0; k < Height - 1; k++) {
		ptr_PD = MyCam_Pixel_Read(txBuffer, ptr_PD, middle, &BayerFilter);
		if (middle == middleGStart)
			middle = middleBStart;
		else if (middle == middleBStart)
			middle = middleGStart;
	}
	ptr_PD = &Pixel_Data;
	GUI_DrawBitmap(&Image, 0, 160);
	Cy_SysLib_Delay(750);

	/* GUI_BITMAP is a structure the EMWIN graphics driver
	 * uses to display an image */

	GUI_BITMAP Image = {
		  (unsigned int)Length, 				// xSize
		  (unsigned int)Height,  				// ySize
		  640, 									// BytesPerLine
		  16, 									// BitsPerPixel
		  (unsigned char *)Pixel_Data,  		// Pointer to picture data
		  NULL,  								// Pointer to palette
		  GUI_DRAW_BMPM565,						// Specifies RGB format
		};

	/*******************************************************************************
	* Function Call: conv2gray()
	********************************************************************************
	*
	* Summary: 		This function takes an image and converts it to grayscale. Each
	* 				time the function is called, 80 rows of pixels are evaluated and
	* 				the pointer to the image data is returned to be the starting
	* 				point of the next function call. The array that holds the processed
	* 				pixels is what will be displayed on the screen. This is just for
	* 				demonstration purposes and won't be used in the final system.
	*
	* 				first call -> 0 - 79;
	* 				second call -> 80 - 159;
	* 				third call -> 160 - 239
	*******************************************************************************/

	//ptr_Image_PD = conv2gray(ptr_Image_PD, ptr_PD, ptr_GD);
	//GUI_DrawBitmap(&Image, 0, 0);

	//ptr_Image_PD = conv2gray(ptr_Image_PD, ptr_PD, ptr_GD);
	//GUI_DrawBitmap(&Image, 0, 80);

	//ptr_Image_PD = conv2gray(ptr_Image_PD, ptr_PD, ptr_GD);
	//GUI_DrawBitmap(&Image, 0, 160);

	//ptr_Image_PD = bmExampleImage.pData;		// Reset test image pointer to beginning

	/*******************************************************************************
	* Function Call: sobel()
	********************************************************************************
	*
	* Summary: 		This function takes an image, uses conv2gray() to convert an image
	* 				to grayscale, and the uses sobel edge detection to detect edges
	* 				in the image. Each time the function is called, 80 rows of pixels
	* 				are evaluated and the pointer to the image data is returned to be
	* 				the starting point of the next function call.
	*
	*	 			first call -> 0 - 79;
	*	 			second call -> 80 - 159;
	*	 			third call -> 160 - 239
	*******************************************************************************/

	ptr_Image_PD = sobel(ptr_Image_PD, ptr_PD, ptr_GD);
	GUI_DrawBitmap(&Image, 0, 0);

	for (k = 0; k < 1024; k++){
		Cy_SCB_UART_PutArray(KIT_UART_HW, ptr_PD, 25);
		Cy_SysLib_Delay(1);
		Cy_SCB_UART_ClearTxFifoStatus(KIT_UART_HW, CY_SCB_UART_TX_DONE);
		ptr_PD = ptr_PD + 128;
}

	ptr_PD = &Pixel_Data;

	Cy_SysLib_Delay(500);

	ptr_Image_PD = sobel(ptr_Image_PD, ptr_PD, ptr_GD);
	GUI_DrawBitmap(&Image, 0, 80);

	for (k = 0; k < 1024; k++){
		Cy_SCB_UART_PutArray(KIT_UART_HW, ptr_PD, 25);
		Cy_SysLib_Delay(1);
		Cy_SCB_UART_ClearTxFifoStatus(KIT_UART_HW, CY_SCB_UART_TX_DONE);
		ptr_PD = ptr_PD + 128;
	}

	ptr_PD = &Pixel_Data;

	Cy_SysLib_Delay(500);

	ptr_Image_PD = sobel(ptr_Image_PD, ptr_PD, ptr_GD);
	GUI_DrawBitmap(&Image, 0, 160);

	for (k = 0; k < 1024; k++){
		Cy_SCB_UART_PutArray(KIT_UART_HW, ptr_PD, 25);
		Cy_SysLib_Delay(1);
		Cy_SCB_UART_ClearTxFifoStatus(KIT_UART_HW, CY_SCB_UART_TX_DONE);
		ptr_PD = ptr_PD + 128;
	}

	ptr_PD = &Pixel_Data;

	/* -------------------Set font size, font color to black-------------------- */
	GUI_SetFont(GUI_FONT_16B_1);
	GUI_SetColor(GUI_WHITE);

	/* -------Set text mode to transparent, underlined and center aligned------- */
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetTextAlign(GUI_TA_HCENTER);

	/* ----------------------Print the page title text-------------------------- */
	GUI_DispStringAt("Objects Detected!!", 160, 0);

}

/*******************************************************************************
* Function Name: bool IsBtnClicked
********************************************************************************
*
* Summary: 		This non-blocking function implements SW2 button click check.
*
* Parameters:	None
*
* Return:		Status of the SW2 button:
* 				true when button was pressed and then released and
* 				false in other cases
*
*******************************************************************************/
bool IsBtnClicked(void)
{
    uint32 currBtnState;
    static uint32 prevBtnState  = BTN_RELEASED;

    bool result = false;

    currBtnState = Cy_GPIO_Read(SW2_PORT, SW2_PIN);

    if((prevBtnState == BTN_RELEASED) && (currBtnState == BTN_PRESSED))
    {
        result = true;
    }
    prevBtnState = currBtnState;

    Cy_SysLib_Delay(5);

    return result;
}


/*******************************************************************************
* Function Name: int main(void)
********************************************************************************
*
* Summary: 		This is the main for this code example.  This function does the following
*            	1. Initializes the EmWin display engine
*            	2. Displays startup screen for 3 seconds
*            	3. In an infinite loop, displays the following screens on
*              	key press and release
*                	a. grayscale and image detection
*
* Parameters:	None
*
* Return:		None
*
*******************************************************************************/
int main(void)
{
	uint8 pageNumber = 0;
    /* ------------------------Initializations------------------------------- */
    init_cycfg_all();
    __enable_irq();
    GUI_Init();
    initSPIMaster();
    initI2CMaster();

    cy_stc_scb_uart_context_t KIT_UART_context;

    Cy_SCB_UART_Init(KIT_UART_HW, &KIT_UART_config, &KIT_UART_context);
    Cy_SCB_UART_Enable(KIT_UART_HW);

   /* --------------Display the startup screen for 2 seconds----------------- */
   ShowStartupScreen();
   Cy_SysLib_Delay(2000);

   /* ----------------------Show Instructions Screen------------------------- */
   ShowInstructionsScreen();

   /* ------------------Display various pages in a loop---------------------- */
    for(;;)
    {
        if(IsBtnClicked())
        {
            /* Using pageNumber as index, update the display with a demo screen
               Following are the functions that are called in sequence
                    ShowProcess_Image()
            */
            (*PageArray[pageNumber])();
            
            /* Increment page number */
            pageNumber = pageNumber + 1;

            /* If pagenumber exceeds maximum pages, reset */
            if(pageNumber >= NUMBER_OF_PAGES)
            {
                pageNumber = 0;
            }
        }
    }
}


/* [] END OF FILE */

