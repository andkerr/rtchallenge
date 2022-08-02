#include "light.h"
#include "sphere.h"
#include "transform.h"
#include "world.h"

#include <cassert>

std::vector<Intersection> intersect(const Ray& r) {
    assert(false);
}

std::shared_ptr<World> create_dummy_world() {
    std::shared_ptr<Light> light(new PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));

    std::shared_ptr<Shape> s1 = create_sphere(Matrix4x4(), 1);
    s1->material = Material(0.1, 0.7, 0.2, 200., Colour(0.8, 1., 0.6));

    Matrix4x4 scale = Transform::scale(0.5, 0.5, 0.5);
    std::shared_ptr<Shape> s2 = create_sphere(scale, 1);

    std::shared_ptr<World> w(new World);
    w->add_shape(s1);
    w->add_shape(s2);
    w->light = light;

    return w;
}