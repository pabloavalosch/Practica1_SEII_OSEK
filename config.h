/*
 * config.h
 *
 * 		\brief
 *  	Created on: 13 oct 2023
 *  Author: pablo
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "fsl_gpio.h"
#include "fsl_port.h"

//GPIO
#define RED_LED_GPIO			(GPIOB)
#define BLUE_LED_GPIO			(GPIOB)
#define GREEN_LED_GPIO			(GPIOE)
#define SW2_GPIO				(GPIOC)
#define SW3_GPIO				(GPIOA)

//PORTS
#define RED_LED_PORT			(PORTB)
#define BLUE_LED_PORT			(PORTB)
#define GREEN_LED_PORT			(PORTE)
#define SW2_PORT				(PORTC)
#define SW3_PORT				(PORTA)

//PIN
#define RED_LED_PIN				(22u)
#define BLUE_LED_PIN			(21u)
#define GREEN_LED_PIN			(26u)
#define	SW2_PIN					(6u)
#define	SW3_PIN					(4u)

// MASKS
#define RED_LED_MASK			(1 << RED_LED_PIN)
#define BLUE_LED_MASK			(1 << BLUE_LED_PIN)
#define GREEN_LED_MASK			(1 << GREEN_LED_PIN)
#define SW2_MASK				(1 << SW2_PIN)
#define SW3_MASK				(1 << SW3_PIN)
#define GPIO_MUX_MASK			(1 << 8)


#endif /* CONFIG_H_ */
