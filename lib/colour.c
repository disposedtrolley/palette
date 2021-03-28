#include <colour.h>

double_t compand_rgb_channel(uint8_t chan) {
    double_t var_chan = chan / (double)255;
    if (var_chan > 0.04045) {
        var_chan = pow(((var_chan  + 0.055) / 1.055), 2.4);
    } else {
        var_chan = var_chan / 12.92;
    }

    return var_chan * (double)100;
}

void rgb_to_ciexyz(RGB *p, CIEXYZ *out) {
    // See http://www.easyrgb.com/en/math.php
    double_t var_R = compand_rgb_channel(p->R);
    double_t var_G = compand_rgb_channel(p->G);
    double_t var_B = compand_rgb_channel(p->B);

    out->X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    out->Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    out->Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;
}

double_t distance(RGB *p1, RGB *p2) {
    uint8_t cR = p1->R - p2->R;
    uint8_t cG = p1->G - p2->G;
    uint8_t cB = p1->B - p2->B;
    uint8_t uR = p1->R + p2->R;

    return pow(
            cR*cR*(2+(double)uR/256) + cG*cG*4 + cB*cB*(2+(double)(255-uR)/256),
            (double)1/3);
}