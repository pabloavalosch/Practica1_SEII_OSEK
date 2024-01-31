/*
 * USER_APP.c
 *
 *  Created on: 19 ene. 2024
 *      Author: PABLO AVALOS AND JORGE LEAUTAUD.
 */

#include "leds.h"
#include "OSEK.h"


#define DELAY	2000000
#define CLOCK_FREQ 21000000

#define NUMBER_OF_USR_TASKS 	3U

enum
{
	g_task_A_ID = 1,
	g_task_B_ID,
	g_task_C_ID
};

uint8_t strTask1[] = {"Task 1 creation failed\r\n"};
uint8_t strTask2[] = {"Task 2 creation failed\r\n"};
uint8_t strTask3[] = {"Task 3 creation failed\r\n"};

void delay(uint32_t delay){
	volatile uint32_t i = 0;

	while(i < DELAY){
		i++;
	}
}

void task_A_function(void){
	Green_led_on();
	delay(DELAY);
	activate_task(g_task_B_ID);
	Green_led_on();
	delay(DELAY);
	RGB_off();
	terminate_task();
}

void task_B_function(void){
	Red_led_on();
	delay(DELAY);
	RGB_off();
	chain_task(g_task_C_ID);
}

void task_C_function(void){
	Blue_led_on();
	delay(DELAY);
	RGB_off();
	terminate_task();
}

void define_Tasks(void)
{

	task_t task_A = {
			.autostart = kAutoStart,
			.priority = 1,
			.function = task_A_function,
	};

	task_t task_B = {
			.autostart = kStartSuspended,
			.priority = 2,
			.function = task_B_function,
	};

	task_t task_C = {
			.autostart = kStartSuspended,
			.priority = 3,
			.function = task_C_function,
	};

	config_NUMBER_OF_TASKS_DEFINED( NUMBER_OF_USR_TASKS );
	config_task(task_A);
	config_task(task_B);
	config_task(task_C);

}
