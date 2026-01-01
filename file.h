#ifndef FILE_H
#define FILE_H

#include "common.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/stat.h>  // this gives info about a file before opening it, efficient

void file_contents(int accepted, char * path);

#endif