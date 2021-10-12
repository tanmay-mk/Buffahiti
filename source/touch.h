/*******************************************************************************************
 * PES Assignment 4
 * File Name: touch.h
 * Author: Alexander G. Dean
 * Github Link:https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense.
 *******************************************************************************************/

#ifndef __TOUCH_SENSOR_INTERFACE__
#define __TOUCH_SENSOR_INTERFACE__

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*****************************************************
 * 					MACROS
 *****************************************************/
#define TOUCH_OFFSET 550  // offset value to be subtracted
#define TOUCH_DATA ((TSI0->DATA) & 0xFFFF)//macro for extracting the count from data register

/*****************************************************
 * 					GLOBAL VARIABLES
 *****************************************************/

extern volatile uint32_t touch_value;

/*****************************************************
 * @brief:Initializes touch sensor interface
 * @parameters: none
 * Returns: none
 *****************************************************/
void Touch_Init();

/*****************************************************
 * @brief:Checks for the change in capacitance of the
 * 			touch sensor
 * @parameters: none
 * Returns: Scanned value on the touch sensor
 *****************************************************/
uint32_t Touch_Scan_LH(void);

#endif /*__TOUCH_SENSOR_INTERFACE__*/
