#ifndef PATTERN_H
#define PATTERN_H

#include "colour.h"
#include "geometry.h"
#include "transform.h"

#include <stdexcept>
#include <utility> // pair

namespace Pattern {

class Pattern {
public:
    Pattern() = default;

    Pattern(const Matrix4x4& transform)
        : transform(transform) { }
    
    // Compute the Colour at a given point in a Pattern.
    // Patterns can be transformed themselves, and will convert
    // points to 'pattern space' before evaluating their colour,
    // but they have no concept of Shape, so all at()
    // functions assume that if they are evalulating a pattern
    // that is a applied to a Shape, the Point they are passed is
    // in the 'object' space of the Shape the Pattern is on.
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

class Gradient : public Pattern {
public:
    Gradient(const Colour& c1, const Colour& c2)
        : Pattern(), c1(c1), c2(c2) { }

    Gradient(const Colour& c1, const Colour& c2, const Matrix4x4& transform)
        : Pattern(transform), c1(c1), c2(c2) { }

    Colour at(const Point& p) const override;

    // Public Gradient data
    Colour c1, c2;
};

class Ring : public Pattern {
public:
    Ring(const Colour& c1, const Colour& c2)
        : Pattern(), c1(c1), c2(c2) { }

    Ring(const Colour& c1, const Colour& c2, const Matrix4x4& transform)
        : Pattern(transform), c1(c1), c2(c2) { }

    Colour at(const Point& p) const override;

    // Public Ring data
    Colour c1, c2;
};

class Check3D : public Pattern {
public:
    Check3D(const Colour& c1, const Colour& c2)
        : Pattern(), c1(c1), c2(c2) { }

    Check3D(const Colour& c1, const Colour& c2, const Matrix4x4& transform)
        : Pattern(transform), c1(c1), c2(c2) { }

    Colour at(const Point& p) const override;

    // Public Check3D data
    Colour c1, c2;
};

// Is this more of a helper class? It doesn't share some
// characteristics with Pattern...
class CheckUV {
public:
    CheckUV(int ncols, int nrows, const Colour& c1, const Colour& c2)
        : ncols(ncols), nrows(nrows), c1(c1), c2(c2) { }

    Colour at(double u, double v) const;

    // Public CheckUV data
    Colour c1, c2;
    int ncols, nrows;
};

}; // namespace Pattern

std::pair<double, double> spherical_map(const Point& p);

#endif // PATTERN_H