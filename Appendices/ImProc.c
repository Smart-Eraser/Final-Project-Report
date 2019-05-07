/*****************************************************************************
* File Name: 	ImProc.c
*
* Version: 		1.0
*
* Description:	This file contains the function definitions for image processing.
* 				Only 80 rows of an image can be evaluated at a time. The expected
* 				resolution is 320 x 240.
*
* Author:		Chris Quesada
*******************************************************************************/

#include <ImProc.h>

/*******************************************************************************
* Function Name: conv2gray(void)
********************************************************************************
*
* Summary: 		Converts an image to grayscale
*
* Parameters:	uint16_t *ptr_Image_PD (points to Image data, unprocessed pixels),
*  				uint16_t *ptr_PD (points to array holding processed pixels),
*  				uint16_t *ptr_GD (points to array holding grayscale pixels)
*
* Return:		Current pointer position to orignal pixel data (*ptr_Image_PD)
*******************************************************************************/
unsigned short* conv2gray( uint16_t *ptr_Image_PD, uint16_t *ptr_PD, uint16_t *ptr_GD  ) {

	uint16_t 	pixel 			= 0;													// original pixel data -> processed pixel data
	uint8   	R				= 0;													// Red intensity
	uint8   	G				= 0;													// Green intensity
	uint8   	B				= 0;													// Blue intensity
	uint16_t	R_processed		= 0;													// "Gray" red intensity
	uint16_t	G_processed		= 0;													// "Gray" green intensity
	uint16_t	B_processed		= 0;													// "Gray" blue intensity
	double  	Gray_pixel 		= 0;													// Stores calculated gray intensity
	int 		k 				= 0;													// counter

	for (k = 0 ; k < Length*Height ; k++) {
		pixel				= *ptr_Image_PD;											// Pull image data
		R 					= ((pixel & 0b1111100000000000) >> 11 << 3);				// Isolate red intensity, scale to 8-bits (0-255 scale)
		G					= ((pixel & 0b0000011111100000) >> 5 << 2);					// Isolate green intensity, scale to 8-bits (0-255 scale)
		B					= (pixel & 0b0000000000011111) << 3;						// Isolate blue intensity, scale to 8-bits (0-255 scale)
		Gray_pixel 			= (R * 0.2126) + (G * 0.7152) + (B * 0.0722);				// Grayscale conversion algorithm, Luminance method (BT.709)
		R_processed		    = ((uint16_t)Gray_pixel)>> 3 << 11;							// descale to 5-bits, deisolate and store "gray" red intensity
		G_processed 		= ((uint16_t)Gray_pixel)>> 2 << 5;							// descale to 6-bits, deisolate and store "gray" green intensity
		B_processed 		= (uint16_t)Gray_pixel >> 3;								// descale to 5-bits, deisolate and store "gray" blue intensity
		pixel 				= (uint16_t)(R_processed + G_processed + B_processed);		// add gray intensities together to form grayscale pixel
		*ptr_GD				= pixel;													// update grayscale data array
		*ptr_PD 			= pixel;													// update pixel data array
		ptr_GD				= ptr_GD + 1;												// increment grayscale pointer
		ptr_PD				= ptr_PD + 1;												// increment pixel pointer
		ptr_Image_PD  		= ptr_Image_PD + 1;											// increment image pointer
	}
	return ptr_Image_PD;																// returns current position in image array
}

