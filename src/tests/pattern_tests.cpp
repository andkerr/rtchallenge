#include "pattern.h"
#include "sphere.h"
#include "transform.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Pattern tests") {
    Colour black(0, 0, 0);
    Colour white(1, 1, 1);

    SECTION("By default, Stripe patterns vary in x, and are constant in y and z") {
        Pattern::Stripe stripe(white, black);

        REQUIRE(stripe.axis == 0);

        REQUIRE(stripe.at(Point(0, 0, 0)) == white);
        REQUIRE(stripe.at(Point(0, 1, 0)) == white);
        REQUIRE(stripe.at(Point(0, 2, 0)) == white);

        REQUIRE(stripe.at(Point(0, 0, 0)) == white);
        REQUIRE(stripe.at(Point(0, 0, 1)) == white);
        REQUIRE(stripe.at(Point(0, 0, 2)) == white);

        REQUIRE(stripe.at(Point(0, 0, 0)) == white);
        REQUIRE(stripe.at(Point(1, 0, 0)) == black);
        REQUIRE(stripe.at(Point(2, 0, 0)) == white);
    }

    SECTION("Patterns respect object transformations") {
        std::shared_ptr<Shape> s = create_sphere(Transform::scale(2, 2, 2), 1);
        std::shared_ptr<Pattern::Pattern> stripe(new Pattern::Stripe(Colour(1, 1, 1), Colour(0, 0, 0)));
        s->material.pattern = stripe;
        
        REQUIRE(s->pattern_at(Point(1.5, 0, 0)) == Colour(1, 1, 1));
    }

    SECTION("Patterns respect transformations on themselves") {
        std::shared_ptr<Shape> s = create_sphere(Matrix4x4(), 1);
        std::shared_ptr<Pattern::Pattern> stripe(new Pattern::Stripe(Colour(1, 1, 1),
                                                                     Colour(0, 0, 0),
                                                                     Transform::scale(2, 2, 2)));
        s->material.pattern = stripe;
        
        REQUIRE(s->pattern_at(Point(1.5, 0, 0)) == Colour(1, 1, 1));
    }

    SECTION("Patterns respect Shape and Pattern transformations in combination") {
        std::shared_ptr<Shape> s = create_sphere(Transform::scale(2, 2, 2), 1);
        std::shared_ptr<Pattern::Pattern> stripe(new Pattern::Stripe(Colour(1, 1, 1),
                                                                     Colour(0, 0, 0),
                                                                     Transform::translate(0.5, 0, 0)));
        s->material.pattern = stripe;
        
        REQUIRE(s->pattern_at(Point(2.5, 0, 0)) == Colour(1, 1, 1));
    }

    SECTION("Gradients linearly interpolate between two Colours") {
        Pattern::Gradient grad(Colour(1, 1, 1), Colour(0, 0, 0));

        REQUIRE(grad.at(Point(0, 0, 0)) == Colour(1, 1, 1));
        REQUIRE(grad.at(Point(0.25, 0, 0)) == Colour(0.75, 0.75, 0.75));
        REQUIRE(grad.at(Point(0.5, 0, 0)) == Colour(0.5, 0.5, 0.5));
        REQUIRE(grad.at(Point(0.75, 0, 0)) == Colour(0.25, 0.25, 0.25));
    }

    SECTION("Ring patterns produce (2-dimensional) concentric circles") {
        Pattern::Ring ring(Colour(1, 1, 1), Colour(0, 0, 0));

        REQUIRE(ring.at(Point(0, 0, 0)) == Colour(1, 1, 1));
        REQUIRE(ring.at(Point(1, 0, 0)) == Colour(0, 0, 0));
        REQUIRE(ring.at(Point(0, 0, 1)) == Colour(0, 0, 0));
        REQUIRE(ring.at(Point(0.708, 0, 0.708)) == Colour(0, 0, 0));
    }

    SECTION("3D Checkers repeat in x") {
        Pattern::Check3D checker(Colour(1, 1, 1), Colour(0, 0, 0));

        REQUIRE(checker.at(Point(0, 0, 0)) == Colour(1, 1, 1));
        REQUIRE(checker.at(Point(0.99, 0, 0)) == Colour(1, 1, 1));
        REQUIRE(checker.at(Point(1.01, 0, 0)) == Colour(0, 0, 0));
    }

    SECTION("3D Checkers repeat in y") {
        Pattern::Check3D checker(Colour(1, 1, 1), Colour(0, 0, 0));

        REQUIRE(checker.at(Point(0, 0, 0)) == Colour(1, 1, 1));
        REQUIRE(checker.at(Point(0, 0.99, 0)) == Colour(1, 1, 1));
        REQUIRE(checker.at(Point(0, 1.01, 0)) == Colour(0, 0, 0));
    }

    SECTION("3D Checkers repeat in z") {
        Pattern::Check3D checker(Colour(1, 1, 1), Colour(0, 0, 0));

        REQUIRE(checker.at(Point(0, 0, 0)) == Colour(1, 1, 1));
        REQUIRE(checker.at(Point(0, 0, 0.99)) == Colour(1, 1, 1));
        REQUIRE(checker.at(Point(0, 0, 1.01)) == Colour(0, 0, 0));
    }

    SECTION("a CheckUV pattern implements a grid with the specified number of rows and columns on [0, 1]") {
        Pattern::CheckUV uv(2, 2, Colour(1, 1, 1), Colour(0, 0, 0));

        REQUIRE(uv.at(0, 0) == Colour(1, 1, 1));
        REQUIRE(uv.at(0.5, 0) == Colour(0, 0, 0));
        REQUIRE(uv.at(0, 0.5) == Colour(0, 0, 0));
        REQUIRE(uv.at(0.5, 0.5) == Colour(1, 1, 1));
        REQUIRE(uv.at(1, 1) == Colour(1, 1, 1));
    }

    SECTION("Points can be mapped to UV coords in [0, 1], assuming a Sphere centered at the origin") {
        std::pair<double, double> result = spherical_map(Point(0, 0, -1));

        REQUIRE(result.first == 0.);
        REQUIRE(result.second == 0.5);
    }

    SECTION("UV patterns map points in 3D to 2D, assuming a Sphere centered at the origin") {
        Pattern::CheckUV uv(16, 8, Colour(1, 1, 1), Colour(0, 0, 0));

    }
}