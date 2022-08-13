#include "plane.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Plane tests") {
    SECTION("A Ray that is parallel to a Plane does not intersect it") {
        Plane p((Matrix4x4()));
        Ray r(Point(0, 10, 0), Vector(0, 0, 1));

        std::vector<Intersection> isections;
        REQUIRE(p.intersects(r, isections) == false);
        REQUIRE(isections.size() == 0);
    }

    SECTION("Assuming planes to have infinite thinness, a Ray that is coplanar with a Plane does not intersect it") {
        Plane p((Matrix4x4()));
        Ray r(Point(0, 0, 0), Vector(1, 0, 1));

        std::vector<Intersection> isections;
        REQUIRE(p.intersects(r, isections) == false);
        REQUIRE(isections.size() == 0);
    }

    SECTION("A Ray intersects a Plane from above") {
        Plane p((Matrix4x4()));
        Ray r(Point(0, 10, 0), Vector(0, -1, 0));

        std::vector<Intersection> isections;
        REQUIRE(p.intersects(r, isections) == true);
        REQUIRE(isections.size() == 1);
        REQUIRE(isections[0].t == 10);
    }

    SECTION("A Ray intersects a Plane from below") {
        Plane p((Matrix4x4()));
        Ray r(Point(0, -10, 0), Vector(0, 1, 0));

        std::vector<Intersection> isections;
        REQUIRE(p.intersects(r, isections) == true);
        REQUIRE(isections.size() == 1);
        REQUIRE(isections[0].t == 10);
    }
}