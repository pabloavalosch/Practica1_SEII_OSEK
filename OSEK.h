/*
 * OSEK.c
 *
 *  Created on: 23 sep. 2023
 *      Author: pablo
 */

#ifndef OSEK_H_
#define OSEK_H_

#include "stdint.h"


#define MAX_TASKS					10U
#define STACK_SIZE					100U
#define STACK_FRAME_SIZE			8
#define STACK_LR_OFFSET				2
#define STACK_PSR_OFFSET			1
#define STACK_PSR_DEFAULT			0x01000000
#define STACKOFFSET 				9


typedef enum{
	READY,
	RUNNING,
	SUSPENDED,
	WAITING
}task_state_t;

typedef enum
{
	kAutoStart,
	kStartSuspended
} autostart_e;

typedef struct{
	uint8_t priority;
	autostart_e autostart;
	void (*function)();	  // apuntador a inicio de la tarea
	uint8_t task_id;
	uint32_t *sp;
	task_state_t state;
	uint32_t stack[STACK_SIZE];
}task_t;




void activate_task(uint8_t task_id);
void chain_task(uint8_t task_id);
void terminate_task(void);
void os_init(void);

uint8_t config_task(task_t task);
void config_NUMBER_OF_TASKS_DEFINED(uint8_t number_of_tasks);

#endif /* OSEK_H_ */
