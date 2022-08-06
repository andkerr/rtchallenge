#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "matrix.h"

class Camera {

};

Matrix4x4 view_transformation(const Point& from, const Point& to, const Vector& up);

#endif // CAMERA_H