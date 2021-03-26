#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <stb_image.h>

int main(void) {
    int x, y, n;
    unsigned char *data = stbi_load("/Users/james/Desktop/_DSF0914.jpg", &x, &y, &n, 0);
    if (data == NULL) {
        return 1;
    }

    printf("x: %d y: %d n: %d\n", x, y, n);

    stbi_image_free(data);

    return 0;
}