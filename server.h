#ifndef SERVER_H
#define SERVER_H

#include "common.h"
#include "file.h"

// socket-specific libs
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int start_listening(int port);
int accept_client(int listening);
int start_server(int port);


#endif