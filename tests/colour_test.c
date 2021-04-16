#include <unity.h>
#include <colour.h>

void setUp(void) {}

void tearDown(void) {}

void test_rgb_to_ciexyz() {
    typedef struct {
        char *name;
        RGB input_rgb;
        CIEXYZ expected_ciexyz;
    } testcase;

    testcase tests[] = {
            {
                .name = "when an RGB pixel is converted to CIEXYZ",
                .input_rgb = (RGB){76, 39, 230},
                .expected_ciexyz = (CIEXYZ){17.988937960048638, 8.700708704519439, 75.59419357206868},
            },
            {
                .name = "when a black RGB pixel is converted to CIEXYZ",
                .input_rgb = (RGB){0, 0, 0},
                .expected_ciexyz = (CIEXYZ){0, 0, 0},
            },
            {
                .name = "when a white RGB pixel is converted to CIEXYZ",
                .input_rgb = (RGB){255, 255, 255},
                .expected_ciexyz = (CIEXYZ){95.05, 100, 108.89999999999999},
            }
    };

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        testcase tc = tests[i];

        TEST_MESSAGE(tc.name);

        CIEXYZ actual = {0};
        rgb_to_ciexyz(&tc.input_rgb, &actual);

        TEST_ASSERT_EQUAL_DOUBLE(tc.expected_ciexyz.X, actual.X);
        TEST_ASSERT_EQUAL_DOUBLE(tc.expected_ciexyz.Y, actual.Y);
        TEST_ASSERT_EQUAL_DOUBLE(tc.expected_ciexyz.Z, actual.Z);
    }
}

void test_ciexyz_to_cielab() {
    CIEXYZ xyz = {17.988937960048638, 8.700708704519439, 75.59419357206868};
    CIELab out = {};
    ciexyz_to_cielab(&xyz, D65_2_Reference, &out);

    TEST_ASSERT_EQUAL_DOUBLE(35.40154806418358, out.L);
    TEST_ASSERT_EQUAL_DOUBLE(65.51462077077721, out.a);
    TEST_ASSERT_EQUAL_DOUBLE(-88.4715662266948, out.b);

    CIEXYZ xyz2 = { 0, 0, 0 };
    ciexyz_to_cielab(&xyz2, D65_2_Reference, &out);

    TEST_ASSERT_EQUAL_DOUBLE(0, out.L);
    TEST_ASSERT_EQUAL_DOUBLE(0, out.a);
    TEST_ASSERT_EQUAL_DOUBLE(0, out.b);

    CIEXYZ xyz3 = { 95.05, 100, 108.89999999999999 };
    ciexyz_to_cielab(&xyz3, D65_2_Reference, &out);

    TEST_ASSERT_EQUAL_DOUBLE(100, out.L);
    TEST_ASSERT_EQUAL_DOUBLE(0.0052604999583039103, out.a);
    TEST_ASSERT_EQUAL_DOUBLE(-0.010408184525267927, out.b);
}

void test_delta_e_76() {
    CIELab a = {35.40, 65.51, -88.47};
    CIELab b = {35.40, 65.51, -88.47};
    TEST_ASSERT_EQUAL_DOUBLE(0, delta_e_76(&a, &b));

    CIELab c = {58, 44, 38};
    CIELab d = {53, 52, 28};
    TEST_ASSERT_EQUAL_DOUBLE(13.74772708486752, delta_e_76(&c, &d));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_rgb_to_ciexyz);
    RUN_TEST(test_ciexyz_to_cielab);
    RUN_TEST(test_delta_e_76);

    return UNITY_END();
}