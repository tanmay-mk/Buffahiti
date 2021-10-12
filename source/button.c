/*********************************************************************************************
 * PES Assignment 4
 * File Name: button.c
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/
/*
 * LIBRARY FILES TO BE INCLUDED
 */
#include "LOG.h"
#include "fsl_debug_console.h"
#include "MKL25Z4.h"

/*
 * OTHER FILES TO BE INCLUDED
 */
#include "button.h"


/*
 * GLOBAL VARIABLES
 */
volatile int button_press = 0;


void switch_init()
{
	//initialize clock to the port D
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//clear port D pin 3
	PORTD->PCR[GPIO_PIN] &= ~PORT_PCR_MUX_MASK;
	//set port pin as GPIO
	PORTD->PCR[GPIO_PIN] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= ~(1 << GPIO_PIN);
	PORTD->PCR[GPIO_PIN]|=PORT_PCR_PS(1)|PORT_PCR_PE(1UL);
	NVIC_SetPriority(PORTD_IRQn,4);
	NVIC_EnableIRQ(PORTD_IRQn);
	PORTD->PCR[GPIO_PIN]|=PORT_PCR_IRQC(10UL);
}


void PORTD_IRQHandler()
{
	//disable irq
    NVIC_DisableIRQ(PORTD_IRQn);

    //set flag to 1
	button_press = 1;
	PORTD->ISFR&=(1<<GPIO_PIN);
}


int switch_pressed()
{
	//this funciton is called every 100mSec during polling
	//to avoid the pending interrupts, we disable the irq
  NVIC_DisableIRQ(PORTD_IRQn);
  int switch_value = button_press;

  button_press = 0;

  NVIC_EnableIRQ(PORTD_IRQn);
  return switch_value;
}
