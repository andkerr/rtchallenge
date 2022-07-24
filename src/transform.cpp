#include "transform.h"

Matrix4x4 Transform::translate(double x, double y, double z) {
    Matrix4x4 result;
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

Matrix4x4 Transform::scale(double x, double y, double z);

Matrix4x4 Transform::rotate_x(double rads);
Matrix4x4 Transform::rotate_y(double rads);
Matrix4x4 Transform::rotate_z(double rads);

// Does it make sense to swap the y* args here?
// For me, this connotes "wrapping" x -> y -> z
Matrix4x4 Transform::shear(double xy, double xz,
                           double yx, double yz,
                           double zx, double zy);