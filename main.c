/*
 * @file    main.c
 * @brief   This main file is to test the OSEK example code developed by
 * 			PABLO AVALOS AND JORGE LEAUTUD.
 */

#include <GPIO.h>
#include <OSEK.h>
#include <stdio.h>
#include "leds.h"
#include "NVIC.h"
#include "USER_APP.h"



int main(void)
{

	define_Tasks();
	GPIO_init();
	os_init();


    while(1)
    {

    }
    return 0 ;
}
