#include "geometry.h"

#include <iostream>

Vector reflect(const Vector& v_in, const Vector& normal) {
    return v_in - normal * normal.dot(v_in) * 2;
}

std::ostream &operator<<(std::ostream& os, const Tuple& t) {
    os << (t.is_point() ? "Point( " : "Vector(")
       << t.x << ", "
       << t.y << ", "
       << t.z << ")";
    return os;
}