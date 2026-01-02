#include "queue.h"

// initialize the queue
void queue(requeue_t * q) {
    // queue starts out as empty
    q->count = 0; q->head = 0; q->tail = 0;

    // initialize the other variables
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->vacant, NULL);
    pthread_cond_init(&q->filled, NULL);
}

// enqueue requests (producer)
void enqueue(requeue_t * q, req_t req){
    // let's make sure this thread is the only one modifying the queue right now
    pthread_mutex_lock(&(q->lock));

    // we have to make sure the thread actually has somethign to do i.e. the queue isn't full
    // otherwise the thread will just be using up cpu power
    while (q->count == QUEUE_SIZE) {
        // cond_wait just puts the thread to sleep. and keeps track of it through the cond variable vacant
        // we have to use a while loop instead of a simple if because threads sometimes wake up randomly, and we must make sure they don't progress
        pthread_cond_wait(&(q->vacant), &(q->lock));
    }

    // now we can safely add the request to the queue
    // queues use FIFO, first in first out which means the request is added to the butt of the data structure
    q->count++;
    q->requests[q->tail] = req;
    // we use wrapping so that memory is not wasted
    q->tail = (q->tail + 1) % QUEUE_SIZE;

    // signal that the queue isn't empty
    pthread_cond_signal(&(q->filled));
    // release the lock now that the thread is done
    pthread_mutex_unlock(&(q->lock));
}

// dequeue requests (worker)
req_t dequeue(requeue_t * q) {
    // let's make sure this thread is the only one modifying the queue right now
    pthread_mutex_lock(&(q->lock));

    // again we must make sure the thread actually has a request to dequeue or else it will be consuminng power for nothing
    while (q->count == 0) pthread_cond_wait(&(q->filled), &(q->lock));

    // queues use FIFO, so the request will be plucked from the head
    q->count--;

    // get the request
    req_t req = q->requests[q->head];

    // we use wrapping so that memory is not wasted
    q->head = (q->head + 1) % QUEUE_SIZE;

    // signal that the queue isn't full
    pthread_cond_signal(&(q->vacant));
    // release the lock now that the thread is done
    pthread_mutex_unlock(&(q->lock));

    return req;
}