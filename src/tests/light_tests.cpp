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

        REQUIRE(lighting(Material(), &p_light, position, camera, normal) == Colour(1.9, 1.9, 1.9));
    }

    SECTION("Camera 45 degrees off reflection vector gives (effectively) 0 specular reflection") {
        Point position(0, 0, 0);
        Vector camera(0, sqrt(2) / 2, -sqrt(2) / 2);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 0, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal) == Colour(1., 1., 1.));
    }

    SECTION("Diffuse reflection drops when a Light move out of the path of the normal vector") {
        Point position(0, 0, 0);
        Vector camera(0, 0, -1);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 10, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal) == Colour(0.7364, 0.7364, 0.7364));
    }

    SECTION("Camera in path of reflection vector gives full specular reflection") {
        Point position(0, 0, 0);
        Vector camera(0, -sqrt(2) / 2, -sqrt(2) / 2);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 10, -10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal) == Colour(1.6364, 1.6364, 1.6364));
    }

    SECTION("If a surface comes between the camera and a point light, only ambient reflection reaches the camera") {
        Point position(0, 0, 0);
        Vector camera(0, -sqrt(2) / 2, -sqrt(2) / 2);
        Vector normal(0, 0, -1);
        PointLight p_light(Point(0, 10, 10), Colour(1, 1, 1));

        REQUIRE(lighting(Material(), &p_light, position, camera, normal) == Colour(0.1, 0.1, 0.1));       
    }
}