/*******************************************************************************
* Function Name: sobel(void)
********************************************************************************
*
* Summary: 		Takes image data, calls conv2gray(), and detects edges using
* 				Sobel operator.
*
* Parameters:	uint16_t *ptr_Image_PD (points to Image data, unprocessed pixels),
*  				uint16_t *ptr_PD (points to array holding processed pixels),
*  				uint16_t *ptr_GD (points to array holding grayscale pixels)
*
* Return:		Current pointer position to orignal pixel data (*ptr_Image_PD)
*******************************************************************************/
unsigned short* sobel( uint16_t *ptr_Image_PD, uint16_t *ptr_PD, uint16_t *ptr_GD ) {

	int k 								= 0;
	int bound							= Length*Height;								// Specifies how many rows are being evaluated
	uint16_t *end 						= conv2gray(ptr_Image_PD, ptr_PD, ptr_GD);		// last row evaluated

	/* ************************************************************************
	 * Sobel kernel variant, negatives will be accounted for
	 * in actual calculation. By using an array of {1,2,1} instead of all 9
	 * values, as shown below, you can use the same kernel for both vertical and horizontal
	 * gradients.
	 *
	 * 				| -1| 0 | 1 |
	 * 				| -2| 0 | 2 |
	 * 				| -1| 0 | 1 |
	 *
	 * ***********************************************************************/
	int sobel_kernel[3] 				= { 1, 2, 1};

	float Gx 							= 0;											// Horizontal gradient
	float Gy 							= 0;											// Vertical gradient
	float G								= 0;											// Magnitude of gradient

	/* ************************************************************************
	 * Start kernel in correct location (not on a bound/edge of image array)
	 *
	 * 				|bnd|bnd|bnd|
	 * 				|bnd| X |	|
	 * 				|bnd|   |   |
	 *
	 * ***********************************************************************/
	ptr_GD 								= ptr_GD + (Length + 1);

	/* ************************************************************************
	 * Evaluate area next to upper bound to keep image consistent
	 * ***********************************************************************/
	for (k = 1; k < Length; k++){
		if (*(ptr_PD + Length) == 0xFFF){
				*ptr_PD = 0xFFF;
				}
				else {
					*ptr_PD = 0x0000;
					ptr_PD = ptr_PD + 1;
				}
		}

	ptr_PD = ptr_PD + 2;																// Align pointer after upper bound evaluation

	/* ************************************************************************
	 * Account for top, bottom and sides of gray pixel array data so that the
	 * sobel kernel convolution does not go out of bounds.
	 * ***********************************************************************/
	for (k = Length + 1; k < bound - Length; k++){

		if ((k + 1) % Length == 0) {
			ptr_GD = ptr_GD + 2;
			ptr_PD = ptr_PD + 2;
			k = k + 2;
		}

		/* ----------------Horizontal gradient calculation----------------- */
		Gx = (sobel_kernel[0])*(*(ptr_GD - Length + 1)) 	+ 	(sobel_kernel[1])*(*(ptr_GD + 1)) 	 			+
			 (sobel_kernel[2])*(*(ptr_GD + Length + 1))		- 	(sobel_kernel[0])*(*(ptr_GD - Length - 1))    	-
			 (sobel_kernel[1])*(*(ptr_GD - 1))				- 	(sobel_kernel[2])*(*(ptr_GD + Length - 1));

		/* ----------------Vertical gradient calculation------------------- */
		Gy = (sobel_kernel[0])*(*(ptr_GD - Length + 1)) 	+ 	(sobel_kernel[1])*(*(ptr_GD - Length)) 	 		+
			 (sobel_kernel[2])*(*(ptr_GD - Length - 1))		- 	(sobel_kernel[0])*(*(ptr_GD + Length + 1))    	-
			 (sobel_kernel[1])*(*(ptr_GD + Length))			- 	(sobel_kernel[2])*(*(ptr_GD + Length - 1));

		/* -------------------Magnitude of gradient------------------------ */
		 G = (sqrt(pow(Gx,2) + pow(Gy,2)));

		 /* -----------store gradient to pixel data array------------------ */
		*ptr_PD = (uint16_t)G;

		/*********************************************************************
		 * Check gradient against threshold value (threshold can be adjusted
		 * in ImProc.h). Depending on whether or not the gradient is less than
		 * or greater than, pixels will be set to either black or white.
		 ********************************************************************/
		if (*ptr_PD > Threshold) {
					*ptr_PD = 0xFFFF;
				}
				else {
					*ptr_PD = 0x0000;
				}

		/* --------------------Increment necessary pointers---------------- */

		ptr_GD = ptr_GD + 1;
		ptr_PD = ptr_PD + 1;

	}

	/* ************************************************************************
	 * Evaluate area next to lower bound to keep image consistent
	 * ***********************************************************************/

	for (k = bound - Length ; k < bound; k++){
		if (*(ptr_PD - Length) == 0xFFF){
			*ptr_PD = 0xFFF;
			}
			else {
				*ptr_PD = 0x0000;
				ptr_PD = ptr_PD + 1;
			}
	}
	return end;

}

/* [] END OF FILE */
