#include "primitives.h"

#include <cmath>

static void compute_quadratic_coeffs(const Ray& r, const Sphere& s, QuadraticCoeffs& coeffs) {
    Vector center_to_origin = r.origin - s.center;
    coeffs.a = r.direction.magnitudeSquared();
    coeffs.b = 2 * r.direction.dot(center_to_origin);
    coeffs.c = center_to_origin.magnitudeSquared() - (s.radius * s.radius);
}

bool Ray::intersects(const Sphere& s, Intersection& solns) const {
    QuadraticCoeffs coeffs;
    compute_quadratic_coeffs(*this, s, coeffs);
    double discrim = coeffs.b*coeffs.b - 4*coeffs.a*coeffs.c;
    if (discrim < 0) {
        return false;
    }
    else {
        solns.t1 = (-coeffs.b - sqrt(discrim)) / (2*coeffs.a);
        solns.t2 = (-coeffs.b + sqrt(discrim)) / (2*coeffs.a);
        solns.obj = &s;
        return true;
    }
}