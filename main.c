/*
 * @file    main.c
 * @brief   This main file is to test the OSEK example code developed by Pablo Avalos.
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
	os_init();


    while(1)
    {

    }
    return 0 ;
}
