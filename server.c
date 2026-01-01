#include "server.h"

int start_server(int port) {
    // create a struct that holds info about for the socket
    // can't use the original sockaddr struct because it is very generic
    struct sockaddr_in saddress;

    // our listening (server) socket which uses ipv4 and TCP
    // if socket creation is successful then a valid file descriptor is returned which is >=0
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE); // fatal error
    }

    // when a TCP socket closes the OS keeps it waiting for several minutes, which is a long time
    // and in this time we can't open a socket with an identical address it will surely lead to a binding error,
    // so because of that, we set the option of resuing the socket address to 1
    //https://pubs.opengroup.org/onlinepubs/009695099/functions/setsockopt.html
    int on = 1;
    setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    memset(&saddress, 0, sizeof(saddress)); // need to make sure all the unused fields are 0's otherwise they'd be garbage values which would lead to undefined behavior

    saddress.sin_family = AF_INET; // ip address is ipv4
    saddress.sin_port = htons(port); // the port is converted into network bytes but short (2 bytes)
    saddress.sin_addr.s_addr = htonl(INADDR_ANY); // the macro means we'll listen on any available network interface, then thats converted to 4 network bytes.

    if (bind(listening, (struct sockaddr *)&saddress, sizeof(saddress)) < 0) { // binding the socket to address, 0 is successful, -1 is failure
        perror("binding failed");
        exit(EXIT_FAILURE); // fatal error
    }

    // now our socket is in listening mode and we're allowing for the max number of connections (4096 in linux) to be in the queue
    // again, 0 here means success, -1 is failure
    if (listen(listening, SOMAXCONN) < 0) {
        perror("listening failed");
        exit(EXIT_FAILURE); // fatal error
    }

    //server is listening right now
    printf("server is listening on port %d\n", port);

    return listening;
}

int accept_client(int listening) {
    // we're accepting one incoming client connection from listening server socket
    struct sockaddr_in caddress;
    // we want to know the length of the address
    socklen_t length = sizeof(caddress);

    // this gives us our client socket and it fills up the client address and the length of said address
    int accepted = accept(listening, (struct sockaddr *)&caddress, &length);

    if (accepted < 0) {
        perror("accept failed");
        // we just skip this client instead of killing the entire server (i.e. exiting)
        // we exited before because the previous errors meant the server fundamentally didn't work
        return -1;
    }

    return accepted;
}