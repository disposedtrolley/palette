#include "image.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int load(const char *filename, Image *target) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening image file at %s: %s\n", filename, strerror(errno));
        return 1;
    }

    int x, y, z;
    unsigned char *img = stbi_load(filename, &x, &y, &z,0);
    if (img == NULL) {
        fprintf(stderr, "Error loading image file at %s\n", filename);
        return 1;
    }

    *target->data = *img;
    target->x = x;
    target->y = y;
    target->z = z;

    stbi_image_free(img);
    fclose(fp);

    return 0;
}