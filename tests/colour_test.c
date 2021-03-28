#include <unity.h>
#include <colour.h>

void setUp(void) {}

void tearDown(void) {}

void test_rgb_to_ciexyz() {
    RGB p = { 76, 39, 230 };
    CIEXYZ xyz = {};
    rgb_to_ciexyz(&p, &xyz);

    TEST_ASSERT_EQUAL_DOUBLE(17.988937960048638, xyz.X);
    TEST_ASSERT_EQUAL_DOUBLE(8.700708704519439, xyz.Y);
    TEST_ASSERT_EQUAL_DOUBLE(75.59419357206868, xyz.Z);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_rgb_to_ciexyz);

    return UNITY_END();
}