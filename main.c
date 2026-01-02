#include "server.h"
#include <signal.h>

int main(int argc, char * argv[]) {
    // need to make sure theres 3 args first
    if (argc != 4) {
        fprintf(stderr, "how to use: %s <port> <thread_count> <queue_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // if this is null it means we succesfully got a proper port number.
    char * end;

    // converts a string to a long integer
    long port = strtol(argv[1], &end, 10);

    // if the port number isnt a proper number, or if its not in the range [1, 65535] then it's invalid
    if (*end != '\0' || port <= 0 || port > 65535) {
        fprintf(stderr, "%s: invalid port number\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // converts thread count string to integer
    long thread_count = strtol(argv[2], &end, 10);
    if (*end != '\0' || thread_count <= 0 || thread_count > 1024) {
        fprintf(stderr, "%s: invalid thread count\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // converts queue size string to integer
    long queue_size = strtol(argv[3], &end, 10);
    if (*end != '\0' || queue_size <= 0 || queue_size > 65536) {
        fprintf(stderr, "%s: invalid queue size\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // making sure that the os doesn't kill the server if a client disconnects unexpectedly
    signal(SIGPIPE, SIG_IGN);

    // pass the dynamic thread count and queue size to start_server
    return start_server((int) port, (int) thread_count, (int) queue_size);
}

