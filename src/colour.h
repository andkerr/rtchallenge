#ifndef COLOUR_H
#define COLOUR_H

#include "double.h"

#include <iostream>

class Colour {
public:
    Colour()
        : r(0), g(0), b(0) { }

    Colour(double r, double g, double b)
        : r(r), g(g), b(b) { }

    Colour(const Colour& c)
        : r(c.r), g(c.g), b(c.b) { }

    bool operator==(const Colour &rhs) const {
        return (doubleEqual(r, rhs.r) &&
                doubleEqual(g, rhs.g) &&
                doubleEqual(b, rhs.b));
    }

    Colour operator+(const Colour &rhs) const {
        return Colour(r + rhs.r,
                      g + rhs.g,
                      b + rhs.b);
    }

    Colour operator-(const Colour &rhs) const {
        return Colour(r - rhs.r,
                      g - rhs.g,
                      b - rhs.b);
    }

    Colour operator*(double s) const {
        return Colour(r * s, g * s, b * s);
    }

    Colour operator*(const Colour &rhs) const {
        return Colour(r * rhs.r,
                      g * rhs.g,
                      b * rhs.b);
    }

    // Colour public data
    double r, g, b;
};

std::ostream& operator<<(std::ostream& os, const Colour& c);

#endif // COLOUR_H