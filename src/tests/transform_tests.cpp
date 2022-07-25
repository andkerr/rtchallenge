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

    SECTION("Scaling affects Points and Vectors") {
        Matrix4x4 scale = Transform::scale(2, 3, 4);
        Point p(-4, 6, 8);
        Vector v(-4, 6, 8);

        REQUIRE(scale.mul(p) == Point(-8, 18, 32));
        REQUIRE(scale.mul(v) == Vector(-8, 18, 32));

        Matrix4x4 inv_scale = scale.inverse();

        REQUIRE(inv_scale.mul(p) == Point(-2, 2, 2));
        REQUIRE(inv_scale.mul(v) == Vector(-2, 2, 2));
    }

    SECTION("Points and Vectors can be reflected along a given axis by scaling the"
            "component lying along that axis by a negative value") {
        Matrix4x4 reflect_along_x = Transform::scale(-1, 1, 1);
        Point p(2, 3, 4);

        REQUIRE(reflect_along_x.mul(p) == Point(-2, 3, 4));
    }

    SECTION("Points and vectors can be rotated about the x axis. Rotations can be applied"
            "in reverse by taking the inverse of a given rotation matrix.") {
        Point p(0, 1, 0);
        Matrix4x4 eighth = Transform::rotate_x(M_PI / 4);
        Matrix4x4 quarter = Transform::rotate_x(M_PI / 2);
    
        REQUIRE(eighth.mul(p) == Point(0, sqrt(2) / 2, sqrt(2) / 2));
        REQUIRE(quarter.mul(p) == Point(0, 0, 1));

        REQUIRE(eighth.inverse().mul(p) == Point(0, sqrt(2) / 2, -sqrt(2) / 2));
        REQUIRE(quarter.inverse().mul(p) == Point(0, 0, -1));
    }

    SECTION("Points and vectors can be rotated about the y axis. Rotations can be applied"
            "in reverse by taking the inverse of a given rotation matrix.") {
        Point p(0, 0, 1);
        Matrix4x4 eighth = Transform::rotate_y(M_PI / 4);
        Matrix4x4 quarter = Transform::rotate_y(M_PI / 2);

        REQUIRE(eighth.mul(p) == Point(sqrt(2) / 2, 0, sqrt(2) / 2));
        REQUIRE(quarter.mul(p) == Point(1, 0, 0));

        REQUIRE(eighth.inverse().mul(p) == Point(-sqrt(2) / 2, 0, sqrt(2) / 2));
        REQUIRE(quarter.inverse().mul(p) == Point(-1, 0, 0));
    }
    
    SECTION("Points and vectors can be rotated about the z axis. Rotations can be applied"
            "in reverse by taking the inverse of a given rotation matrix.") {
        Point p(0, 1, 0);
        Matrix4x4 eighth = Transform::rotate_z(M_PI / 4);
        Matrix4x4 quarter = Transform::rotate_z(M_PI / 2);

        REQUIRE(eighth.mul(p) == Point(-sqrt(2) / 2, sqrt(2) / 2, 0));
        REQUIRE(quarter.mul(p) == Point(-1, 0, 0));

        REQUIRE(eighth.inverse().mul(p) == Point(sqrt(2) / 2, sqrt(2) / 2, 0));
        REQUIRE(quarter.inverse().mul(p) == Point(1, 0, 0));
    }
}