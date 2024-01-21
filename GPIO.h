/*
 * GPIO.h
 *
 *  Created on: 4 oct 2023
 *      Author: pablo
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"
#include <fsl_gpio.h>
#include <fsl_port.h>

#define EnablePortClock(MASK) ({SIM->SCGC5 |= MASK;})
#define SetPin_GPIO(PORT,PIN) ({PORT->PCR[PIN] |= GPIO_MUX_MASK;})


/*! These constants are used to select an specific port in the different API functions*/
typedef enum{GPIO_A, /*!< Definition to select GPIO A */
			 GPIO_B, /*!< Definition to select GPIO B */
			 GPIO_C, /*!< Definition to select GPIO C */
			 GPIO_D, /*!< Definition to select GPIO D */
			 GPIO_E, /*!< Definition to select GPIO E */
			 GPIO_F  /*!< Definition to select GPIO F */
} gpio_name_t;


void GPIO_init(void);

#endif /* GPIO_H_ */
