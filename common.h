#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit, atoi
#include <string.h>     // memset
#include <unistd.h>     // close

// buffer size
#define SIZE 4096

// represents a single client request
typedef struct request {
    int client; // client socket
    char path[SIZE]; // the returned path
    char header[SIZE]; // the header in text
} req_t;

#endif