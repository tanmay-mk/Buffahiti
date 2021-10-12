/*********************************************************************************************
 * PES Assignment 4
 * File Name: led_on.h
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/
#ifndef _LED_H_
#define _LED_H_

/*
 * OTHER FILES TO BE INCLUDED
 */
#include "pwm.h"

/*
 * @brief: 					Turns on LED with specific RGB value.
 *
 * @parameters:
 * 			red_value:		Turns ON the LED with a specific duty cycle
 * 							for RED color.
 * 			green_value: 	Turns ON the LED with a specific duty cycle
 * 							for GREEN color.
 * 			blue_value:		Turns ON the LED with a specific duty cycle
 * 							for RED color.
 *
 * @returns: 				None.
 */
void LED_ON(uint32_t red_value, uint32_t green_value, uint32_t blue_value);

#endif /*_LED_H_*/
