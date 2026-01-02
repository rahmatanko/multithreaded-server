#include "worker.h"

void * worker(void * arg) {
    // cast the argument back to our worker_t struct
    worker_t * worker = (worker_t *) arg;

    req_t req;

    while (1){
        // get the request from the queue
        req = dequeue(worker->queue);

        // log the worker who picker the request
        log_worker(worker->id, &req);

        // get the file contents
        file_contents(req.client, req.path + 1); // skipped the leading '/'

        // closing the socket to avoid file descriptor leak
        close(req.client);
    }

    return NULL;
}