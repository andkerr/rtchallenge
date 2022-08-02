#ifndef WORLD_H
#define WORLD_H

#include "light.h"
#include "shape.h"

#include <memory>
#include <vector>

class World {
public:
    World() = default;

    bool empty() const {
        return objects.size() == 0;
    }

    bool has_light() const {
        return light.get() != nullptr;
    }

    void add_shape(std::shared_ptr<Shape> sptr) {
        objects.push_back(sptr);
    }

    std::vector<Intersection> intersect(const Ray& r);

    // Public World data
    std::vector< std::shared_ptr<Shape>> objects;
    std::shared_ptr<Light> light;
};

std::shared_ptr<World> create_dummy_world();

#endif // WORLD_H