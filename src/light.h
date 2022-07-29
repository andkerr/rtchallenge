#ifndef LIGHT_H
#define LIGHT_H

#include "colour.h"
#include "geometry.h"
#include "material.h"

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

Colour lighting(const Material& m,
                const Light* light,
                const Point& pos,
                const Vector& camera,
                const Vector& normal);

#endif // LIGHT_H