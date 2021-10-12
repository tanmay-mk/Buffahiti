/*********************************************************************************************
 * PES Assignment 4
 * File Name: button.h
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/
#ifndef _BUTTON_H_
#define _BUTTON_H_

/*
 * LIBRARY FILES TO BE INCLUDED
 */
#include "MKL25Z4.h"


/*
 * MACROS
 */
#define GPIO_PIN 3 //port D pin 3

/*
 * @brief: Initializes GPIO interrupt by using Port D pin 3
 *
 * @parameters: none
 *
 * @returns: nnone
 */
void switch_init();

/*
 * @brief: GPIO Interrupt routine
 *
 * @parameters: None
 *
 * @returns: none
 */
void PORTD_IRQHandler();

/*
 * @brief: A function that returns 1 or 0, when called, depending
 * 			upon whether the GPIO interrupt has occurred or not.
 *
 * @parameters: None
 *
 * @returns: 	switch_value: Returns 0 if interrupt is absent
 * 								Returns 1 otherwise.
 */
int switch_pressed();

#endif /*_BUTTON_H_*/
