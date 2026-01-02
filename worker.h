#ifndef WORKER_H
#define WORKER_H

#include "file.h"
#include "queue.h"
#include "http.h"

void * worker(requeue_t * q);

#endif 