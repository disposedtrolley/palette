#include <unity.h>
#include <cluster.h>
#include <image.h>
#include <stdlib.h>

const char *filename = "./_DSF0914.jpg";

void setUp(void) {}

void tearDown(void) {}

void test_points_from_image() {
    Image img = {0};

    int ret = image_load(filename, &img);
    TEST_ASSERT_EQUAL(0, ret);

    Point *points = malloc(img.x * img.y * sizeof(Point));

    ret = points_from_image(&img, points);
    TEST_ASSERT_EQUAL(0, ret);

    Point first_pixel_point = points[0];
    TEST_ASSERT_EQUAL(0, first_pixel_point.x);
    TEST_ASSERT_EQUAL(0, first_pixel_point.y);
    TEST_ASSERT_EQUAL(67, first_pixel_point.pixel.R);
    TEST_ASSERT_EQUAL(78, first_pixel_point.pixel.G);
    TEST_ASSERT_EQUAL(98, first_pixel_point.pixel.B);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_points_from_image);

    return UNITY_END();
}