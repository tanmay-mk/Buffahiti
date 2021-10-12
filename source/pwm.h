/*********************************************************************************************
 * PES Assignment 4
 * File Name: pwm.h
 * Author: Alexander G. Dean
 * GitHub Link:https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/PWM_LED/Source/timers.c
 ********************************************************************************************/
#ifndef _PWM_H_
#define _PWM_H_

/*
 * LIBRARY FILES TO BE INCLUDED
 */
#include "MKL25Z4.h"

/*
 * MACROS
 */
#define RED_LED_PIN 18
#define GREEN_LED_PIN 19
#define BLUE_LED_PIN 1

/*
 * @brief: 					Initializes the Blue LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
void Init_Blue_LED_PWM();

/*
 * @brief: 					Initializes the Red LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
void Init_Red_LED_PWM();

/*
 * @brief: 					Initializes the Grenn LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
void Init_Green_LED_PWM();

#endif /*_PWM_H*/
