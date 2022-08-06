#include "colour.h"

std::ostream& operator<<(std::ostream& os, const Colour& c) {
    os << "Colour( " << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}