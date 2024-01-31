/*
 * OSEK.c
 *
 *  Created on: 23 sep. 2023
 *      Author: PABLO AVALOS AND JORGE LEAUTUD.
 */

#include <OSEK.h>

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
			task_list.tasks[i].state = READY;
			task_list.tasks[i].priority = task.priority;

		}
		else
		{
			task_list.tasks[i].state = SUSPENDED;
			task_list.tasks[i].priority = task.priority;
		}

		//Inicializa el stack pointer de la tarea apuntando al final del stack de la tarea, tomando en cuenta el stack frame inicial.
		task_list.tasks[i].sp = task_list.tasks[i].stack-STACK_FRAME_SIZE+STACK_SIZE-1;
		task_list.tasks[i].function = (uint32_t)task.function;

		return kStatusSuccess;
	}

	return kStatusError; //(Invalid task).
}

void activate_task(uint8_t task_id){ //TODO: Return ID task in function
	// pone la tarea en ready

	task_list.tasks[task_id].state = READY;
}


void chain_task(uint8_t task_id){
	// termina la tarea actual y ejecuta otra tarea

	task_list.tasks[task_list.current_task].state = SUSPENDED;
	task_list.tasks[task_id].state = READY;
}


void terminate_task(void){
	task_list.tasks[task_list.current_task].state = SUSPENDED;
}



void scheduler(void)
{
	static uint32_t * src;

	uint8_t max_priority = 0;

	for(uint8_t i = 0; i < task_list.nTasks ;i++)
	{
		if(task_list.tasks[i].priority >= max_priority &&
				(task_list.tasks[i].state == RUNNING || task_list.tasks[i].state == READY))
		{
			max_priority = task_list.tasks[i].priority;

			task_list.next_task = i;
		}
	}



	task_list.current_task = task_list.next_task;
	task_list.tasks[task_list.current_task].state = RUNNING;

	src = task_list.tasks[task_list.current_task].sp;

	asm(	"MOV R0, SP"	);
	asm(	"MOV R1, PC"	);
	asm(	"LDR R0, [R1]"	);

}
static void idle_function(void)
{
	while(1);
}

void os_init(void){

	task_list.next_task = 1;
	task_list.current_task = 0;

	task_t idle_task = {
				.autostart = kAutoStart,
				.priority = 0,
				.function = idle_function,
		};

	config_task(idle_task);

	scheduler();


}
