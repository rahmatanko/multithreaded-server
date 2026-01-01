#include <string.h>
#include <stdio.h>

// this parses a simple http GET request
// https://http.dev/1.0
// we need the request itself and also a buffer to write the path into
int parse_request(char * request, char * path) {
    // variables to hold the method (GET, POST) and version (1.0, 1.1, etc)
    // size is one value larger than the string itself to make space for the null character
    // char method[8], version[16];

    // a correct request would in the form 'GET /file HTTP/1.0'
    // sscanf returns the no. of successfully filled variables, so anything other than 1 is not successful
    if (!sscanf(request, "GET %255s HTTP/1.0", path)) return -1;

    // if we reached here, this was a success
    return 0;
}

