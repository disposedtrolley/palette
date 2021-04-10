#pragma once

#include<stdint.h>

typedef struct {
    unsigned char *data;
    int x;
    int y;
    int z;
} Image;

// load loads the image found at filename into target.
// A non-zero return indicates failure.
int load(const char *filename, Image *target);