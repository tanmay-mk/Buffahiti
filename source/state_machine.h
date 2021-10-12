/*********************************************************************************************
 * PES Assignment 4
 * File Name: state_machine.h
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

/*
 * LIBRARY FILES TO BE INCLUDED
 */
#include <stdint.h>
#include <stdio.h>
#include<stdlib.h>
#include "board.h"

/*
 * OTHER FILES TO BE INCLUDED
 */
#include "led_on.h"
#include "systick.h"
#include "touch.h"
#include "button.h"
/*
 * MACROS
 */
#if DEBUG
#define TWENTY_SECONDS 				100
#define FIVE_SECONDS				60

#else
#define TWENTY_SECONDS 				400
#define FIVE_SECONDS				100
#endif

#define TEN_SECONDS					200
#define ONE_SECOND					20
#define SEVEN_FIFTY_MILLISECONDS	15
#define TWO_FIFTY_MILLISECONDS		5
/*
 * @brief: 					An enumeration of all the possible states with
 * 							various numeric values assigned to each state.
 */
typedef enum {
	STOP_STATE							= 0,
	GO_STATE							= 1,
	WARNING_STATE						= 2,
	CROSSWALK_STATE						= 4,
	TRANSITION_STOP_TO_GO				= 8,
	TRANSITION_GO_TO_WARNING			= 16,
	TRANSITION_WARNING_TO_STOP			= 32,
	TRANSITION_STOP_TO_CROSSWALK		= 64,
	TRANSITION_GO_TO_CROSSWALK			= 128,
	TRANSITION_WARNING_TO_CROSSWALK		= 512,
	TRANSITION_CROSSWALK_TO_GO			= 1024,
	TRANSITION_TO_CROSSWALK				= 2048
}state;

/*
 * @brief: 					A structure that configures the Red, Green
 * 							& Blue values of a specific RGB color.
 */
typedef struct colors {
	uint32_t red_value;
	uint32_t green_value;
	uint32_t blue_value;
} color_configuration;

/*
 * @brief: 					A structure that configures the transition state
 * 							from one color to another. It defines the starting
 * 							R, G & B values of a color and the end R, G, B values
 * 							of the color to whihc the color is supposed to be changed.
 */
typedef struct color_change {
	uint32_t red_start;
	uint32_t green_start;
	uint32_t blue_start;
	uint32_t red_end;
	uint32_t green_end;
	uint32_t blue_end;
} color_transition;

/*
 * @brief: 					A finite state machine which handles all the cases
 * 							which are necessary for the entire operation.
 *
 * @parameters:				None.
 *
 * @Returns 				None.
 */
void state_machine();

/*
 * @brief: 					Transitions from a previous color to next color
 * 							by taking RGB values of current color and next
 * 							intended color.
 *
 * @parameters:
 * 				color:		A data structure of type color_transition which takes 6
 * 							values as inputs.
 *
 * @Returns 				None.
 */
void transition(color_transition* color);

#endif /*_STATE_MACHINE_H_*/
