#ifndef PATTERN_H
#define PATTERN_H

#include "colour.h"
#include "geometry.h"
#include "transform.h"

#include <stdexcept>

namespace Pattern {

class Pattern {
public:
    Pattern() = default;

    Pattern(const Matrix4x4& transform)
        : transform(transform) { }

    virtual Colour at(const Point& p) const = 0;

    // Public Pattern data
    const Matrix4x4 transform;
};

class Stripe : public Pattern {
public:
    Stripe(const Colour& c1, const Colour& c2, int axis = 0)
        : Pattern(), c1(c1), c2(c2), axis(axis) {
            if (!(0 <= axis && axis <= 2)) {
                throw std::invalid_argument("Stripe axis must be in the range [0, 2]");
            }
        }

    Stripe(const Colour& c1,
           const Colour& c2,
           const Matrix4x4& transform,
           int axis = 0)
        : Pattern(transform), c1(c1), c2(c2), axis(axis) {
            if (!(0 <= axis && axis <= 2)) {
                throw std::invalid_argument("Stripe axis must be in the range [0, 2]");
            }
        }

    Colour at(const Point& p) const override;

    // Public Stripe pattern data
    int axis;
    Colour c1, c2;
};

}; // namespace Pattern

#endif // PATTERN_H