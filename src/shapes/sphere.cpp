#include "shape.h"
#include "shapes/sphere.h"

#include <exception>

struct QuadraticCoeffs {
    double a, b, c;
};

static bool quadratic_has_solns(double a, double b, double c, double &t1, double &t2) {
    double discrim = b*b - 4*a*c;
    if (discrim < 0) {
        return false;
    }
    else {
        t1 = (-b - sqrt(discrim)) / (2*a);
        t2 = (-b + sqrt(discrim)) / (2*a);
        return true;
    }
}

bool Sphere::intersects(const Ray& r, std::vector<Intersection>& solns) const {
    Matrix4x4 world_to_object = obj_to_world.inverse();

    Ray ray = r.transform(world_to_object);
    // Sphere located at origin in object space
    Vector sphere_to_ray = ray.origin - Point(0, 0, 0);
    double a = ray.direction.magnitudeSquared();
    double b = 2 * ray.direction.dot(sphere_to_ray);
    double c = sphere_to_ray.magnitudeSquared() - (radius * radius);

    double t1, t2;
    if (!quadratic_has_solns(a, b, c, t1, t2)) {
        return false;
    }
    else {
        solns.push_back(Intersection(t1, create_sphere(obj_to_world, radius)));
        solns.push_back(Intersection(t2, create_sphere(obj_to_world, radius)));
        return true;
    }
}

Vector Sphere::normal(const Point& p) const {
    Matrix4x4 world_to_obj = obj_to_world.inverse();
    Point p_object = world_to_obj.mul(p);
    Vector norm_obj = p_object - Point(0, 0, 0);
    Vector norm_world = world_to_obj.transpose().mul(norm_obj);
    norm_world.w = 0;
    return norm_world.normalize();
}

Vector Sphere::reflect(const Ray& r, const Point& p) const {
    Vector normal = Sphere::normal(p);
    return r.direction - normal * normal.dot(r.direction) * 2;
}

std::shared_ptr<Shape> create_sphere(const Matrix4x4& obj_to_world, double radius) {
    return std::make_shared<Sphere>(obj_to_world, radius);
}