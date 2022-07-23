#include "geometry.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Geometry Tests") {
    SECTION("A tuple with w = 1 is a point") {
        Tuple t(-4.2, 1, 0, 1);

        REQUIRE(t.x == -4.2);
        REQUIRE(t.y == 1);
        REQUIRE(t.z == 0);
        REQUIRE(t.w == 1);
        REQUIRE(t.is_point());
        REQUIRE(!t.is_vector());
    }

    SECTION("A tuple with w = 0 is a vector") {
        Tuple t(-8.3, 0.3, 1.3, 0);
        
        REQUIRE(t.x == -8.3);
        REQUIRE(t.y == 0.3);
        REQUIRE(t.z == 1.3);
        REQUIRE(t.w == 0);
        REQUIRE(!t.is_point());
        REQUIRE(t.is_vector());
    }

    SECTION("Point ctor creates a Tuple with w = 1") {
        Point p(0.3, 0.123, 3.1);

        REQUIRE(p == Tuple(0.3, 0.123, 3.1, 1));
    }

    SECTION("Vector ctor creates a Tuple with w = 0") {
        Vector v(0.3, 0.123, 3.1);
    
        REQUIRE(v == Tuple(0.3, 0.123, 3.1, 0));
    }

    SECTION("Points with equal parameters compare equal") {
        Point p1(0.3, 0.123, 3.1);
        Point p2(0.3, 0.123, 3.1);

        REQUIRE(p1 == p2);
    }

    SECTION("Vectors with equal parameters compare equal") {
        Vector v1(0.3, 0.123, 3.1);
        Vector v2(0.3, 0.123, 3.1);

        REQUIRE(v1 == v2);
    }

    SECTION("Adding two tuples performs parameter-wise addition") {
        Tuple t1(3, -2, 5, 1);
        Tuple t2(-2, 3, 1, 0);

        REQUIRE(t1 + t2 == Tuple(1, 1, 6, 1));
        REQUIRE(t1 + t2 == Point(1, 1, 6));
    }

    SECTION("Subtracting two points returns the vector pointing from the subtrahend to the minuend") {
        Point p1(3, 2, 1);
        Point p2(5, 6, 7);

        REQUIRE(p1 - p2 == Vector(-2, -4, -6));
    }

    SECTION("Subtracting a vector from a point returns the point reached by travelling 'backward' along the vector") {
        Point p(3, 2, 1);
        Vector v(5, 6, 7);

        REQUIRE(p - v == Point(-2, -4, -6));
    }

    SECTION("Subtracting two vectors returns the vector representing the change in direction between the two") {
        Vector v1(3, 2, 1);
        Vector v2(5, 6, 7);

        REQUIRE(v1 - v2 == Vector(-2, -4, -6));
    }

    SECTION("Tuples can be negated with a unary minus") {
        Tuple t(1, -2, 3, -4);

        REQUIRE(-t == Tuple(-1, 2, -3, 4));
    }

    SECTION("Tuples support scalar multiplication (and division)") {
        Tuple t(1, -2, 3, -4);

        REQUIRE(t * 3.5 == Tuple(3.5, -7, 10.5, -14));
        REQUIRE(t * 0.5 == Tuple(0.5, -1, 1.5, -2));
        REQUIRE(t / 2 == Tuple(0.5, -1, 1.5, -2));
    }

    SECTION("Vector magnitude computes the L2 norm") {
        Vector v(1, 0, 0);
        REQUIRE(v.magnitude() == 1);

        v = Vector(0, 1, 0);
        REQUIRE(v.magnitude() == 1);

        v = Vector(0, 0, 1);
        REQUIRE(v.magnitude() == 1);

        v = Vector(1, 2, 3);
        REQUIRE(v.magnitude() == std::sqrt(14));

        v = Vector(-1, -2, -3);
        REQUIRE(v.magnitude() == std::sqrt(14));
    }

    SECTION("Vectors can be normalized to unit length") {
        Vector v(4, 0, 0);
        REQUIRE(v.normalize() == Vector(1, 0, 0));

        v = Vector(1, 2, 3);
        REQUIRE(v.normalize() == Vector(0.26726, 0.53452, 0.80178));

        REQUIRE(v.normalize().magnitude() == 1);
    }

    SECTION("Scalar products can be computed between two vectors") {
        Vector v1(1, 2, 3);
        Vector v2(2, 3, 4);

        REQUIRE(v1.dot(v2) == 20);
        REQUIRE(v2.dot(v1) == 20);
    }

    SECTION("Vector proucts can be computed between two vectors") {
        Vector v1(1, 2, 3);
        Vector v2(2, 3, 4);

        REQUIRE(v1.cross(v2) == Vector(-1, 2, -1));
        REQUIRE(v2.cross(v1) == Vector(1, -2, 1));
    }
}