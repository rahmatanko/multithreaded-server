#include "server.h"
#include <signal.h>

int main(int argc, char * argv[]) {
    // need to make sure theres 4 args first
    if (argc != 5) {
        fprintf(stderr, "how to use: %s <port> <threads> <queue_size> <policy (fifo|sff)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // convert port to long
    char *end;
    long port = strtol(argv[1], &end, 10);
    if (*end != '\0' || port <= 0 || port > 65535) {
        fprintf(stderr, "%s: invalid port number\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // convert thread count to int
    long threads = strtol(argv[2], &end, 10);
    if (*end != '\0' || threads <= 0 || threads > 256) {
        fprintf(stderr, "%s: invalid thread count\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // convert queue size to int
    long qsize = strtol(argv[3], &end, 10);
    if (*end != '\0' || qsize <= 0 || qsize > 1024) {
        fprintf(stderr, "%s: invalid queue size\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // parse policy
    policy_t policy;
    if (strcmp(argv[4], "fifo") == 0) policy = FIFO;
    else if (strcmp(argv[4], "sff") == 0) policy = SFF;
    else {
        fprintf(stderr, "%s: invalid policy, use fifo or sff\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // making sure that the os doesn't kill the server if a client disconnects unexpectedly
    signal(SIGPIPE, SIG_IGN);

    // start the server
    return start_server((int)port, (int)threads, (int)qsize, policy);
}


