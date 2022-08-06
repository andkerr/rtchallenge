#ifndef WORLD_H
#define WORLD_H

#include "light.h"
#include "shape.h"

#include <memory>
#include <vector>

struct IntersectionComps {
    IntersectionComps(const Ray& r, const Intersection& i);

    // Public IntersectionComps data
    double t;
    std::shared_ptr<Shape> obj;
    Point point;
    Vector v_eye;
    Vector v_normal;
    bool inside;
};

class World {
public:
    World()
        : objects(), light(), n_obj(0) { }

    bool empty() const {
        return objects.size() == 0;
    }

    int n_objects() const {
        return n_obj;
    }

    bool has_light() const {
        return light.get() != nullptr;
    }

    void add_shape(std::shared_ptr<Shape> sptr) {
        objects.push_back(sptr);
        ++n_obj;
    }

    std::vector<Intersection> intersect(const Ray& r);

    Colour shade_hit(const IntersectionComps& icomps);

    Colour colour_at(const Ray& r);

    // Public World data
    std::vector< std::shared_ptr<Shape>> objects;
    std::shared_ptr<Light> light;

private:
    int n_obj;
};

std::shared_ptr<World> create_dummy_world();

#endif // WORLD_H