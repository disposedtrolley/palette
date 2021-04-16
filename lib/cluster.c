#include "cluster.h"
#include <stdlib.h>

 int points_from_image(Image *target, Point *points_array, size_t *len) {
    for (int x = 0; x < target->x; x+=1) {
        for (int y = 0; y < target->y; y+=1) {
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

            points_array[x + y] = p;
        }
    }

    *len = (target->x * target->y);

    return EXIT_SUCCESS;
}