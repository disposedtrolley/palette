#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

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

double_t compand_rgb_channel(uint8_t chan) {
    double_t var_chan = chan / (double)255;
    if (var_chan > 0.04045) {
        var_chan = pow(((var_chan  + 0.055) / 1.055), 2.4);
    } else {
        var_chan = var_chan / 12.92;
    }

    return var_chan * (double)100;
}

// rgb_to_ciexyz converts the supplied RGB pixel p into the CIEXYZ structure out.
void rgb_to_ciexyz(RGB *p, CIEXYZ *out) {
    // See http://www.easyrgb.com/en/math.php
    double_t var_R = compand_rgb_channel(p->R);
    double_t var_G = compand_rgb_channel(p->G);
    double_t var_B = compand_rgb_channel(p->B);

    out->X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    out->Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    out->Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;
}

// distance returns the euclidean distance between the RGB pixels p1 and p2.
double_t distance(RGB *p1, RGB *p2) {
    uint8_t cR = p1->R - p2->R;
    uint8_t cG = p1->G - p2->G;
    uint8_t cB = p1->B - p2->B;
    uint8_t uR = p1->R + p2->R;

    return pow(
            cR*cR*(2+(double)uR/256) + cG*cG*4 + cB*cB*(2+(double)(255-uR)/256),
            (double)1/3);
}

int main(void) {
    int x, y, n;
    unsigned char *img = stbi_load("/Users/james/Desktop/_DSF0914.jpg", &x, &y, &n, 0);
    if (img == NULL) {
        return 1;
    }

//    size_t img_size = x * y * n;
    size_t img_size = n * 10;  // first 10 pixels

    for (unsigned char *img_p = img; img_p != img + img_size; img_p += n) {
        RGB p = {
                .R = *img_p,
                .G = *(img_p + 1),
                .B = *(img_p + 2),
        };

        printf("R: %d G: %d B: %d\n", p.R, p.G, p.B);
    }

    printf("x: %d y: %d n: %d\n", x, y, n);

    stbi_write_jpg("/Users/james/Desktop/out.jpg", x, y, n, img, 100);

    stbi_image_free(img);

    RGB p1 = {67, 78, 98 };
    RGB p2 = {56, 67, 87 };
    RGB p3 = {56, 67, 87 };

    printf("distance: %.2f\n", distance(&p1, &p2));
    printf("distance: %.2f\n", distance(&p2, &p3));
    return 0;
}