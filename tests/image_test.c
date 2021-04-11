#include <unity.h>
#include <image.h>

const char *filename = "./_DSF0914.jpg";

void setUp(void) {}

void tearDown(void) {}

void test_image_load() {
    Image img = {0};

    int ret = image_load(filename, &img);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(3, img.channels);
    TEST_ASSERT_EQUAL(5977, img.x);
    TEST_ASSERT_EQUAL(3985, img.y);
}

void test_image_unload() {
    Image img = {0};

    int ret = image_load(filename, &img);
    TEST_ASSERT_EQUAL(0, ret);

    image_unload(&img);

    // No assertions here. Just making sure we exercise this function so we can
    // catch any exceptions.
}

void test_pixel_get() {
    Image img = {0};

    int ret = image_load(filename, &img);
    TEST_ASSERT_EQUAL(0, ret);

    RGB pixel = {0};
    ret = pixel_get(&img, 0, 0, &pixel);
    TEST_ASSERT_EQUAL(0, ret);

    TEST_ASSERT_EQUAL(67, pixel.R);
    TEST_ASSERT_EQUAL(78, pixel.G);
    TEST_ASSERT_EQUAL(98, pixel.B);

    ret = pixel_get(&img, 5976, 3984, &pixel);
    TEST_ASSERT_EQUAL(0, ret);

    TEST_ASSERT_EQUAL(35, pixel.R);
    TEST_ASSERT_EQUAL(43, pixel.G);
    TEST_ASSERT_EQUAL(56, pixel.B);

    ret = pixel_get(&img, -1, -1, &pixel);
    TEST_ASSERT_EQUAL(1, ret);

    ret = pixel_get(&img, 10000, 10000, &pixel);
    TEST_ASSERT_EQUAL(1, ret);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_image_load);
    RUN_TEST(test_image_unload);
    RUN_TEST(test_pixel_get);

    return UNITY_END();
}