#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"

#define _USE_MATH_DEFINES // PI
#include <cmath>

namespace Transform {

    Matrix4x4 translate(double x, double y, double z);

    Matrix4x4 scale(double x, double y, double z);

    Matrix4x4 rotate_x(double rads);
    Matrix4x4 rotate_y(double rads);
    Matrix4x4 rotate_z(double rads);

    // Does it make sense to swap the y* args here?
    // For me, this connotes "wrapping" x -> y -> z
    Matrix4x4 shear(double xy, double xz,
                    double yx, double yz,
                    double zx, double zy);

}; // namespace Transform

#endif //TRANSFORM_H