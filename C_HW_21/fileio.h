#ifndef FILEIO_H
#define FILEIO_H

#include "album.h"

int load_from_file(const char* filename, Album arr[], int* n);
int save_to_file(const char* filename, Album arr[], int n);

#endif