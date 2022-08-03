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
}