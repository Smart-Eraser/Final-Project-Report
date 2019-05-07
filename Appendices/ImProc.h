/******************************************************************************
* File Name: 	ImProc.h
*
* Version: 		1.0
*
* Description: 	This file contains function prototypes for image processing.
*
* Author:		Chris Quesada
*******************************************************************************/
#ifndef IMPROC_H
#define IMPROC_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include "cy_pdl.h"
#include "cycfg.h"

/* Image Processing Parameters */
#define Max_Length					(320)
#define Max_Height					(240)
#define	Length						(320)
#define Height						(80)
#define Pixel_Count_1				(25600)
#define	Pixel_Count_2				(16960)
#define Threshold					(40000)

//Prototype of functions

//allocation of memory
unsigned short* conv2gray( uint16_t *ptr_Image_PD, uint16_t *ptr_PD,uint16_t *ptr_GD ) ;
unsigned short* sobel( uint16_t *ptr_Image_PD, uint16_t *ptr_PD, uint16_t *ptr_GD ) ;

#endif
