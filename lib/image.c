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
        return EXIT_FAILURE;
    }

    target->data = img;
    target->x = x;
    target->y = y;
    target->channels = channels;

    return EXIT_SUCCESS;
}

int image_unload(Image *target) {
    stbi_image_free(target->data);
    return EXIT_SUCCESS;
}

// pointer_to_coordinate returns a pointer to the beginning of
// target's data where the x and y coordinate lies.
unsigned char* pointer_to_coordinate(Image *target, int x, int y) {
    int row_offset = (y * target->y) * target->channels;
    int col_offset = (x * target->channels);
    return target->data + (row_offset + col_offset);
}

int pixel_get(Image *target, int x, int y, RGB *pixel) {
    if (target->channels < 3) {
        fprintf(stderr, "Image has less than 3 channels\n");
        return EXIT_FAILURE;
    }

    if (x < 0 || x >= target->x) {
        fprintf(stderr, "x value %d is out of range\n", x);
        return EXIT_FAILURE;
    }

    if (y < 0 || y >= target->y) {
        fprintf(stderr, "y value %d is out of range\n", y);
        return EXIT_FAILURE;
    }

    unsigned char *pixel_start = pointer_to_coordinate(target, x, y);

    pixel->R = *pixel_start;
    pixel->G = *(pixel_start + 1);
    pixel->B = *(pixel_start + 2);

    return EXIT_SUCCESS;
}