#ifndef MATERIAL_H
#define MATERIAL_H

#include "colour.h"

#include <stdexcept>

static const double DEFAULT_AMBIENCE = 0.1;
static const double DEFAULT_DIFFUSE = 0.9;
static const double DEFAULT_SPECULAR = 0.9;
static const double DEFAULT_SHININESS = 200.0;
static const Colour DEFAULT_COLOUR = Colour(1, 1, 1);

class Material {
public:
    Material()
        : ambient(DEFAULT_AMBIENCE),
          diffuse(DEFAULT_DIFFUSE),
          specular(DEFAULT_SPECULAR),
          shininess(DEFAULT_SHININESS),
          colour(DEFAULT_COLOUR) { }

    Material(double ambient, double diffuse, double specular, double shininess, const Colour& c)
        : ambient(ambient),
          diffuse(diffuse),
          specular(specular),
          shininess(shininess),
          colour(c) {
            if (ambient < 0) {
                throw std::invalid_argument("Material ambience must be non-negative");
            }
            if (diffuse < 0) {
                throw std::invalid_argument("Material diffuseness must be non-negative");
            }
            if (specular < 0) {
                throw std::invalid_argument("Material specular reflection parameter must be non-negative");
            }
            if (shininess < 0) {
                throw std::invalid_argument("Material shininess must be non-negative");
            }
        }

    double ambient, diffuse, specular, shininess;
    Colour colour;
};

#endif // MATERIAL_H