#include "worker.h"

void * worker(requeue_t * q) {
    req_t req;

    while (1){
        // get the request from the queue
        req = dequeue(q);

        // parse request
        if (!parse_request(req.client, req.path)) continue;

        // get file contents
        file_contents(req.client, req.path);
    }
}