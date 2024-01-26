/*
 * OSEK.c
 *
 *  Created on: 23 sep. 2023
 *      Author: pablo
 */

#include <OSEK.h>

struct{
	uint8_t nTasks;
	uint8_t current_task;
	uint8_t next_task;
	task_t tasks[MAX_TASKS + 1];
} task_list; //Initialize all struct variables in 0

//__attribute__((always_inline)) inline static void context_switch(void)
//{
//	register uint32_t r0 asm("r0");
//	(void) r0;
//	uint8_t static fist_time_here = 0;
//
//	if(fist_time_here)
//	{
//		asm("mov r0, r7");
//		task_list.tasks[task_list.current_task].sp = (uint32_t *) r0;
//		if(1)
//		{
//			task_list.tasks[task_list.current_task].sp -= -6;
//			if(task_list.tasks[task_list.current_task].state != WAITING)
//			{
//				task_list.tasks[task_list.current_task].state = READY;
//			}
//		}
//		else
//		{
//			task_list.tasks[task_list.current_task].sp -= STACKOFFSET; //9
//		}
//	}
//	else
//	{
//		fist_time_here = 1;
//	}
//
//	task_list.current_task = task_list.next_task;
//	task_list.tasks[task_list.current_task].state = RUNNING;
//	//Call the PENDSV
////	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
//
//
//}

//static void dispatcher(void)
//{
//	task_list.next_task = task_list.nTasks; //Start in the last task
//
//	int8_t max_priority = 0;
//
//	//task_list.tasks[task_list.current_task].priority
//	for(uint8_t i = 0; i<task_list.nTasks ;i++)
//	{
//		if(task_list.tasks[i].priority >= max_priority &&
//				(task_list.tasks[i].state == RUNNING || task_list.tasks[i].state == READY))
//		{
//			max_priority = task_list.tasks[i].priority;
//
//			task_list.next_task = i;
//		}
//	}
//
//}

void config_NUMBER_OF_TASKS_DEFINED(uint8_t number_of_usr_tasks)
{
	task_list.nTasks = number_of_usr_tasks;
}

uint8_t config_task(task_t task)
{

	if (MAX_TASKS > task_list.nTasks)
	{

		if (task.autostart == kAutoStart)
		{
			task_list.tasks[task_list.nTasks].state = READY;
			task_list.tasks[task_list.nTasks].priority = task.priority;
		}
		else
		{
			task_list.tasks[task_list.nTasks].state = SUSPENDED;
			task_list.tasks[task_list.nTasks].priority = task.priority;
		}

		//Inicializa el stack pointer de la tarea apuntando al final del stack de la tarea, tomando en cuenta el stack frame inicial.
		task_list.tasks[task_list.nTasks].sp = task_list.tasks[task_list.nTasks].stack-STACK_FRAME_SIZE+STACK_SIZE-1;

		//Inicializa el stack frame inicial, con la dirección de retorno en el cuerpo de la tarea y el PSR en el valor por defecto.
		task_list.tasks[task_list.nTasks].function = task.function;
		task_list.tasks[task_list.nTasks].stack[STACK_SIZE-STACK_PSR_OFFSET-1] = (uint32_t)task.function;
		task_list.tasks[task_list.nTasks].stack[STACK_SIZE-STACK_PSR_OFFSET] = STACK_PSR_DEFAULT;


		task_list.nTasks ++;

		return (task_list.nTasks-1);
	}

	return -1; //(Invalid task).
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



void scheduler(void){

	for(uint8_t i = 0; i < MAX_TASKS;i++)
	{
		if(WAITING == task_list.tasks[i].state)
		{
			task_list.tasks[i].state = READY;
		}
	}

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

void PendSV_Handler(void)
{
	register int32_t r0 asm("r0");
	(void) r0;
//	SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;
	r0 = (int32_t) task_list.tasks[task_list.current_task].sp;
	asm("mov r7,r0");
}
