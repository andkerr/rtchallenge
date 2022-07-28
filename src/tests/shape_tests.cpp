#include "shape.h"
#include "sphere.h"
#include "transform.h"

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

        REQUIRE(r.displace_by(0) == Point(2, 3, 4));
        REQUIRE(r.displace_by(1) == Point(3, 3, 4));
        REQUIRE(r.displace_by(-1) == Point(1, 3, 4));
        REQUIRE(r.displace_by(2.5) == Point(4.5, 3, 4));
    }

    SECTION("Ray-sphere intersections calculations return true if a given Ray and Sphere intersect,"
            "and false, if they do not. A std::pair passed-to the query contains solutions in the form"
            "of displacement from the ray's origin, if they exist") {
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        Sphere s(Matrix4x4(), 1.0);

        std::vector<Intersection> solns;
        REQUIRE(s.intersects(r, solns) == true);
        REQUIRE(solns[0].t == 4);
        REQUIRE(solns[1].t == 6);

        r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
        solns.clear();
        REQUIRE(s.intersects(r, solns) == true);
        REQUIRE(solns[0].t == 5);
        REQUIRE(solns[1].t == 5);

        r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
        solns.clear();
        REQUIRE(s.intersects(r, solns) == false);
    }

    SECTION("Rays that originate inside a Sphere intersect with it upon exiting") {
        Ray r(Point(0, 0, 0), Vector(0, 0, 1));
        Sphere s(Matrix4x4(), 1);

        std::vector<Intersection> solns;
        REQUIRE(s.intersects(r, solns) == true);
        REQUIRE(solns[0].t == -1);
        REQUIRE(solns[1].t == 1);
    }

    SECTION("Rays extend in both the positive and negative direction of their direction vectors") {
        Ray r(Point(0, 0, 2), Vector(0, 0, 1));
        Sphere s(Matrix4x4(), 1);

        std::vector<Intersection> solns;
        s.intersects(r, solns);
        REQUIRE(s.intersects(r, solns) == true);
        REQUIRE(solns[0].t == -3);
        REQUIRE(solns[1].t == -1);
    }

    SECTION("The Intersection object incapsulates a single t value, and the object that a given Ray intersects with") {
        std::shared_ptr<Shape> sptr = create_sphere(Matrix4x4(), 4);
        double t = 1.5;
        Intersection i(t, sptr);

        REQUIRE(i.t == 1.5);
        REQUIRE(i.obj == sptr);
    }

    SECTION("A hit is the Intersection with the lowest positive t value in a collection. If no Intersections"
            "from a collection have a positive t value, no hit is identified") {
        std::shared_ptr<Shape> s = create_sphere(Matrix4x4(), 5);
        Intersection i1(1, s);
        Intersection i2(2, s);
    
        std::vector<Intersection> is = {i1, i2};
        Intersection hit;
        REQUIRE(find_hit(is, hit) == true);
        REQUIRE(hit == i1);
    
        i1 = Intersection(-1, s);
        is = {i2, i1};
        REQUIRE(find_hit(is, hit) == true);
        REQUIRE(hit == i2);


        i2 = Intersection(-2, s);
        is = {i2, i1};
        REQUIRE(find_hit(is, hit) == false);
    }

    SECTION("Hits are correctly identified regardless of whether the Intersection sequence"
            "is sorted on t value or not") {
        std::shared_ptr<Shape> s = create_sphere(Matrix4x4(), 5);
        Intersection i1(5, s);
        Intersection i2(7, s);
        Intersection i3(-3, s);
        Intersection i4(2, s);
        std::vector<Intersection> intersections = {i1, i2, i3, i4};

        Intersection hit;
        REQUIRE(find_hit(intersections, hit) == true);
        REQUIRE(hit == i4);
    }

    SECTION("Transforming a Ray returns a new Ray with correctly-adjusted origin and direction") {
        Ray r(Point(1, 2, 3), Vector(0, 1, 0));
        Matrix4x4 translate = Transform::translate(3, 4, 5);
        Matrix4x4 scale = Transform::scale(2, 3, 4);

        REQUIRE(r.transform(translate) == Ray(Point(4, 6, 8), Vector(0, 1, 0)));
        REQUIRE(r.transform(scale) == Ray(Point(2, 6, 12), Vector(0, 3, 0)));
    }

    SECTION("Shapes contain a transformation matrix that encodes how to move between"
            "their and the world's frame-of-reference. This is the identity matrix by default") {
        Matrix4x4 identity;
        std::shared_ptr<Shape> s = create_sphere(Matrix4x4(), 9);
        
        REQUIRE(s->obj_to_world == identity);

        Matrix4x4 translate = Transform:: translate(2, 3, 4);
        s = create_sphere(translate, 9);
        REQUIRE(s->obj_to_world == translate);
    }

    SECTION("The normal vector at a given point on a Sphere points perpendicular to its surface") {
        Sphere s(Matrix4x4(), 1);

        Vector normal = s.normal(Point(1, 0, 0));
        REQUIRE(normal == Vector(1, 0, 0));
        REQUIRE(normal.magnitude() == 1);

        normal = s.normal(Point(0, -1, 0));
        REQUIRE(normal == Vector(0, -1, 0));
        REQUIRE(normal.magnitude() == 1);

        normal = s.normal(Point(0, 0, 1));
        REQUIRE(normal == Vector(0, 0, 1));
        REQUIRE(normal.magnitude() == 1);
        
        normal = s.normal(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
        REQUIRE(normal == Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
        REQUIRE(normal.magnitude() == 1);
    }

    SECTION("Sphere normals respect any transformations that have been applied to the shape") {
        Matrix4x4 translate = Transform::translate(0, 1, 0);
        Sphere s(translate, 1);

        Vector normal = s.normal(Point(0, 1.70711, -0.70711));
        REQUIRE(normal == Vector(0, 0.70711, -0.70711));
        REQUIRE(normal.magnitude() == 1);


        Matrix4x4 t = Transform::scale(1, 0.5, 1).mul(Transform::rotate_z(M_PI / 5));
        Sphere s2(t, 1);
        
        normal = s2.normal(Point(0, sqrt(2) / 2, -sqrt(2) / 2));
        REQUIRE(normal == Vector(0, 0.97014, -0.24254));
        REQUIRE(normal.magnitude() == 1);
    }

    SECTION("Vectors are relfected about a Shape's normal vector at a given point") {
        Vector v(1, -1, 0);
        Vector n(0, 1, 0);
        REQUIRE(reflect(v, n) == Vector(1, 1, 0));
    
        v = Vector(0, -1, 0);
        n = Vector(sqrt(2) / 2, sqrt(2) / 2, 0);
        REQUIRE(reflect(v, n) == Vector(1, 0, 0));
    }
}