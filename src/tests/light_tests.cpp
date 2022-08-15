#include "light.h"
#include "material.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Light tests") {
    SECTION("PointLights have a position and an intensity") {
        PointLight pl(Point(0, 0, 0), Colour(1, 1, 1));
        REQUIRE(pl.position == Point(0, 0, 0));
        REQUIRE(pl.intensity == Colour(1, 1, 1));
    }

    SECTION("Putting the camera directly between a PointLight and a perpendicular surface gives maximum intensity") {
        Point position(0, 0, 0);
        Vector camera(0, 0, -1);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 0, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal, false) == Colour(1.9, 1.9, 1.9));
    }

    SECTION("Camera 45 degrees off reflection vector gives (effectively) 0 specular reflection") {
        Point position(0, 0, 0);
        Vector camera(0, sqrt(2) / 2, -sqrt(2) / 2);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 0, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal, false) == Colour(1., 1., 1.));
    }

    SECTION("Diffuse reflection drops when a Light move out of the path of the normal vector") {
        Point position(0, 0, 0);
        Vector camera(0, 0, -1);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 10, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal, false) == Colour(0.7364, 0.7364, 0.7364));
    }

    SECTION("Camera in path of reflection vector gives full specular reflection") {
        Point position(0, 0, 0);
        Vector camera(0, -sqrt(2) / 2, -sqrt(2) / 2);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 10, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal, false) == Colour(1.6364, 1.6364, 1.6364));
    }

    SECTION("If a surface comes between the camera and a point light, only ambient reflection reaches the camera") {
        Point position(0, 0, 0);
        Vector camera(0, -sqrt(2) / 2, -sqrt(2) / 2);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 10, 10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal, false) == Colour(0.1, 0.1, 0.1));       
    }

    SECTION("If an Point is in shadow, only its ambient reflection contributes to its colour") {
        Point position(0, 0, 0);
        Vector camera(0, 0, -1);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 0, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal, true) == Colour(0.1, 0.1, 0.1));       
    }

    SECTION("The lighting functions considers whether a given material has a pattern") {
        Material m(1., 0., 0., 200.,
                   Colour(0.5, 0.5, 0.5),
                   std::make_shared<Pattern::Stripe>(Pattern::Stripe(Colour(1, 1, 1), Colour(0, 0, 0))));

        Vector v_eye(0, 0, -1);
        Vector v_norm(0, 0, -1);
        PointLight light(Point(0, 0, -10), Colour(1, 1, 1));

        REQUIRE(lighting(m, &light, Point(0.9, 0, 0), v_eye, v_norm, false) == Colour(1, 1, 1));
        REQUIRE(lighting(m, &light, Point(1.1, 0, 0), v_eye, v_norm, false) == Colour(0, 0, 0));
    }
}