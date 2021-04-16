#include "image.h"

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>
#define STBI_FAILURE_USERMSG

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

int image_downsize(const Image *target, Image *resized) {
    const int rw = target->x / DOWNSIZED_IMAGE_MIN_DIMENSION;
    const int rh = target->y / DOWNSIZED_IMAGE_MIN_DIMENSION;
    const int ratio = rw < rh ? rw : rh;

    resized->x = target->x / ratio;
    resized->y = target->y / ratio;
    resized->channels = target->channels;
    resized->data = malloc(resized->x * resized->y * resized->channels);

    const int ret = stbir_resize_uint8(
            target->data, target->x, target->y,0,
            resized->data, resized->x, resized->y,0,
            resized->channels);
    if (ret != EXIT_SUCCESS) {
        fprintf(stderr, "Error rezising image: %s\n", stbi_failure_reason());
    }

    return EXIT_SUCCESS;
}

// pointer_to_coordinate returns a pointer to the beginning of
// target's data where the x and y coordinate lies.
unsigned char* pointer_to_coordinate(const Image *target, int x, int y) {
    int row_offset = (y * target->y) * target->channels;
    int col_offset = (x * target->channels);
    return target->data + (row_offset + col_offset);
}

int pixel_get(const Image *target, int x, int y, RGB *pixel) {
    assert(("Image should have at least 3 channels", target->channels >= 3));
    assert(("0 <= x < target.width", x >= 0 && x < target->x));
    assert(("0 <= y < target.height", y >= 0 && y < target->y));

    unsigned char *pixel_start = pointer_to_coordinate(target, x, y);

    pixel->R = *pixel_start;
    pixel->G = *(pixel_start + 1);
    pixel->B = *(pixel_start + 2);

    return EXIT_SUCCESS;
}