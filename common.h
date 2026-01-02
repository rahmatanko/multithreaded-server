#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit, atoi
#include <string.h>     // memset
#include <unistd.h>     // close
#include <time.h>   // for time(), time_t
#include <pthread.h>

// buffer size
#define SIZE 4096

// represents a single client request
typedef struct request {
    int client; // client socket
    char path[SIZE]; // the returned path
    char header[SIZE]; // the header in text
    time_t arrival; // arrival time
    size_t ID;
    size_t file_size;
} req_t;

#endif