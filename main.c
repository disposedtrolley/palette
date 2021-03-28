#include <colour.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

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