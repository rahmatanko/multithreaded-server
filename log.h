#ifndef LOG_H
#define LOG_H

#include "common.h"

void log_request(req_t req);
void log_worker(int worker_id, req_t req);

#endif