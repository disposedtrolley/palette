#include "image.h"

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

int image_load(const char *filename, Image *target) {
    int x, y, channels;
    unsigned char *img = stbi_load(filename, &x, &y, &channels,0);
    if (img == NULL) {
        fprintf(stderr, "Error loading image file at %s: %s\n", filename, stbi_failure_reason());
        return 1;
    }

    target->data = img;
    target->x = x;
    target->y = y;
    target->channels = channels;

    return 0;
}

int image_unload(Image *target) {
    stbi_image_free(target->data);
    return 0;
}