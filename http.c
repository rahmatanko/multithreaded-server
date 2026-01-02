#include "http.h"

// this parses a simple http GET request and gives the path
// https://http.dev/1.0
// we need the header itself and also a buffer to write the path into
int get_path(char * header, char * path) {
    // variables to hold the method (GET, POST) and version (1.0, 1.1, etc)
    // size is one value larger than the string itself to make space for the null character
    // char method[8], version[16];

    // a correct header would in the form 'GET /file HTTP/1.0'
    // sscanf returns the no. of successfully filled variables, so anything other than 1 is not successful
    if (!sscanf(header, "GET %255s HTTP/1.0", path)) return -1;

    // if we reached here, this was a success
    return 0;
}

// this gets the header from the client file descriptor
int get_header(int accepted, char * header) {

    // http headers can arrive in multiple packets and may be longer than our buffer size but we're assuming otherwise for this implementation
    // read like fread returns size but it can also return a negative value if its an error
    // which is why ssize_t is used not size_t
    ssize_t n = read(accepted, header, SIZE);

    // if the the request is empty or an error occurred
    if (n <= 0) {
        perror("header acquisition error");
        return -1;
    }
    
    // since read doesn't automatically add a null char like some other string funcs do, it must be added or else there will be overflow
    header[n] = '\0';
    return 0;
}

