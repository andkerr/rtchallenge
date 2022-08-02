#include "world.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("World tests") {
    SECTION("By default, a world has no shapes and no light source") {
        World w;
        REQUIRE(w.empty());
        REQUIRE(!w.has_light());
    }
}