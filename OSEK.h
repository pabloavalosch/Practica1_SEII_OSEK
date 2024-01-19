/*
 * OSEK.c
 *
 *  Created on: 23 sep. 2023
 *      Author: pablo
 */

#ifndef OSEK_H_
#define OSEK_H_

#include "stdint.h"
#include "config.h"


#define TOTAL_TASKS					5
#define MAX_TASKS					10
#define STACK_SIZE					100
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
	kFromNormalExec = 0,
	kFromISR,
} task_switch_type;

typedef enum
{
	kAutoStart,
	kStartSuspended
} autostart_e;

typedef struct{
	int8_t priority;
	autostart_e autostart;
	void (*function)();	  // apuntador a inicio de la tarea
	uint8_t task_id;
	uint32_t *sp;
	task_state_t state;
	uint32_t stack[STACK_SIZE];
}task_t;




void activate_task(uint8_t task_id,task_switch_type task_type);
void chain_task(uint8_t task_id,task_switch_type task_type);
void terminate_task(void);
void os_init(void);

uint8_t task_create(task_t task);

#endif /* OSEK_H_ */
