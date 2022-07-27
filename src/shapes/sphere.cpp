#include "shape.h"
#include "shapes/sphere.h"

struct QuadraticCoeffs {
    double a, b, c;
};

static void compute_quadratic_coeffs(const Ray& r, const Sphere& s, QuadraticCoeffs& coeffs) {
    Ray r_object_space = r.transform(s.obj_to_world.inverse());
    // Sphere located at origin in object space
    Vector sphere_to_ray = r_object_space.origin - Point(0, 0, 0);
    coeffs.a = r_object_space.direction.magnitudeSquared();
    coeffs.b = 2 * r_object_space.direction.dot(sphere_to_ray);
    coeffs.c = sphere_to_ray.magnitudeSquared() - (s.radius * s.radius);
}

bool Sphere::intersects(const Ray& r, std::vector<Intersection>& solns) const {
    QuadraticCoeffs coeffs;
    compute_quadratic_coeffs(r, *this, coeffs);
    double discrim = coeffs.b*coeffs.b - 4*coeffs.a*coeffs.c;
    if (discrim < 0) {
        return false;
    }
    else {
        double t1 = (-coeffs.b - sqrt(discrim)) / (2*coeffs.a);
        double t2 = (-coeffs.b + sqrt(discrim)) / (2*coeffs.a);
        solns.push_back(Intersection(t1, create_sphere(obj_to_world, radius)));
        solns.push_back(Intersection(t2, create_sphere(obj_to_world, radius)));
        return true;
    }
}

std::shared_ptr<Shape> create_sphere(const Matrix4x4& obj_to_world, double radius) {
    return std::make_shared<Sphere>(obj_to_world, radius);
}