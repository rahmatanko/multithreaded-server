#ifndef SERVER_H
#define SERVER_H

// we'll import all the libs here ig
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit, atoi
#include <string.h>     // memset
#include <unistd.h>     // close

// socket-specific libs
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int start_server(int port);
int accept_client(int listening);

#endif