#include "pattern.h"

#include <cmath>
#include <vector>

namespace Pattern {

Colour Stripe::at(const Point& p) const {
    Point point = transform.inverse().mul(p);
    std::vector<double> coords = {point.x, point.y, point.z};
    if (int (floor(coords[axis])) % 2 == 0) {
        return c1;
    }
    else {
        return c2;
    }
}

Colour Gradient::at(const Point& p) const {
    Point point = transform.inverse().mul(p);
    Colour delta = c2 - c1;
    double fraction = point.x - floor(point.x);
    return c1 + delta * fraction;
}

Colour Ring::at(const Point& p) const {
    Point point = transform.inverse().mul(p);
    double distance = sqrt(point.x * point.x + point.z * point.z);
    if (int (floor(distance)) % 2 == 0) {
        return c1;
    }
    else {
        return c2;
    }
}

Colour Check3D::at(const Point& p) const {
    Point point = transform.inverse().mul(p);
    if (int (floor(point.x) + floor(point.y) + floor(point.z)) % 2 == 0) {
        return c1;
    }
    else {
        return c2;
    }
}

Colour CheckUV::at(double u, double v) const {
    assert(0 <= u && u <= 1);
    assert(0 <= v && v <= 1);

    int col = floor(u * ncols);
    int row = floor(v * nrows);

    if ((col + row) % 2 == 0) {
        return c1;
    }
    else {
        return c2;
    }
}

}; // namespace Pattern

std::pair<double, double> spherical_map(const Point& p) {
    Vector d = Vector(p - Point(0, 0, 0)).normalize();

    double u = 0.5 + atan2(d.x, d.z) / (2 * M_PI);
    double v = 0.5 + asin(d.y) / M_PI;

    return std::pair<double, double>(u, v);
}