#include "server.h"
#include <signal.h>

int main(int argc, char * argv[]) {
    // need to make sure theres 2 args first
    if (argc != 2) {
        fprintf(stderr, "how to use: %s <port>\n", argv[0]);
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

    // making sure that the os doesn't kill the server if a client disconnects unexpectedly
    signal(SIGPIPE, SIG_IGN);

    return start_server((int) port);
}