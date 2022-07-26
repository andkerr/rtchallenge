#include "transform.h"

#include <exception>

Matrix4x4 Transform::translate(double x, double y, double z) {
    Matrix4x4 result;
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

Matrix4x4 Transform::scale(double x, double y, double z) {
    if (x == 0 || y == 0 || z == 0) {
        throw std::invalid_argument("Objects cannot be scaled by a factor of 0");
    }

    Matrix4x4 result;
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    return result;
}

Matrix4x4 Transform::rotate_x(double rads) {
    Matrix4x4 result;
    result.m[1][1] = cos(rads);
    result.m[1][2] = -sin(rads);
    result.m[2][1] = sin(rads);
    result.m[2][2] = cos(rads);
    return result;
}

Matrix4x4 Transform::rotate_y(double rads) {
    Matrix4x4 result;
    result.m[0][0] = cos(rads);
    result.m[0][2] = sin(rads);
    result.m[2][0] = -sin(rads);
    result.m[2][2] = cos(rads);
    return result;
}

Matrix4x4 Transform::rotate_z(double rads) {
    Matrix4x4 result;
    result.m[0][0] = cos(rads);
    result.m[0][1] = -sin(rads);
    result.m[1][0] = sin(rads);
    result.m[1][1] = cos(rads);
    return result;
}

Matrix4x4 Transform::shear(double xy, double xz,
                           double yx, double yz,
                           double zx, double zy) {
    Matrix4x4 result;
    result.m[0][1] = xy;
    result.m[0][2] = xz;
    result.m[1][0] = yx;
    result.m[1][2] = yz;
    result.m[2][0] = zx;
    result.m[2][1] = zy;
    return result;
}