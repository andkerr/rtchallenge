#include "canvas.h"

#include <sstream>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Canvas tests") {
    SECTION("Canvas ctor initializes a width * height length array of default-Colour pixels") {
        const int w = 10;
        const int h = 20;
        Canvas c(w, h);

        REQUIRE(c.size() == 200);
        for (int x = 0; x < w; ++x) {
            for (int y = 0; y < h; ++y) {
                REQUIRE(c.get_pixel(x, y) == Colour(0, 0, 0));
            }
        }
    }

    SECTION("Canvas supports pixel getting and setting") {
        Canvas c(10, 20);
        Colour red(1, 0, 0);
        c.set_pixel(5, 3, red);

        REQUIRE(c.get_pixel(5, 3) == red);
    }

    SECTION("Canvas prints to PPM format") {
        Canvas canvas(2, 2);
        Colour c1(1.5, 0, 0);
        Colour c2(-0.5, 0, 1);
        canvas.set_pixel(0, 0, c1);
        canvas.set_pixel(1, 1, c2);

        std::ostringstream result;
        canvas.to_ppm(result);

        std::ostringstream expected;
        expected << "P3\n2 2\n255\n255 0 0 0 0 0 \n0 0 0 0 0 255 \n";

        REQUIRE(result.str() == expected.str());
    }
}