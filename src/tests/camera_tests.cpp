#include "camera.h"
#include "transform.h"
#include "world.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

TEST_CASE("Camera tests") {
    SECTION("The transformation for the default view (at the origin,"
            "looking down the negative z-axis) is the identity matrix") {
        REQUIRE(view_transformation(Point(0, 0, 0), Point(0, 0, -1), Vector(0, 1, 0)) == Matrix4x4());
    }

    SECTION("Looking down the positive z-axis, +y is still up") {
        Matrix4x4 vtrans = view_transformation(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0));
        REQUIRE(vtrans == Transform::scale(-1, 1, -1));
    }

    SECTION("View transformations actually apply to the world, *not* the camera."
            "e.g. to move the camera +8 z-units, the world moves -8 z-units") {
        Matrix4x4 vtrans = view_transformation(Point(0, 0, 8), Point(0, 0, 0), Vector(0, 1, 0));
        REQUIRE(vtrans == Transform::translate(0, 0, -8));
    }

    SECTION("Arbitrary view transformation") {
        Matrix4x4 vtrans = view_transformation(Point(1, 3, 2), Point(4, -2, 8), Vector(1, 1, 0));
        Matrix4x4 expected(-0.50709, 0.50709,  0.67612, -2.36643,
 	                       0.76772, 0.60609,  0.12122, -2.82843,
 	                       -0.35857, 0.59761, -0.71714,  0.00000,
 	                       0.00000, 0.00000,  0.00000,  1.00000);
        REQUIRE(vtrans == expected);
    }

    SECTION("If a view transform is not passed to the Camera contstructor, the new"
            "Camera is given the identity matrix (no transformation) by default") {
        Camera camera(160, 120, M_PI / 2);

        REQUIRE(camera.canvas_w == 160);
        REQUIRE(camera.canvas_h == 120);
        REQUIRE(camera.field_of_view == M_PI / 2);
    }

    SECTION("Pixel size is computed correctly for horizontal and vertical canvases") {
        using Catch::Approx;
        using std::cout;

        Camera c1(200, 125, M_PI / 2);
        Camera c2(125, 200, M_PI / 2);

        REQUIRE(c1.pixel_size == Approx(0.01));
        REQUIRE (c2.pixel_size == Approx(0.01));
    }

    SECTION("Rays can be constructed to travel from a given Camera through a given Point on its Canvas") {
        Camera c(201, 101, M_PI / 2);
        Ray r = c.ray_for(100, 50);

        REQUIRE(r.origin == Point(0, 0, 0));
        REQUIRE(r.direction == Vector(0, 0, -1));

        r = c.ray_for(0, 0);
        REQUIRE(r.origin == Point(0, 0, 0));
        REQUIRE(r.direction == Vector(0.66519, 0.33259, -0.66851));
    }

    SECTION("Rays are correctly constructed for transformed Cameras") {
        Matrix4x4 transform = Transform::rotate_y(M_PI / 4).mul(Transform::translate(0, -2, 5));
        Camera c(201, 101, M_PI / 2, transform);
        Ray r = c.ray_for(100, 50);

        REQUIRE(r.origin == Point(0, 2, -5));
        REQUIRE(r.direction == Vector(sqrt(2) / 2, 0, -sqrt(2) / 2));
    }

    SECTION("Cameras can be used to render an image of a World") {
        std::shared_ptr<World> w = create_dummy_world();
        Camera c(11, 11, M_PI / 2, Point(0, 0, -5), Point(0, 0, 0), Vector(0, 1, 0));
        Canvas image = c.render(w);

        REQUIRE(image.get_pixel(5, 5) == Colour(0.38066, 0.47583, 0.2855));
    }
}