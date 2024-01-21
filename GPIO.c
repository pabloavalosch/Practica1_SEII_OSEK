/*
 * GPIO.c
 *
 *  Created on: 4 oct 2023
 *      Author: pablo
 */

#include <GPIO.h>
#include "leds.h"
#include "fsl_gpio.h"
#include "fsl_port.h"


void GPIO_init(void)
{
	//Enable port clocks
	EnablePortClock(SIM_SCGC5_PORTE_MASK);
	EnablePortClock(SIM_SCGC5_PORTB_MASK);

	//Config mux port as GPIO
	SetPin_GPIO(RED_LED_PORT,RED_LED_PIN);
	SetPin_GPIO(BLUE_LED_PORT,BLUE_LED_PIN);
	SetPin_GPIO(GREEN_LED_PORT,GREEN_LED_PIN);


	//Config GPIO direction as output
	RED_LED_GPIO->PDDR |= RED_LED_MASK;
	BLUE_LED_GPIO->PDDR |= BLUE_LED_MASK;
	GREEN_LED_GPIO->PDDR |= GREEN_LED_MASK;


}
