#include "cluster.h"
#include <stdlib.h>

 int points_from_image(const Image *target, Point *points_array, size_t *len) {
    size_t i = 0;
    for (int x = 0; x < target->x; x++) {
        for (int y = 0; y < target->y; y++) {
            RGB pixel = {0};
            int ret = pixel_get(target, x, y, &pixel);
            if (ret != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }

            Point p = {
                    .x = x,
                    .y = y,
                    .pixel = pixel,
            };

            points_array[i] = p;
            i++;
        }
    }

    *len = (target->x * target->y);

    return EXIT_SUCCESS;
}