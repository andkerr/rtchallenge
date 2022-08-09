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

    over_point = point + v_normal * EPSILON;
}

std::vector<Intersection> World::intersect(const Ray& r) const {
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

bool World::is_shadowed(const Point& p) const {
    Vector v_light = Vector(light->position - p);
    double distance_to_light = Vector(light->position - p).magnitude();
    Vector dir_light = v_light.normalize();

    Ray ray_to_light(p, dir_light);

    std::vector<Intersection> isections = intersect(ray_to_light);
    Intersection hit;
    bool has_hit = find_hit(isections, hit);
    if (has_hit && (hit.t < distance_to_light)) {
        return true;
    }
    else {
        return false;
    }
}

Colour World::shade_hit(const IntersectionComps& icomps) const {
    bool in_shadow = is_shadowed(icomps.over_point);

    return lighting(icomps.obj->material,
                    light.get(),
                    icomps.over_point,
                    icomps.v_eye,
                    icomps.v_normal,
                    in_shadow);
}

Colour World::colour_at(const Ray& r) const {
    std::vector<Intersection> isections = intersect(r);

    Intersection hit;
    if (!find_hit(isections, hit)) {
        return Colour(0, 0, 0);
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