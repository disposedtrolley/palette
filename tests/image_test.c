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

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_image_load);

    return UNITY_END();
}