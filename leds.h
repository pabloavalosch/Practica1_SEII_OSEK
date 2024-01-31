/*
 * leds.h
 *
 *  Created on: 8 oct 2023
 *      Author: PABLO AVALOS AND JORGE LEAUTAUD.
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "GPIO.h"

//GPIO
#define RED_LED_GPIO			(GPIOB)
#define BLUE_LED_GPIO			(GPIOB)
#define GREEN_LED_GPIO			(GPIOE)

//PORTS
#define RED_LED_PORT			(PORTB)
#define BLUE_LED_PORT			(PORTB)
#define GREEN_LED_PORT			(PORTE)

//PIN
#define RED_LED_PIN				(22u)
#define BLUE_LED_PIN			(21u)
#define GREEN_LED_PIN			(26u)

// MASKS
#define RED_LED_MASK			(1 << RED_LED_PIN)
#define BLUE_LED_MASK			(1 << BLUE_LED_PIN)
#define GREEN_LED_MASK			(1 << GREEN_LED_PIN)
#define GPIO_MUX_MASK			(1 << 8)

#define RGB_off() ({RED_LED_GPIO->PSOR |= RED_LED_MASK; BLUE_LED_GPIO->PSOR |= BLUE_LED_MASK; GREEN_LED_GPIO->PSOR |= GREEN_LED_MASK;})
#define Green_led_on() ({RGB_off(); GREEN_LED_GPIO->PCOR |= GREEN_LED_MASK;})
#define Blue_led_on() ({RGB_off(); BLUE_LED_GPIO->PCOR |= BLUE_LED_MASK;})
#define Red_led_on() ({RGB_off(); RED_LED_GPIO->PCOR |= RED_LED_MASK;})


#endif /* LEDS_H_ */
