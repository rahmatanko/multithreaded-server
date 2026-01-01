#include <string.h>
#include <stdio.h>

// this parses a simple http GET request
// https://http.dev/1.0
// we need the request itself and also a buffer to write the path into
int parse_request(char * request, char * path) {
    // variables to hold the method (GET, POST) and version (1.0, 1.1, etc)
    // size is one value larger than the string itself is to make space for the null character
    char method[8], version[16];

    // a correct request would in the form 'GET /file HTTP/1.0'
    //sscanf returns the no. of successfully filled variables, so anything other than 3 is not successful
    if (sscanf(request, "%7s %255s %15s", method, path, version) != 3) return -1;

    // strcmp returns the difference between characters in strings, so if it isn't 0, it means the strings are not the same
    if (strcmp(method, "GET")) return -1;

    // strcmp returns the difference between characters in strings, so if it isn't 0, it means the strings are not the same
    if (strcmp(version, "HTTP/1.0")) return -1;

    // if we reached ehre, this was a success
    return 0;
}