#include <stdio.h>
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

    for (unsigned char *p = img; p != img + img_size; p += n) {
        uint8_t r = *p;
        uint8_t g = *(p + 1);
        uint8_t b = *(p + 2);

        printf("R: %d G: %d B: %d\n", r, g, b);
    }

    printf("x: %d y: %d n: %d\n", x, y, n);

    stbi_write_jpg("/Users/james/Desktop/out.jpg", x, y, n, img, 100);

    stbi_image_free(img);
    return 0;
}