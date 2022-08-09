#include "sphere.h"
#include "transform.h"
#include "world.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("World tests") {
    SECTION("By default, a world has no shapes and no light source") {
        World w;
        REQUIRE(w.empty());
        REQUIRE(!w.has_light());
    }

    SECTION("create_dummy_world() initializes a default World with specific presets") {
        std::shared_ptr<World> w = create_dummy_world();

        REQUIRE(w->n_objects() == 2);
        REQUIRE(w->light->position == Point(-10, 10, -10));
        REQUIRE(w->light->intensity == Colour(1, 1, 1));
    
        std::shared_ptr<Shape> s1 = w->objects[0];
        REQUIRE(s1->material.colour == Colour(0.8, 1.0, 0.6));
        REQUIRE(s1->material.ambient == 0.1);
        REQUIRE(s1->material.diffuse == 0.7);
        REQUIRE(s1->material.specular == 0.2);
        REQUIRE(s1->material.shininess == 200.);

        std::shared_ptr<Shape> s2 = w->objects[1];
        REQUIRE(s2->material.colour == Colour(1, 1, 1));
        REQUIRE(s2->material.ambient == 0.1);
        REQUIRE(s2->material.diffuse == 0.9);
        REQUIRE(s2->material.specular == 0.9);
        REQUIRE(s2->material.shininess == 200.);
    }

    SECTION("Given a Ray, a World object computes the intersections between"
            "the Ray and any objects it contains") {
        std::shared_ptr<World> w = create_dummy_world();
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        std::vector<Intersection> result = w->intersect(r);

        REQUIRE(result.size() == 4);
        REQUIRE(result[0].t == 4);
        REQUIRE(result[1].t == 4.5);
        REQUIRE(result[2].t == 5.5);
        REQUIRE(result[3].t == 6);
    }

    SECTION("A IntersectionComps object contains information about a given Ray and Shape that it intersects with") {
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        std::shared_ptr<Shape> s = create_sphere(Matrix4x4(), 1);
        Intersection i(4, s);

        IntersectionComps icomps(r, i);
        REQUIRE(icomps.t == 4);
        REQUIRE(icomps.obj == s);
        REQUIRE(icomps.point == Point(0, 0, -1));
        REQUIRE(icomps.v_eye == Vector(0, 0, -1));
        REQUIRE(icomps.v_normal == Vector(0, 0, -1));
        REQUIRE(icomps.inside == false);
    }

    SECTION("If the eye vector and normal vector at an intersection point in opposite directions, the intersecting"
            "Ray is correctly identified as having oringiated inside the given Shape") {
        Ray r(Point(0, 0, 0), Vector(0, 0, 1));
        std::shared_ptr<Shape> s = create_sphere(Matrix4x4(), 1);
        Intersection i(1, s);

        IntersectionComps icomps(r, i);
        REQUIRE(icomps.t == 1);
        REQUIRE(icomps.obj == s);
        REQUIRE(icomps.point == Point(0, 0, 1));
        REQUIRE(icomps.v_eye == Vector(0, 0, -1));
        REQUIRE(icomps.v_normal == Vector(0, 0, -1));
        REQUIRE(icomps.inside == true);
    }

    SECTION("shade_hit() returns the correct Colour for a given set of IntersectionComps") {
        std::shared_ptr<World> w = create_dummy_world();
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        std::shared_ptr<Shape> s1 = w->objects[0];
        Intersection i1(4, s1);
        IntersectionComps icomps1(r, i1);
        Colour c = w->shade_hit(icomps1);

        REQUIRE(c == Colour(0.38066, 0.47583, 0.2855));
    }

    SECTION("Intersections can be shaded when the intersecting Ray originates inside the Shape") {
        std::shared_ptr<World> w = create_dummy_world();
        w->light = std::make_shared<Light>(PointLight(Point(0, 0.25, 0), Colour(1, 1, 1)));
        Ray r(Point(0, 0, 0), Vector(0, 0, 1));
        std::shared_ptr<Shape> s2 = w->objects[1];
        Intersection i(0.5, s2);
        IntersectionComps icomps(r, i);
        Colour c = w->shade_hit(icomps);

        REQUIRE(c == Colour(0.90498, 0.90498, 0.90498));
    }

    SECTION("When a Ray intersects no objects, the corresponding Colour is black") {
        std::shared_ptr<World> w = create_dummy_world();
        Ray r(Point(0, 0, -5), Vector(0, 1, 0));

        REQUIRE(w->colour_at(r) == Colour(0, 0, 0));
    }

    SECTION("...otherwise, colour_at returns the Colour appropriate for the Shape the Ray intersects with") {
        std::shared_ptr<World> w = create_dummy_world();
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        Colour c = w->colour_at(r);

        REQUIRE(c == Colour(0.38066, 0.47583, 0.2855));
    }

    SECTION("colour_at from inside a Shape") {
        std::shared_ptr<World> w = create_dummy_world();
        std::shared_ptr<Shape> outer = w->objects[0];
        std::shared_ptr<Shape> inner = w->objects[1];
        outer->material.ambient = 1.;
        inner->material.ambient = 1.;
        Ray r(Point(0, 0, 0.75), Vector(0, 0, -1));
        Colour c = w->colour_at(r);

        REQUIRE(c == inner->material.colour);
    }

    SECTION("There is no shadow when nothing is collinear with a Point and the (single) Light source") {
        std::shared_ptr<World> w = create_dummy_world();
        Point p(0, 10, 0);

        REQUIRE(w->is_shadowed(p) == false);
    }

    SECTION("A point is in shadow when a Shape is located in the path from the Light source to it") {
        std::shared_ptr<World> w = create_dummy_world();
        Point p(10, -10, 10);

        REQUIRE(w->is_shadowed(p) == true);
    }

    SECTION("A Point is not in shadow if nothing lies between it and the (single) Light source") {
        std::shared_ptr<World> w = create_dummy_world();
        Point p(-20, 20, -20);

        // Light, Point, and Shape are collinear. Light between Point and Shape
        REQUIRE(w->is_shadowed(p) == false);

        // Light, Point, and Shape are collinear. Point between Light and Shape
        p = Point(-2, 2, -2);
        REQUIRE(w->is_shadowed(p) == false);
    }

    SECTION("shade_hit considers intersections that are in shadow") {
        std::shared_ptr<World> w(new World);
        w->light = std::make_shared<Light>(PointLight(Point(0, 0, -10), Colour(1, 1, 1)));

        std::shared_ptr<Shape> s1 = create_sphere(Matrix4x4(), 1);
        w->add_shape(s1);

        std::shared_ptr<Shape> s2 = create_sphere(Transform::translate(0, 0, 10), 1);
        w->add_shape(s2);

        Ray r(Point(0, 0, 5), Vector(0, 0, 1));
        Intersection i(4, s2);
        IntersectionComps icomps(r, i);

        Colour c = w->shade_hit(icomps);
        REQUIRE(c == Colour(0.1, 0.1, 0.1));
    }

    SECTION("Hit points are offset slightly in the direction of their normal vectors. This guards against"
            "self-shadowing due to floating point error.") {
        Ray r(Point(0, 0, -5), Vector(0, 0, 1));
        std::shared_ptr<Shape> s = create_sphere(Transform::translate(0, 0, 1), 1);
        Intersection i(5, s);
        IntersectionComps icomps (r, i);

        REQUIRE(icomps.over_point.z < -EPSILON / 2.);
        REQUIRE(icomps.point.z > icomps.over_point.z);
    }
}