/*********************************************************************************************
 * PES Assignment 4
 * File Name: led_on.c
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/

/*
 * OTHER FILES TO BE INCLUDED
 */

#include "led_on.h"
#include "state_machine.h"

void LED_ON(uint32_t red_value, uint32_t green_value, uint32_t blue_value)
{
		TPM2->CONTROLS[0].CnV = red_value;
		TPM2->CONTROLS[1].CnV = green_value;
		TPM0->CONTROLS[1].CnV = blue_value;
}
