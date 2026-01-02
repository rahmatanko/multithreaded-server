#ifndef WORKER_H
#define WORKER_H

#include "file.h"
#include "queue.h"
#include "http.h"
#include "log.h"

// represents a single worker thread
typedef struct worker {
    int id;              // unique worker ID (used in logs)
    pthread_t thread;    // the actual pthread
    requeue_t *queue;    // pointer to the shared request queue
} worker_t;

void * worker(void * arg);

#endif 