#include "geometry.h"

#include <iostream>

std::ostream &operator<<(std::ostream& os, const Tuple& t) {
    os << (t.is_point() ? "Point( " : "Vector(")
       << t.x << ", "
       << t.y << ", "
       << t.z << ")";
    return os;
}