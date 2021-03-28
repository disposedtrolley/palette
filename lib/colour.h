#ifndef COLOUR_H
#define COLOUR_H

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
    double_t L;
    double_t a;
    double_t b;
} CIELab;

typedef double CIE_Reference[3];

// Illuminant D65 with 2 degree observer.
const CIE_Reference D65_2_Reference;

// rgb_to_ciexyz converts the supplied RGB pixel p into the CIEXYZ structure out.
void rgb_to_ciexyz(RGB *p, CIEXYZ *out);

// ciexyz_to_cielab converts the supplied CIEXYZ pixel p into the CIELab structure
// out, using the supplied CIE Reference ref.
void ciexyz_to_cielab(CIEXYZ *p, const CIE_Reference ref, CIELab *out);

// distance returns the euclidean distance between the RGB pixels p1 and p2.
double_t distance(RGB *p1, RGB *p2);

#endif /* COLOUR_H */