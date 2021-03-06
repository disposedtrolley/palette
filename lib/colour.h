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
    double_t L;
    double_t a;
    double_t b;
} CIELab;

typedef double CIE_Reference[3];

// Illuminant D65 with 2 degree observer.
const CIE_Reference D65_2_Reference;

// rgb_to_ciexyz converts the supplied RGB pixel p into the CIEXYZ structure out.
void rgb_to_ciexyz(const RGB *p, CIEXYZ *out);

// ciexyz_to_cielab converts the supplied CIEXYZ pixel p into the CIELab structure
// out, using the supplied CIE Reference ref.
void ciexyz_to_cielab(const CIEXYZ *p, const CIE_Reference ref, CIELab *out);

// distance returns the euclidean distance between the RGB pixels p1 and p2.
double_t distance(const RGB *p1, const RGB *p2);

// delta_e_76 returns the Delta E 76 difference value between the CIELab
// colours a and b.
double delta_e_76(const CIELab *a, const CIELab *b);