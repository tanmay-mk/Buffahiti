/*********************************************************************************************
 * PES Assignment 4
 * File Name: state_machine.c
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/
#include "fsl_debug_console.h"
/*
 * OTHER FILES TO BE INCLUDED
 */

#include "state_machine.h"
#include "log.h"

 /*
  * GLOBAL VARIABLES
  */

/*
 * @brief:
 *
 * touch_value			: A variable that stores the value returned by
 * 						Touch_Scan_LH() function which is then used to
 * 						determine whether a touch was detected or not.
 *
 * touch_poll_variable	: A variable specifically used to poll for touch sensor
 * 						and GPIO interrupt every 100mSec. The variable is
 * 						incremented by 1 every time the polling turns out to
 * 						be unfruitful. It is reset to 1 otherwise.
 *
 * 	timer_value			: A variable that is used to get the number of systick
 * 						interrupts since the last time the state was changed.
 *
 * 	switch_value		: A variable that is either 1 or 0 depending on the
 * 						presence of GPIO interrupt.
 */

volatile uint32_t touch_value=0;

uint32_t touch_poll_variable=1;

uint32_t timer_value=0;

uint32_t switch_value=0;

uint32_t variable_for_ON=0, variable_for_OFF=0;


void state_machine()
{
	/*
	 * @brief: LED color configuration of STOP state
	 */
	color_configuration* STOP =(color_configuration *) malloc(sizeof(color_configuration));
	STOP->red_value 					= 0x61;
	STOP->green_value 					= 0x1E;
	STOP->blue_value 					= 0x3C;

	/*
	 * @brief: LED color configuration of GO state
	 */
	color_configuration* GO = (color_configuration *)malloc(sizeof(color_configuration));
	GO->red_value 						= 0x22;
	GO->green_value 					= 0x96;
	GO->blue_value 						= 0x22;

	/*
	 * @brief: LED color configuration of WARNING state
	 */
	color_configuration* WARNING = (color_configuration *)malloc(sizeof(color_configuration));
	WARNING->red_value 					= 0xFF;
	WARNING->green_value 				= 0xB2;
	WARNING->blue_value 				= 0x00;

	/*
	 * @brief: LED color configuration of CROSSWALK state
	 */
	color_configuration* CROSSWALK = (color_configuration *)malloc(sizeof(color_configuration));
	CROSSWALK->red_value 				= 0x00;
	CROSSWALK->green_value 				= 0x10;
	CROSSWALK->blue_value 				= 0x30;

	/*
	 * @brief: LED color transition specifics for STOP to GO state
	 */
	color_transition* STOP_TO_GO = (color_transition *)malloc(sizeof(color_transition));
	STOP_TO_GO->red_start 				= STOP->red_value;
	STOP_TO_GO->green_start 			= STOP->green_value;
	STOP_TO_GO->blue_start 				= STOP->blue_value;
	STOP_TO_GO->red_end 				= GO->red_value;
	STOP_TO_GO->green_end 				= GO->green_value;
	STOP_TO_GO->blue_end 				= GO->blue_value;

	/*
	 * @brief: LED color transition specifics for GO to WARNING state
	 */
	color_transition* GO_TO_WARNING = (color_transition *)malloc(sizeof(color_transition));
	GO_TO_WARNING->red_start 			= GO->red_value;
	GO_TO_WARNING->green_start	 		= GO->green_value;
	GO_TO_WARNING->blue_start 			= GO->blue_value;
	GO_TO_WARNING->red_end 				= WARNING->red_value;
	GO_TO_WARNING->green_end 			= WARNING->green_value;
	GO_TO_WARNING->blue_end 			= WARNING->blue_value;

	/*
	 * @brief: LED color transition specifics for WARNING to STOP state
	 */
	color_transition* WARNING_TO_STOP = (color_transition *)malloc(sizeof(color_transition));
	WARNING_TO_STOP->red_start 			= WARNING->red_value;
	WARNING_TO_STOP->green_start 		= WARNING->green_value;
	WARNING_TO_STOP->blue_start 		= WARNING->blue_value;
	WARNING_TO_STOP->red_end 			= STOP->red_value;
	WARNING_TO_STOP->green_end 			= STOP->green_value;
	WARNING_TO_STOP->blue_end 			= STOP->blue_value;

	/*
	 * @brief: LED color transition specifics for STOP to CROSSWALK state
	 */
	color_transition* STOP_TO_CROSSWALK = (color_transition *)malloc(sizeof(color_transition));
	STOP_TO_CROSSWALK->red_start 		= STOP->red_value;
	STOP_TO_CROSSWALK->green_start 		= STOP->green_value;
	STOP_TO_CROSSWALK->blue_start 		= STOP->blue_value;
	STOP_TO_CROSSWALK->red_end 			= CROSSWALK->red_value;
	STOP_TO_CROSSWALK->green_end 		= CROSSWALK->green_value;
	STOP_TO_CROSSWALK->blue_end 		= CROSSWALK->blue_value;

	/*
	 * @brief: LED color transition specifics for GO to CROSSWALK state
	 */
	color_transition* GO_TO_CROSSWALK = (color_transition *)malloc(sizeof(color_transition));
	GO_TO_CROSSWALK->red_start 			= GO->red_value;
	GO_TO_CROSSWALK->green_start 		= GO->green_value;
	GO_TO_CROSSWALK->blue_start 		= GO->blue_value;
	GO_TO_CROSSWALK->red_end 			= CROSSWALK->red_value;
	GO_TO_CROSSWALK->green_end 			= CROSSWALK->green_value;
	GO_TO_CROSSWALK->blue_end 			= CROSSWALK->blue_value;

	/*
	 * @brief: LED color transition specifics for WARNING to CROSSWALK state
	 */
	color_transition* WARNING_TO_CROSSWALK = (color_transition *)malloc(sizeof(color_transition));
	WARNING_TO_CROSSWALK->red_start 	= WARNING->red_value;
	WARNING_TO_CROSSWALK->green_start 	= WARNING->green_value;
	WARNING_TO_CROSSWALK->blue_start 	= WARNING->blue_value;
	WARNING_TO_CROSSWALK->red_end 		= CROSSWALK->red_value;
	WARNING_TO_CROSSWALK->green_end 	= CROSSWALK->green_value;
	WARNING_TO_CROSSWALK->blue_end 		= CROSSWALK->blue_value;

	/*
	 * @brief: LED color transition specifics for CROSSWALK to GO state
	 */
	color_transition* CROSSWALK_TO_GO = (color_transition *)malloc(sizeof(color_transition));
	CROSSWALK_TO_GO->red_start 			= CROSSWALK->red_value;
	CROSSWALK_TO_GO->green_start 		= CROSSWALK->green_value;
	CROSSWALK_TO_GO->blue_start 		= CROSSWALK->blue_value;
	CROSSWALK_TO_GO->red_end 			= GO->red_value;
	CROSSWALK_TO_GO->green_end			= GO->green_value;
	CROSSWALK_TO_GO->blue_end 			= GO->blue_value;

	color_transition* TO_CROSSWALK = (color_transition *)malloc(sizeof(color_transition));
	TO_CROSSWALK->red_start 			= 0;
	TO_CROSSWALK->green_start 			= 0;
	TO_CROSSWALK->blue_start 			= 0;
	TO_CROSSWALK->red_end 				= CROSSWALK->red_value;
	TO_CROSSWALK->green_end 			= CROSSWALK->green_value;
	TO_CROSSWALK->blue_end 				= CROSSWALK->blue_value;

	while (1)
	{

		state currentState;							//a variable that will select the operation based
													//on current state of the state machine

		static state nextState = 0;					//a variable that will determine the next state
													//of the state machine based on the changes occured
													//during the course of operation

		currentState = nextState;


		switch(currentState)
		{
		/*
		 *@brief: As soon as the state machine starts, first state is STOP state.
		 *			The state machine stays in this state for a total of 20 seconds
		 *			(5 seconds in DEBUG mode) unless CROSSWALK state is requested.
		 */
		case STOP_STATE:
			if (get_timer()<TWENTY_SECONDS)
			{
				timer_value = get_timer();
				if (timer_value>=(2*touch_poll_variable))			//polling for touch slider & GPIO interrupt every
				{													//100mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)			//if any one of them is true, then we change the state
					{												//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif

						//resetting the counter
						reset_count();
						touch_poll_variable = 1;
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_STOP_TO_CROSSWALK.\n", now()*50-50);
						#endif
						//resetting the GPIO interrupt variable
						switch_value=0;
						nextState = TRANSITION_STOP_TO_CROSSWALK;
						break;
					}
					touch_poll_variable++;
				}
				LED_ON(STOP->red_value, STOP->green_value, STOP->blue_value);
				nextState = STOP_STATE;
			}
			else if (get_timer()>TWENTY_SECONDS)
			{
				//resetting the counter
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to TRANSITION_STOP_TO_GO.\n", now()*50-50);
				#endif
				nextState = TRANSITION_STOP_TO_GO;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to GO
		 * 			state, unless CROSSWALK is requested.
		 */
		case TRANSITION_STOP_TO_GO:
			if (get_timer()<ONE_SECOND)
			{
				if (timer_value>=(2*touch_poll_variable))		//polling for touch slider & GPIO interrupt every
				{												//100mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)		//if any one of them is true, then we change the state
					{											//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif
						//resetting the counter
						reset_count();
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_TO_CROSSWALK.\n", now()*50-50);
						#endif
						nextState = TRANSITION_TO_CROSSWALK;
						switch_value=0;
						touch_poll_variable = 1;
						break;
					}
					touch_poll_variable++;
				}
				transition(STOP_TO_GO);
				nextState = TRANSITION_STOP_TO_GO;
			}
			else if (get_timer()>ONE_SECOND)
			{
				touch_poll_variable = 1;
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to GO_STATE.\n", now()*50-50);
				#endif
				nextState = GO_STATE;
			}
			break;

		/*
		 *@brief: 	Next state after STOP state & CROSSWALK state is GO state.
		 *			The state machine stays in this state for a total of 20 seconds
		 *			(5 seconds in DEBUG mode) unless CROSSWALK state is requested.
		 */
		case GO_STATE:
			if (get_timer()<TWENTY_SECONDS)
			{
				timer_value = get_timer();
				if (timer_value>=(2*touch_poll_variable))			//polling for touch slider & GPIO interrupt every
				{													//100mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)			//if any one of them is true, then we change the state
					{												//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif
						reset_count();
						touch_poll_variable = 1;
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_GO_TO_CROSSWALK.\n", now()*50-50);
						#endif
						switch_value=0;
						nextState = TRANSITION_GO_TO_CROSSWALK;
						break;
					}
					touch_poll_variable++;
				}
				LED_ON(GO->red_value, GO->green_value, GO->blue_value);
				nextState = GO_STATE;
			}
			else if (get_timer()>TWENTY_SECONDS)
			{
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to TRANSITION_GO_TO_WARNING.\n", now()*50-50);
				#endif
				nextState = TRANSITION_GO_TO_WARNING;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to WARNING
		 * 			state, unless CROSSWALK is requested.
		 */
		case TRANSITION_GO_TO_WARNING:
			if (get_timer()<ONE_SECOND)
			{
				if (timer_value>=(2*touch_poll_variable))		//polling for touch slider & GPIO interrupt every
				{												//100mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)		//if any one of them is true, then we change the state
					{											//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif
						reset_count();
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_TO_CROSSWALK.\n", now()*50-50);
						#endif
						nextState = TRANSITION_TO_CROSSWALK;
						switch_value=0;
						touch_poll_variable = 1;
						break;
					}
					touch_poll_variable++;
				}
				transition(GO_TO_WARNING);
				nextState = TRANSITION_GO_TO_WARNING;
			}
			else if (get_timer()>ONE_SECOND)
			{
				touch_poll_variable = 1;
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to WARNING_STATE.\n", now()*50-50);
				#endif
				nextState = WARNING_STATE;
			}
			break;

		/*
		 *@brief: 	Next state after GO state is WARNING state.
		 *			The state machine stays in this state for a total of 5 seconds
		 *			(3 seconds in DEBUG mode) unless CROSSWALK state is requested.
		 */
		case WARNING_STATE:
			if (get_timer()<FIVE_SECONDS)
			{
				timer_value = get_timer();
				if (timer_value>=(2*touch_poll_variable))	//polling for touch sensor & GPIO interrupt every
				{											//100mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)	//if any one of them is true, then we change the state
					{										//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif
						reset_count();
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_WARNING_TO_CROSSWALK.\n", now()*50-50);
						#endif
						nextState = TRANSITION_WARNING_TO_CROSSWALK;
						switch_value=0;
						touch_poll_variable = 1;
						break;
					}
					touch_poll_variable++;
				}
				LED_ON(WARNING->red_value, WARNING->green_value, WARNING->blue_value);
				nextState = WARNING_STATE;
			}
			else if (get_timer()>FIVE_SECONDS)
			{
				touch_poll_variable = 1;
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to TRANSITION_WARNING_TO_STOP.\n", now()*50-50);
				#endif
				nextState = TRANSITION_WARNING_TO_STOP;
			}
			break;

	   /*
		* @brief: The state machine remains in this state for 1 second. It
		* 			gradually changes the color of LED, and then goes to STOP
		* 			state, unless CROSSWALK is requested.
		*/
		case TRANSITION_WARNING_TO_STOP:
			if (get_timer()<ONE_SECOND)
			{
				if (timer_value>=(2*touch_poll_variable))		//polling for touch sensor & GPIO interrupt every
				{												//100mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)		//if any one of them is true, then we change the state
					{											//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif
						reset_count();
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_TO_CROSSWALK.\n", now()*50-50);
						#endif
						nextState = TRANSITION_TO_CROSSWALK;
						switch_value=0;
						touch_poll_variable = 1;
						break;
					}
					touch_poll_variable++;
				}
				transition(WARNING_TO_STOP);
				nextState = TRANSITION_WARNING_TO_STOP;
			}
			else if (get_timer()>ONE_SECOND)
			{
				touch_poll_variable = 1;
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to STOP_STATE.\n", now()*50-50);
				#endif
				nextState = STOP_STATE;
			}
			break;
		/*
		 * @brief: 	This state is triggered only after there is a GPIO interrupt
		 * 			present or touch has been detected on the TSI surface.
		 *			The state machine stays in this state for a total of 10 seconds,
		 *			keeping the LED ON for 750mSec and OFF for 250mSec. Then it
		 *			changes the state to GO state.
		 */
		case CROSSWALK_STATE:
			NVIC_DisableIRQ(PORTD_IRQn);
			if (get_timer()<TEN_SECONDS)
			{
				timer_value = get_timer();
				if(timer_value >= SEVEN_FIFTY_MILLISECONDS + variable_for_ON)
				{
					LED_ON(0,0,0);
					variable_for_ON += ONE_SECOND;
				}
				else if (timer_value >= TWO_FIFTY_MILLISECONDS + variable_for_OFF)
				{
					LED_ON(CROSSWALK->red_value, CROSSWALK->green_value, CROSSWALK->blue_value);
					variable_for_OFF += ONE_SECOND;
				}
			}
			else if (get_timer()>TEN_SECONDS)
			{
				variable_for_ON = 0;
				variable_for_OFF = 0;
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to TRANSITION_CROSSWALK_TO_GO.\n", now()*50);
				#endif
				nextState = TRANSITION_CROSSWALK_TO_GO;
				break;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to CROSSWALK
	   	 * 			state.
		 */
		case TRANSITION_STOP_TO_CROSSWALK:
			if (get_timer()<ONE_SECOND)
			{
				transition(STOP_TO_CROSSWALK);
				nextState = TRANSITION_STOP_TO_CROSSWALK;
			}

			else if (get_timer()>ONE_SECOND)
			{
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to CROSSWALK_STATE.\n", now()*50-50);
				#endif
				nextState = CROSSWALK_STATE;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to CROSSWALK
	   	 * 			state.
		 */
		case TRANSITION_GO_TO_CROSSWALK:
			if (get_timer()<ONE_SECOND)
			{
				transition(GO_TO_CROSSWALK);
				nextState = TRANSITION_GO_TO_CROSSWALK;
			}
			else if (get_timer()>ONE_SECOND)
			{
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to CROSSWALK_STATE.\n", now()*50-50);
				#endif
				nextState = CROSSWALK_STATE;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to CROSSWALK
	   	 * 			state.
		 */
		case TRANSITION_WARNING_TO_CROSSWALK:
			if (get_timer()<ONE_SECOND)
			{
				transition(WARNING_TO_CROSSWALK);
				nextState = TRANSITION_WARNING_TO_CROSSWALK;
			}
			else if (get_timer()>ONE_SECOND)
			{
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to CROSSWALK_STATE.\n", now()*50-50);
				#endif
				nextState = CROSSWALK_STATE;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to GO
	   	 * 			state.
		 */
		case TRANSITION_CROSSWALK_TO_GO:
			if (get_timer()<ONE_SECOND)
			{
				timer_value = get_timer();
				if (timer_value>=(2*touch_poll_variable))	//polling for touch sensor and GPIO interrupt every
				{											//100 mSec
					touch_value = Touch_Scan_LH();
					switch_value = switch_pressed();
					if (touch_value>150 || switch_value)	//if any one of them is true then we change the state
					{										//to CROSSWALK
						#if DEBUG
							if (touch_value>150)
							{
								LOG("%d mSec\t\t:Touch Detected!\n", now()*50-50);
							}
							if (switch_value)
							{
								LOG("%d mSec\t\t:Button Press Detected!\n", now()*50-50);
							}
						#endif
						reset_count();
						touch_poll_variable = 1;
						#if DEBUG
							LOG("%d mSec\t\t:Changning State to TRANSITION_TO_CROSSWALK.\n", now()*50-50);
						#endif
						nextState = TRANSITION_TO_CROSSWALK;
						switch_value=0;
						break;
					}
					touch_poll_variable++;
				}
				transition(CROSSWALK_TO_GO);
				nextState = TRANSITION_CROSSWALK_TO_GO;
			}
			else if (get_timer()>ONE_SECOND)
			{
				reset_count();
				touch_poll_variable = 1;
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to GO_STATE.\n", now()*50-50);
				#endif
				nextState = GO_STATE;
			}
			break;

		/*
		 * @brief: The state machine remains in this state for 1 second. It
		 * 			gradually changes the color of LED, and then goes to CROSSWALK
	   	 * 			state.
		 */
		case TRANSITION_TO_CROSSWALK:
			if (get_timer()<ONE_SECOND)
			{
				transition(TO_CROSSWALK);
				nextState = TRANSITION_TO_CROSSWALK;
			}
			else if (get_timer()>ONE_SECOND)
			{
				reset_count();
				#if DEBUG
					LOG("%d mSec\t\t:Changning State to CROSSWALK_STATE.\n", now()*50-50);
				#endif
				nextState = CROSSWALK_STATE;
			}
			break;

		default:
			break;

		} 		//switch

	}			//while

}				//state_machine

void transition(color_transition* color)
{
	static int current_red, current_green, current_blue;

	if (color->red_start == 0 && color->green_start == 0 && color->green_start == 0)
	{
		color->red_start 	= current_red;
		color->green_start 	= current_green;
		color->blue_start 	= current_blue;
	}


	int red_difference, blue_difference, green_difference;

	red_difference = (color->red_end) - (color->red_start);
	green_difference = (color->green_end) - (color->green_start);
	blue_difference = (color->blue_end) - (color->blue_start);

	timer_value = get_timer();
	current_red = red_difference*(0.05*timer_value) + color->red_start;
	current_green = green_difference*(0.05*timer_value)+color->green_start;
	current_blue = blue_difference*(0.05*timer_value)+color->blue_start;

	LED_ON(current_red, current_green, current_blue);
}
