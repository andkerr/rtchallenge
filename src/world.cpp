#include "light.h"
#include "sphere.h"
#include "transform.h"
#include "world.h"

#include <algorithm>
#include <cassert>

IntersectionComps::IntersectionComps(const Ray& r, const Intersection& i) {
    t = i.t;
    obj = i.obj;
    point = r.origin + r.direction * i.t;
    v_eye = -r.direction;
    v_normal = i.obj->normal_at(point);
    inside = v_eye.dot(v_normal) < 0;
    if (inside) {
        v_normal = -v_normal;
    }
}

std::vector<Intersection> World::intersect(const Ray& r) {
    std::vector<Intersection> result;
    std::vector<Intersection> solns;
    for (const std::shared_ptr<Shape> s : objects) {
        if (s->intersects(r, solns)) {
            for (const Intersection& solution : solns) {
                result.push_back(solution);
            }
            solns.clear();
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}

Colour World::shade_hit(const IntersectionComps& icomps) {
    return lighting(icomps.obj->material,
                    light.get(),
                    icomps.point,
                    icomps.v_eye,
                    icomps.v_normal);
}

Colour World::colour_at(const Ray& r) {
    std::vector<Intersection> isections = intersect(r);
    if (isections.size() == 0) {
        return Colour(0, 0, 0);
    }

    Intersection hit;
    if (!find_hit(isections, hit)) {
        assert(false);
    }
    return shade_hit(IntersectionComps(r, hit));
}

/*
    Returns a pointer to a dummy world created from default values.

​ 	 light = PointLight(Point(-10, 10, -10), Colour(1, 1, 1))
​ 	 Shape #1 = Sphere() with:
​ 	      | material.color     | (0.8, 1.0, 0.6)        |
​ 	      | material.diffuse   | 0.7                    |
​ 	      | material.specular  | 0.2                    |
​ 	 Shape #2 = Sphere() with:
​ 	      | transform | scaling(0.5, 0.5, 0.5) |
*/
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