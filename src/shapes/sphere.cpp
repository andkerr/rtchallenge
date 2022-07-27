#include "shape.h"
#include "shapes/sphere.h"

struct QuadraticCoeffs {
    double a, b, c;
};

static void compute_quadratic_coeffs(const Ray& r, const Sphere& s, QuadraticCoeffs& coeffs) {
    Ray r_obj = r.transform(s.obj_to_world.inverse());
    Vector s_to_r = r_obj.origin - Point(0, 0, 0);
    coeffs.a = r_obj.direction.magnitudeSquared();
    coeffs.b = 2 * r_obj.direction.dot(s_to_r);
    coeffs.c = s_to_r.magnitudeSquared() - (s.radius * s.radius);
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