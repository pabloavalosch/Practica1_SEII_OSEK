/*
 * @file    main.c
 * @brief   This main file is to test the OSEK example code developed by Pablo Avalos.
 */

#include <GPIO.h>
#include <OSEK.h>
#include "config.h"
#include <stdio.h>
#include "leds.h"
#include "NVIC.h"
#include "Queue.h"
#include "UART.h"

#define DELAY	2000000
#define CLOCK_FREQ 21000000


uint8_t g_task_A_ID;
uint8_t g_task_B_ID;
uint8_t g_task_C_ID;

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
	activate_task(g_task_B_ID,kFromNormalExec);
	Green_led_on();
	delay(DELAY);
	RGB_off();
	terminate_task();
}

void task_B_function(void){
	Red_led_on();
	delay(DELAY);
	RGB_off();
	chain_task(g_task_C_ID,kFromNormalExec);
}

void task_C_function(void){
	Blue_led_on();
	delay(DELAY);
	RGB_off();
	terminate_task();
}

int main(void)
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

	g_task_A_ID = task_create(task_A);

	g_task_B_ID = task_create(task_B);

	g_task_C_ID = task_create(task_C);

//	Queue_t myQueue;
//	Queue_Init(myQueue);
//	UART_Initialization();


	NVIC_SetPriority(PendSV_IRQn, 0xFF);
	GPIO_init();
	os_init();

    while(1)
    {

    }
    return 0 ;
}
