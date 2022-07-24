#include "matrix.h"
#include "transform.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tranformations tests") {
    SECTION("Translation matrices translate a point by the specificed dimensions") {
        Matrix4x4 translate = Transform::translate(5, -3, 2);
        Point p(-3, 4, 5);

        REQUIRE(translate.mul(p) == Point(2, 1, 7));
    }

    SECTION("Applying the inverse of a transform matrix applies the opposite tranformation to a point") {
        Matrix4x4 translate = Transform::translate(5, -3, 2);
        Point p(-3, 4, 5);
        Matrix4x4 inverse = translate.inverse();

        REQUIRE(inverse.mul(p) == Point(-8, 7, 3));
    }

    SECTION("Translation does not affect vectors") {
        Matrix4x4 translate = Transform::translate(5, -3, 2);
        Vector v(-3, 4, 5);

        REQUIRE(translate.mul(v) == v);
    }
}