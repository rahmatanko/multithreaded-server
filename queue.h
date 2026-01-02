#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

typedef enum { FIFO, SFF } policy_t; // policies for benchmarking

// bounded request queue
typedef struct {
    req_t *requests;        // dynamically allocated array

    int head, tail, count; // count is the size

    int max_size;           // replaces QUEUE_SIZE

    // cond vars to keep track of when the queue is not full and when its not empty
    pthread_cond_t vacant, filled;
    // and a lock so that the queue can only be modified by 1 thread at a time
    pthread_mutex_t lock;

    policy_t policy; // checking which scheduling policy to use

} requeue_t;

// initialize the queue
void queue(requeue_t * q);

// enqueue requests (producer)
void enqueue(requeue_t * q, req_t req);

// dequeue requests (consumer)
req_t dequeue(requeue_t * q);


#endif