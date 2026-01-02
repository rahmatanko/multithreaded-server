#include "worker.h"

void * worker(void * arg) {
    requeue_t * q = (requeue_t *) arg;

    req_t req;

    while (1){
        // get the request from the queue
        req = dequeue(q);

        // get the header
        if (get_header(req.client, req.header)) {close(req.client); continue;}

        // get path from the header
        if (get_path(req.header, req.path)) {close(req.client); continue;}

        // get file contents
        file_contents(req.client, req.path);

        // closing the socket to avoid file descriptor leak
        close(req.client);
    }
}