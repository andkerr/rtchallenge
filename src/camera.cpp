#include "camera.h"
#include "transform.h"

Matrix4x4 view_transformation(const Point& from, const Point& to, const Vector& up) {
    Vector forward = Vector(to - from).normalize();
    Vector left = forward.cross(up.normalize());
    Vector true_up = left.cross(forward);
    Matrix4x4 result(left.x, left.y, left.z, 0,
                     true_up.x, true_up.y, true_up.z, 0,
                     -forward.x, -forward.y, -forward.z, 0,
                     0, 0, 0, 1);
    return result.mul(Transform::translate(-from.x, -from.y, -from.z));
}