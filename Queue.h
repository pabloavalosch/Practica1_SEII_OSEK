/*
 * Queue.h
 *
 *  Created on: 26 sep. 2023
 *      Author: pablo
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

#define QUEUE_SIZE		16U

enum {FALSE, TRUE};

typedef struct {
    uint8_t *queue[QUEUE_SIZE];
    uint8_t front;
    uint8_t rear;
    uint8_t count;
} Queue_t;

uint8_t Queue_Init(Queue_t myQueue);
uint8_t Queue_Enqueue(Queue_t * myQueue, uint8_t * pStr);
uint8_t Queue_Dequeue(Queue_t * myQueue, uint8_t * pStr);
uint8_t Queue_is_empty(Queue_t * myQueue);
Queue_t get_myQueue(Queue_t myQueue);

#endif /* QUEUE_H_ */
