#ifndef LIGHT_H
#define LIGHT_H

#include "geometry.h"
#include "colour.h"

class Light {
public:
    Light() = default;

    Light(const Point& p, const Colour& i)
        : position(p), intensity(i) { }

    // Public Light data
    Point position;
    Colour intensity;
};

class PointLight : public Light {
public:
    PointLight() = default;

    PointLight(const Point& p, const Colour& i)
        : Light(p, i) { }
};

#endif // LIGHT_H