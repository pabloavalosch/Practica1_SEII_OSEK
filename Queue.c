/*
 * Queue.c
 *
 *  Created on: 26 sep. 2023
 *      Author: pablo
 */

#include "Queue.h"

uint8_t Queue_Init(Queue_t myQueue)
{
    myQueue.front = 0;
    myQueue.rear = 0;

    return TRUE;
}

uint8_t Queue_Enqueue(Queue_t * myQueue, uint8_t * pStr)
{
    if( QUEUE_SIZE <= myQueue->rear )
    {
        // Not enough space in the queue
        return FALSE;
    }

    // Enqueue the string into the queue of pointers
    myQueue->queue[myQueue->rear++] = pStr;

    if( QUEUE_SIZE == myQueue->rear)
    {
    	myQueue->rear--;
    }
    return TRUE;
}

uint8_t Queue_Dequeue(Queue_t * myQueue, uint8_t * pStr)
{
	if( 0 == myQueue->count )
	{
		// Queue is empty, nothing to Dequeue
		return FALSE;
	}

	// Dequeue the string from the queue of pointers
	myQueue->queue[myQueue->front] = 0;
	myQueue->count--;

	return TRUE;
}

uint8_t Queue_is_empty(Queue_t* myQueue)
{
	return (myQueue->count);
}

Queue_t get_myQueue(Queue_t myQueue)
{
	return (myQueue);
}
