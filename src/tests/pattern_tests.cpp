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
}