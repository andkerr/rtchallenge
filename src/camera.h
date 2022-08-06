#ifndef CAMERA_H
#define CAMERA_H

#include "canvas.h"
#include "geometry.h"
#include "matrix.h"
#include "shape.h"
#include "world.h"

#include <memory>

class Camera {
public:
    Camera(int canvas_w, int canvas_h, double field_of_view);

    Camera(int canvas_w, int canvas_h, double field_of_view, Matrix4x4 transform);

    Camera(int canvas_w, int canvas_h, double field_of_view,
           const Point& from, const Point& to, const Vector& up);

    Ray ray_for(int x_px, int y_px);

    Canvas render(const std::shared_ptr<World> w);

    // Public Camera data
    int canvas_w, canvas_h; // canvas size in screen pixels
    double pixel_size; // world units per pixel
    double field_of_view;
    Matrix4x4 transform;

private:
    void compute_pixel_size(int width_px, int height_px, double field_of_view);
    double half_width_wu, half_height_wu;
};

Matrix4x4 view_transformation(const Point& from, const Point& to, const Vector& up);

#endif // CAMERA_H