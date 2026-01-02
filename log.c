#include "log.h"

// mutex to prevent multiple threads from writing to log at the same time
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

// log file path
static const char *LOG_FILE = "server.log";

// log the arrival of a new request
void log_request(req_t * req) {
    // lock mutex to prevent interleaved writes from other threads
    pthread_mutex_lock(&log_mutex);

    // open log file in append mode
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp) {
        // convert arrival timestamp to human-readable string
        struct tm *tm_info = localtime(&req->arrival);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%Y-%m-%dT%H:%M:%S", tm_info);

        // write request log: sequence ID, requested path, arrival time
        fprintf(fp, "REQUEST seq=%lu path=\"%s\" time=%s\n",
                req->ID, req->path, time_str);

        // close the file to flush changes
        fclose(fp);
    }

    // unlock mutex so other threads can log
    pthread_mutex_unlock(&log_mutex);
}

// log when a worker thread picks a request to serve
void log_worker(int worker_id, req_t * req) {
    // lock mutex to prevent interleaved writes
    pthread_mutex_lock(&log_mutex);

    // open log file in append mode
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp) {
        // write worker log: worker ID, request sequence ID, file size
        fprintf(fp, "WORKER %d picked request with seq=%lu size=%zu\n",
                worker_id, req->ID, req->file_size);

        // close the file to flush changes
        fclose(fp);
    }

    // unlock mutex so other threads can log
    pthread_mutex_unlock(&log_mutex);
}