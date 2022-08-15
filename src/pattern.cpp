#include "pattern.h"

#include <cmath>
#include <vector>

namespace Pattern {

Colour Stripe::at(const Point& p) const {
    std::vector<double> coords = {p.x, p.y, p.z};
    if (int (floor(coords[axis])) % 2 == 0) {
        return c1;
    }
    else {
        return c2;
    }
}

}; // namespace Pattern