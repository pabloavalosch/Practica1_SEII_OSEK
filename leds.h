/*
 * leds.h
 *
 *  Created on: 8 oct 2023
 *      Author: pablo
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "config.h"

#define RGB_off() ({RED_LED_GPIO->PSOR |= RED_LED_MASK; BLUE_LED_GPIO->PSOR |= BLUE_LED_MASK; GREEN_LED_GPIO->PSOR |= GREEN_LED_MASK;})
#define Green_led_on() ({RGB_off(); GREEN_LED_GPIO->PCOR |= GREEN_LED_MASK;})
#define Blue_led_on() ({RGB_off(); BLUE_LED_GPIO->PCOR |= BLUE_LED_MASK;})
#define Red_led_on() ({RGB_off(); RED_LED_GPIO->PCOR |= RED_LED_MASK;})


#endif /* LEDS_H_ */
