#include "worker.h"

void * worker(void * arg) {
    requeue_t * q = (requeue_t *) arg;

    req_t req;

    while (1){
        // get the request from the queue
        req = dequeue(q);

        // get the header
        if (get_header(req.client, req.header)) {close(req.client); continue;}

        // attempt to get the path from the header
        if (!get_path(req.header, req.path)) {
            // get the file contents, if any
            file_contents(req.client, req.path + 1); // skipped the leading '/'
        }

        else {
            // otherwise the request is invalid
            write(req.client, "HTTP/1.0 400 Bad Request\r\n\r\n", 28);
        }

        // closing the socket to avoid file descriptor leak
        close(req.client);
    }

    return NULL;
}