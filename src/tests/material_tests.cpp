#include "material.h"
#include "sphere.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Material tests") {
    SECTION("Materials can be default constructed from parameters defined in material.h") {
        Material m;
        REQUIRE(m.ambient == 0.1);
        REQUIRE(m.diffuse == 0.9);
        REQUIRE(m.specular == 0.9);
        REQUIRE(m.shininess == 200.);
        REQUIRE(m.colour == Colour(1, 1, 1));
    }
}