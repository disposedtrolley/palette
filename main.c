#include <stdio.h>
#include <stdlib.h>
#include <colour.h>
#include <image.h>

int main(void) {
    Image img;
    int ret = image_load("/Users/james/Desktop/_DSF0914.jpg", &img);
    printf("ret: %d\n", ret);
    if (ret == 0) {
        printf("x: %d y: %d channels: %d\n", img.x, img.y, img.channels);
    }

    image_unload(&img);


//    for (unsigned char *img_p = img; img_p != img + img_size; img_p += n) {
//        RGB p = {
//                .R = *img_p,
//                .G = *(img_p + 1),
//                .B = *(img_p + 2),
//        };
//
//        printf("R: %d G: %d B: %d\n", p.R, p.G, p.B);
//    }
//
//    printf("x: %d y: %d n: %d\n", x, y, n);
//
//    stbi_write_jpg("/Users/james/Desktop/out.jpg", x, y, n, img, 100);
//
//    stbi_image_free(img);
//
//    RGB p1 = {67, 78, 98 };
//    RGB p2 = {56, 67, 87 };
//    RGB p3 = {56, 67, 87 };
//
//    printf("distance: %.2f\n", distance(&p1, &p2));
//    printf("distance: %.2f\n", distance(&p2, &p3));
    return EXIT_SUCCESS;
}