#include "shape.h"
#include "shapes/sphere.h"

struct QuadraticCoeffs {
    double a, b, c;
};

static void compute_quadratic_coeffs(const Ray& r, const Sphere& s, QuadraticCoeffs& coeffs) {
    Vector center_to_origin = r.origin - s.center;
    coeffs.a = r.direction.magnitudeSquared();
    coeffs.b = 2 * r.direction.dot(center_to_origin);
    coeffs.c = center_to_origin.magnitudeSquared() - (s.radius * s.radius);
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
        solns.push_back(Intersection(t1, create_sphere(center, radius)));
        solns.push_back(Intersection(t2, create_sphere(center, radius)));
        return true;
    }
}

std::shared_ptr<Shape> create_sphere(const Point& center, double radius) {
    return std::make_shared<Sphere>(center, radius);
}