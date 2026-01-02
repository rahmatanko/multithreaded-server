#ifndef HTTP_H
#define HTTP_H

#include "file.h"

int get_header(int accepted, char * header);
int get_path(char * request, char * path);

#endif