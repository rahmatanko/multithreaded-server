#ifndef FILE_H
#define FILE_H

#include "common.h"
#include <sys/stat.h>  // this gives info about a file before opening it, efficient

void file_contents(int accepted, char * path);
int get_file_size(char *path, size_t *file_size);

#endif