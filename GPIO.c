/*
 * GPIO.c
 *
 *  Created on: 4 oct 2023
 *      Author: pablo
 */

#include <GPIO.h>
#include "config.h"
#include <OSEK.h>
#include "fsl_gpio.h"
#include "fsl_port.h"

void PORTD_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOD);
	GPIO_PortClearInterruptFlags(GPIOD, irq_status);
	//activate_task(2);

}

void PORTA_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA);
	GPIO_PortClearInterruptFlags(GPIOA, irq_status);
	terminate_task();

}


void GPIO_init(void)
{
	//Enable port clocks
	EnablePortClock(SIM_SCGC5_PORTC_MASK);
	EnablePortClock(SIM_SCGC5_PORTA_MASK);
	EnablePortClock(SIM_SCGC5_PORTE_MASK);
	EnablePortClock(SIM_SCGC5_PORTB_MASK);

	//Config mux port as GPIO
	SetPin_GPIO(RED_LED_PORT,RED_LED_PIN);
	SetPin_GPIO(BLUE_LED_PORT,BLUE_LED_PIN);
	SetPin_GPIO(GREEN_LED_PORT,GREEN_LED_PIN);
	SetPin_GPIO(SW2_PORT,SW2_PIN);
	SetPin_GPIO(SW3_PORT,SW3_PIN);


	//Config GPIO direction as output
	RED_LED_GPIO->PDDR |= RED_LED_MASK;
	BLUE_LED_GPIO->PDDR |= BLUE_LED_MASK;
	GREEN_LED_GPIO->PDDR |= GREEN_LED_MASK;

	//Config GPIO direction as input
	SW2_GPIO->PDDR &= GPIO_FIT_REG(~(SW2_MASK));
	SW3_GPIO->PDDR &= GPIO_FIT_REG(~(SW3_MASK));

	// Config interruption
	SW2_PORT->PCR[SW2_PIN] = (SW2_PORT->PCR[SW2_PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptFallingEdge);
	SW3_PORT->PCR[SW3_PIN] = (SW3_PORT->PCR[SW3_PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptFallingEdge);

}
