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

void test_ciexyz_to_cielab() {
    CIEXYZ xyz = {17.988937960048638, 8.700708704519439, 75.59419357206868};
    CIELab out = {};
    ciexyz_to_cielab(&xyz, D65_2_Reference, &out);

    TEST_ASSERT_EQUAL_DOUBLE(35.40154806418358, out.L);
    TEST_ASSERT_EQUAL_DOUBLE(65.51462077077721, out.a);
    TEST_ASSERT_EQUAL_DOUBLE(-88.4715662266948, out.b);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_rgb_to_ciexyz);
    RUN_TEST(test_ciexyz_to_cielab);

    return UNITY_END();
}