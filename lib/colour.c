#include <colour.h>

double_t compand_rgb_channel(const uint8_t chan) {
    double_t var_chan = (double)chan / (double)255;
    if (var_chan > 0.04045) {
        var_chan = pow(((var_chan  + 0.055) / 1.055), 2.4);
    } else {
        var_chan = var_chan / 12.92;
    }

    return var_chan * (double)100;
}

void rgb_to_ciexyz(const RGB *p, CIEXYZ *out) {
    // See http://www.easyrgb.com/en/math.php
    double_t var_R = compand_rgb_channel(p->R);
    double_t var_G = compand_rgb_channel(p->G);
    double_t var_B = compand_rgb_channel(p->B);

    out->X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    out->Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    out->Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;
}

double_t normalise_xyz_channel(const double_t chan) {
    double_t normalised = chan;
    if (chan > 0.008856) {
        normalised = pow(chan, (double)1/(double)3);
    } else {
        normalised = (7.787 * chan) + ((double)16/(double)116);
    }

    return normalised;
}

const CIE_Reference D65_2_Reference = { 95.047, 100.000, 108.883 };

void ciexyz_to_cielab(const CIEXYZ *p, const CIE_Reference ref, CIELab *out) {
    // See http://www.easyrgb.com/en/math.php
    double_t var_X = p->X / ref[0];
    double_t var_Y = p->Y / ref[1];
    double_t var_Z = p->Z / ref[2];

    var_X = normalise_xyz_channel(var_X);
    var_Y = normalise_xyz_channel(var_Y);
    var_Z = normalise_xyz_channel(var_Z);

    out->L = ((double)116 * var_Y) - (double)16;
    out->a = (double)500 * (var_X - var_Y);
    out->b = (double)200 * (var_Y - var_Z);
}

double_t distance(const RGB *p1, const RGB *p2) {
    uint8_t cR = p1->R - p2->R;
    uint8_t cG = p1->G - p2->G;
    uint8_t cB = p1->B - p2->B;
    uint8_t uR = p1->R + p2->R;

    return pow(
            cR*cR*(2+(double)uR/256) + cG*cG*4 + cB*cB*(2+(double)(255-uR)/256),
            (double)1/3);
}

double delta_e_76(const CIELab *a, const CIELab *b) {
    return sqrt(
        pow(b->L - a->L, 2) +
        pow(b->a - a->a, 2) +
        pow(b->b - a->b, 2));
}
