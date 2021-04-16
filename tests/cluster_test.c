#include <unity.h>
#include <cluster.h>
#include <image.h>
#include <stdlib.h>

void setUp(void) {}

void tearDown(void) {}

void test_points_from_image() {
    typedef struct {
        char *name;
        char *img_path;
        Point expected_first_point;
        int expected_len;
    } points_from_image_test_case;

    points_from_image_test_case tests[] = {
            {
                .name = "when points are extracted from a large JPEG",
                .img_path = "./_DSF0914.jpg",
                .expected_first_point = (Point){
                        .x = 0,
                        .y = 0,
                        .pixel = (RGB){67, 78, 98},
                },
                .expected_len = 23818345,
            },
            {
                    .name = "when points are extracted from a small JPEG of uniform colour",
                    .img_path = "./orange.jpg",
                    .expected_first_point = (Point){
                            .x = 0,
                            .y = 0,
                            .pixel = (RGB){255, 102, 0},
                    },
                    .expected_len = 4784,
            }
    };

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        points_from_image_test_case tc = tests[i];

        TEST_MESSAGE(tc.name);

        Image img = {0};

        int ret = image_load(tc.img_path, &img);
        TEST_ASSERT_EQUAL(0, ret);

        Point *points = malloc(img.x * img.y * sizeof(Point));
        size_t len;

        ret = points_from_image(&img, points, &len);
        TEST_ASSERT_EQUAL(0, ret);

        Point first_pixel_point = points[0];
        TEST_ASSERT_EQUAL(tc.expected_first_point.x, first_pixel_point.x);
        TEST_ASSERT_EQUAL(tc.expected_first_point.y, first_pixel_point.y);
        TEST_ASSERT_EQUAL(tc.expected_first_point.pixel.R, first_pixel_point.pixel.R);
        TEST_ASSERT_EQUAL(tc.expected_first_point.pixel.G, first_pixel_point.pixel.G);
        TEST_ASSERT_EQUAL(tc.expected_first_point.pixel.B, first_pixel_point.pixel.B);

        TEST_ASSERT_EQUAL(tc.expected_len, len);
    }
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_points_from_image);

    return UNITY_END();
}