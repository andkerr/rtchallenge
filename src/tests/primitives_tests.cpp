#include "primitives.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Primitives tests") {
    SECTION("Rays are constructed from a point of origin and a direction vector") {
        Point p(0, 0, 0);
        Vector v(1, 2, 3);
        Ray r(p, v);

        REQUIRE(r.origin == Point(0, 0, 0));
        REQUIRE(r.direction == Vector(1, 2, 3));
    }

    SECTION("Multiplying a ray's direction vector by a scalar t returns the Point"
            "that is displace v * t from the ray's origin") {
        Ray r(Point(2, 3, 4), Vector(1, 0, 0));

        REQUIRE(r.displace(0) == Point(2, 3, 4));
        REQUIRE(r.displace(1) == Point(3, 3, 4));
        REQUIRE(r.displace(-1) == Point(1, 3, 4));
        REQUIRE(r.displace(2.5) == Point(4.5, 3, 4));
    }

    SECTION("Ray-sphere intersections calculations return true if a given Ray and Sphere intersect,"
            "and false, if they do not. A std::pair passed-to the query contains solutions in the form"
            "of displacement from the ray's origin, if they exist") {
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        Sphere s(Point(0, 0, 0), 1.0);

        Intersection solns;
        REQUIRE(r.intersects(s, solns) == true);
        REQUIRE(solns.t1 == 4);
        REQUIRE(solns.t2 == 6);

        r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
        REQUIRE(r.intersects(s, solns) == true);
        REQUIRE(solns.t1 == 5);
        REQUIRE(solns.t2 == 5);

        r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
        REQUIRE(r.intersects(s, solns) == false);
    }

    SECTION("Rays that originate inside a Sphere intersect with it upon exiting") {
        Ray r(Point(0, 0, 0), Vector(0, 0, 1));
        Sphere s(Point(0, 0, 0), 1);

        Intersection solns;
        REQUIRE(r.intersects(s, solns) == true);
        REQUIRE(solns.t1 == -1);
        REQUIRE(solns.t2 == 1);
    }

    SECTION("Rays extend in both the positive and negative direction of their direction vectors") {
        Ray r(Point(0, 0, 2), Vector(0, 0, 1));
        Sphere s(Point(0, 0, 0), 1);

        Intersection soln;
    }

    SECTION("The Intersection object incapsulates t values, and the object that a given Ray intersects with") {
        const Sphere s(Point(1, 3, 4), 5.3);
        double t1 = 1.5;
        double t2 = -4;

        Intersection i;
        i.obj = &s;

        REQUIRE(*(i.obj) == s);
    }
}