#include "file.h"

// now that there's a path, the file contents have to be returned
// status codes from here: https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
void file_contents(int accepted, char * path) {

    // the struct will give filesystem metadata about a path
    struct stat info;
    FILE *f;

    // if stat returns < 0 it means it failed
    // if the file is empty, or if the path is a directory, or if opening fails -> 404
    if (stat(path, &info) < 0 || S_ISDIR(info.st_mode) || !(f = fopen(path, "rb"))) {
        const char *body = "404 Not Found\n";

        perror("file open failed");

        dprintf(accepted,
                "HTTP/1.0 404 Not Found\r\n"
                "Content-Length: %zu\r\n"
                "Connection: close\r\n"
                "\r\n"
                "%s",
                strlen(body), body);

        close(accepted);
        return;
    }

    // otherwise the file was opened successfully
    size_t file_size = info.st_size;

    dprintf(accepted,
            "HTTP/1.0 200 OK\r\n"
            "Content-Length: %zu\r\n"
            "Connection: close\r\n"
            "\r\n",
            file_size);

    // now the file is streamed to the client socket
    char data[SIZE];
    size_t n;

    // read/write file contents
    while ((n = fread(data, 1, sizeof(data), f)) > 0) {
        write(accepted, data, n);
    }

    // close the file or else memory leaks happen
    fclose(f);

    // close client socket so client knows response is finished
    close(accepted);
}


// gets the size of the file
int get_file_size(char *path, size_t *file_size) {
    struct stat st;

    if (stat(path, &st) == 0) {
        if (S_ISREG(st.st_mode)) {
            // regular file, update the size
            *file_size = (size_t)st.st_size;
            return 0;  // success
        } else {
            // not a regular file (e.g., directory)
            return -1;
        }
    } else {
        // stat() failed (file doesn’t exist, permission issue, etc.)
        perror("stat failed");
        return -1;
    }
}


