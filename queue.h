#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

#define POOL_SIZE 6 // pcs and laptops nowdays have 4-8 cores usually so 6 sits nicely in the middle
#define QUEUE_SIZE 16 // the producer can add upto 16 requests at a time to the queue

// bounded request queue
typedef struct {
    req_t requests[QUEUE_SIZE]; // the queue itself

    int head, tail, count; // count is the size

    // cond vars to keep track of when the queue is not full and when its not empty
    pthread_cond_t vacant, filled;
    // and a lock so that the queue can only be modified by 1 thread at a time
    pthread_mutex_t lock;
} requeue_t;

// initialize the queue
void queue(requeue_t * q);

// enqueue requests (producer)
void enqueue(requeue_t * q, req_t req);

// dequeue requests (consumer)
req_t dequeue(requeue_t * q);


#endif