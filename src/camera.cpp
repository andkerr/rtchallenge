#include "camera.h"
#include "transform.h"

#include <cmath>

void Camera::compute_pixel_size(int width_px, int height_px, double field_of_view) {
    // assume Cameras are positioned 1 world unit in front of their canvases
    double half_view = tan(field_of_view / 2);
    double aspect = static_cast<double>(width_px) / height_px;

    double width_wu, height_wu; // wu - world units
    if (width_px >= height_px) {
        half_width_wu = half_view;
        half_height_wu = half_view / aspect;

        width_wu = 2 * half_view;
        height_wu = width_wu / aspect;
    }
    else {
        half_height_wu = half_view;
        half_width_wu = half_view * aspect;
        
        height_wu = 2 * half_view;
        width_wu = height_wu * aspect;
    }

    pixel_size = width_wu / width_px;
}

Camera::Camera(int canvas_w, int canvas_h, double field_of_view)
    : canvas_w(canvas_w), canvas_h(canvas_h), field_of_view(field_of_view), transform(Matrix4x4()) {
        compute_pixel_size(canvas_w, canvas_h, field_of_view);
}

Camera::Camera(int canvas_w, int canvas_h, double field_of_view, Matrix4x4 transform)
    : canvas_w(canvas_w), canvas_h(canvas_h), field_of_view(field_of_view), transform(transform) {
        compute_pixel_size(canvas_w, canvas_h, field_of_view);
}

Camera::Camera(int canvas_w, int canvas_h, double field_of_view,
               const Point& from, const Point& to, const Vector& up)
                : canvas_w(canvas_w), canvas_h(canvas_h), field_of_view(field_of_view) {
    compute_pixel_size(canvas_w, canvas_h, field_of_view);
    transform = view_transformation(from, to, up);
}

Ray Camera::ray_for(int x_px, int y_px) {
    double offset_x = (x_px + 0.5) * pixel_size;
    double offset_y = (y_px + 0.5) * pixel_size;

    // For an untransformed view, +x points left
    double world_x = half_width_wu - offset_x;
    double world_y = half_height_wu - offset_y;

    // Canvas is at z = -1
    Point pixel = transform.inverse().mul(Point(world_x, world_y, -1));
    Point origin = transform.inverse().mul(Point(0, 0, 0));
    Vector direction = Vector(pixel - origin).normalize();

    return Ray(origin, direction);
}

Canvas render(const std::shared_ptr<World> w) {

}

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