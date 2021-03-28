#pragma once

#include <stdint.h>
#include <math.h>

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB;

typedef struct {
    double_t X;
    double_t Y;
    double_t Z;
} CIEXYZ;

typedef struct {
    uint8_t L;
    int8_t a;
    int8_t b;
} CIELab;

// rgb_to_ciexyz converts the supplied RGB pixel p into the CIEXYZ structure out.
void rgb_to_ciexyz(RGB *p, CIEXYZ *out);

// distance returns the euclidean distance between the RGB pixels p1 and p2.
double_t distance(RGB *p1, RGB *p2);
