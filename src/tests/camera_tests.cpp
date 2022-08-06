#include "camera.h"
#include "transform.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Camera tests") {
    SECTION("The transformation for the default view (at the origin,"
            "looking down the negative z-axis) is the identity matrix") {
        REQUIRE(view_transformation(Point(0, 0, 0), Point(0, 0, -1), Vector(0, 1, 0)) == Matrix4x4());
    }

    SECTION("Looking down the positive z-axis, +y is still up") {
        Matrix4x4 vtrans = view_transformation(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0));
        REQUIRE(vtrans == Transform::scale(-1, 1, -1));
    }

    SECTION("View transformations actually apply to the world, *not* the camera."
            "e.g. to move the camera +8 z-units, the world moves -8 z-units") {
        Matrix4x4 vtrans = view_transformation(Point(0, 0, 8), Point(0, 0, 0), Vector(0, 1, 0));
        REQUIRE(vtrans == Transform::translate(0, 0, -8));
    }

    SECTION("Arbitrary view transformation") {
        Matrix4x4 vtrans = view_transformation(Point(1, 3, 2), Point(4, -2, 8), Vector(1, 1, 0));
        Matrix4x4 expected(-0.50709, 0.50709,  0.67612, -2.36643,
 	                       0.76772, 0.60609,  0.12122, -2.82843,
 	                       -0.35857, 0.59761, -0.71714,  0.00000,
 	                       0.00000, 0.00000,  0.00000,  1.00000);
        REQUIRE(vtrans == expected);
    }
}