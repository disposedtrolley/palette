#pragma once

#include <stdint.h>
#include <colour.h>

// Image represents an image that has been decoded into memory.
typedef struct {
    // Contiguous block of pixel data of y rows of x pixels each.
    // Each pixel consists of 8 bits * channels.
    unsigned char *data;
    int x;
    int y;
    int channels;
} Image;

// image_load loads the image found at filename into target.
// A non-zero return indicates failure.
int image_load(const char *filename, Image *target);

// image_unload frees the target Image from memory.
int image_unload(Image *target);

// pixel_get sets pixel to the RGB values found at the x and
// y coordinates of target. x and y can range from 0 to width-1
// and height-1 respectively.
// A non-zero return value indicates failure.
int pixel_get(Image *target, int x, int y, RGB *pixel);