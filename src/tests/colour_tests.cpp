#include "colour.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Colour tests") {
    SECTION("Colors are (r, g, b) tuples") {
        Colour c(-0.5, 0.4, 1.7);
    
        REQUIRE(c.r == -0.5);
        REQUIRE(c.g == 0.4);
        REQUIRE(c.b == 1.7);
    }

    SECTION("Colours can be added and subtracted element-wise") {
        Colour c1(0.9, 0.6, 0.75);
        Colour c2(0.7, 0.1, 0.25);

        REQUIRE(c1 + c2 == Colour(1.6, 0.7, 1));
        REQUIRE(c1 - c2 == Colour(0.2, 0.5, 0.5));
    }

    SECTION("Colours support scalar multiplication (changing brightness)"
            "and mutliplication with other colours (blending)") {
        Colour c(0.2, 0.3, 0.4);

        REQUIRE(c * 2 == Colour(0.4, 0.6, 0.8));
    
        Colour c1(1, 0.2, 0.4);
        Colour c2(0.9, 1, 0.1);
        
        REQUIRE(c1 * c2 == Colour(0.9, 0.2, 0.04));
    }
}