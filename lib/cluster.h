#pragma once

#include <image.h>

// Point represents a pixel within an image.
typedef struct {
    int x;
    int y;
    RGB pixel;
} Point;

// Cluster represents a group of Point instances with a
// centre and array of neighbouring points.
typedef struct {
    Point centre;
    Point *points[];
} Cluster;

// points_from_image fills points with an array of Point instances for
// each pixel of the target.
// A non-zero return value indicates failure.
int points_from_image(Image *target, Point *points_array);
