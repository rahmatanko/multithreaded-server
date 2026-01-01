#include "file.h"

// now that there's a path, the file contents have to be returned
// status codes from here: https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
void file_contents(int accepted, char * path) {

    // the struct will give filesystem metadata about a path
    struct stat info; FILE *f;

    // if stat returns 0  it means it now has file info
    // we open the file in binary mode instead of the regular way to be mindful of all filetypes, curroption is a risk if the file isnt txt otherwise
    // if the file is empty, then our response is 404, or if the file is actually a directory then its an error as well
    // otherwise if there's another problem in opening the file then the error is the same
    if (stat(path, &info) < 0 || S_ISDIR(info.st_mode) || !(f = fopen(path, "rb"))) {
        perror("file open failed");
        write(accepted, "HTTP/1.0 404 Not Found\r\n\r\n", 26);
    }

    else {
        // otherwise the file was opened successfully
        write(accepted, "HTTP/1.0 200 OK\r\n\r\n", 19);

        // now the file is streamed to the client socket
        char data[SIZE];
        // used size_t because it always matches memory size which is convenient
        size_t n;

        // we read/write a chunk of data once, for as long as there is data to read/write
        while ((n = fread(data, 1, sizeof(data), f)) > 0) {
            write(accepted, data, n);
        }

        // close the file or else memory leaks happen
        fclose(f);
    }
}


