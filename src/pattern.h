#ifndef PATTERN_H
#define PATTERN_H

#include "colour.h"

#include <vector>

namespace Pattern {

class Pattern {
public:
    Pattern(const std::vector<Colour>& colours)
        : colours(colours) { }

    virtual Colour at(const Point& p) const = 0;

    // Public pattern data
    std::vector<Colour> colours;
};

class StripeX : public Pattern {
public:
    StripeX(const std::vector<Colour>& colours)
        : Pattern(colours) { }

    Colour at(const Point& p) const override;
};

}; // namespace Pattern

#endif // PATTERN_H