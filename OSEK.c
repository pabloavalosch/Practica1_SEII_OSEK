/*
 * OSEK.c
 *
 *  Created on: 23 sep. 2023
 *      Author: PABLO AVALOS AND JORGE LEAUTAUD.
 */

#include <OSEK.h>


#define ADJUST_ADDRESS (-1 + 4)

uint32_t g_src = 0; //global address of each task
uint32_t g_return_addr  = 0; //variable to store the return address on link register

struct{
	uint8_t nTasks;
	uint8_t current_task;
	uint8_t next_task;
	task_t tasks[MAX_TASKS + 1];
} task_list; //Initialize all struct variables in 0


void config_NUMBER_OF_TASKS_DEFINED(uint8_t number_of_usr_tasks)
{
	task_list.nTasks = number_of_usr_tasks;
}

uint8_t config_task(task_t task)
{
	static uint8_t i = 0; // Variable to count each time a task is configured

	if (MAX_TASKS > task_list.nTasks)
	{
		i++;
		if (kAutoStart == task.autostart)
		{
			task_list.tasks[i].autostart = kAutoStart;
			task_list.tasks[i].state = READY;
			task_list.tasks[i].priority = task.priority;

		}
		else
		{
			task_list.tasks[i].autostart = kStartSuspended;
			task_list.tasks[i].state = SUSPENDED;
			task_list.tasks[i].priority = task.priority;
		}


		task_list.tasks[i].function = (uint32_t)task.function;

		return kStatusSuccess;
	}

	return kStatusError; //(Invalid task).
}

void activate_task(uint8_t task_id){ //TODO: Return ID task in function



	asm(	"LDR R0, =g_return_addr");
	asm(	"MOV R1, LR"	);
	asm(	"SUB R1, R1, #1");
	asm(	"STR R1, [R0]");


	task_list.tasks[task_list.next_task].return_addr = g_return_addr;
	task_list.tasks[task_list.next_task].state = READY; //task which called this function change from running to ready
	task_list.tasks[task_id].state = READY;
	scheduler();
}


void chain_task(uint8_t task_id){
	// termina la tarea actual y ejecuta otra tarea

	task_list.tasks[task_list.next_task].state = SUSPENDED;
	task_list.tasks[task_id].state = READY;
	scheduler();
}


void terminate_task(void){
	task_list.tasks[task_list.next_task].state = SUSPENDED;
	scheduler();
}



void scheduler(void)
{

	uint8_t max_priority = 0;

	for(uint8_t i = 0; i <= task_list.nTasks ;i++)
	{
		if(task_list.tasks[i].priority >= max_priority &&
				 task_list.tasks[i].state == READY)
		{
			max_priority = task_list.tasks[i].priority;

			task_list.next_task = i;
		}
	}

	if( 0 != task_list.next_task)
	{
		task_list.tasks[task_list.next_task].state = RUNNING;

		if(0 != task_list.tasks[task_list.next_task].return_addr)
		{

			g_src = (uint32_t)(task_list.tasks[task_list.next_task].return_addr);

		}
		else
		{
			g_src = (uint32_t)(task_list.tasks[task_list.next_task].function + ADJUST_ADDRESS);
		}

		asm(	"LDR R0, =g_src");
		asm(	"LDR R1, [R0]"	);
		asm(	"MOV PC, R1"	);
	}

	else
	{
		while(1);
	}
}

void os_init(void){

	task_list.next_task = 0;
	task_list.current_task = 0;


	scheduler();


}
