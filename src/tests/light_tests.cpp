#include "light.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Light tests") {
    SECTION("PointLights have a position and an intensity") {
        PointLight pl(Point(0, 0, 0), Colour(1, 1, 1));
        REQUIRE(pl.position == Point(0, 0, 0));
        REQUIRE(pl.intensity == Colour(1, 1, 1));
    }
}