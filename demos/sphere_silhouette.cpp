#include "canvas.h"
#include "sphere.h"
#include "shape.h"
#include "transform.h"

#include <fstream>
#include <vector>

int main() {
    int canvas_size = 200;
    int wall_size = 10;

    Canvas canvas(canvas_size, canvas_size);
    Colour red(1, 0, 0);

    double pixel_size = (double) wall_size / canvas_size;

    Matrix4x4 transform = Transform::translate(wall_size / 2., wall_size / 2., 10);
    std::shared_ptr<Shape> s = create_sphere(transform, 1);

    Point ray_origin = Point(wall_size / 2, wall_size / 2, 15);
    for (int y = 0; y < canvas_size; ++y) {
        for (int x = 0; x < canvas_size; ++x) {
            double world_x = (double) x * pixel_size;
            double world_y = (double) y * pixel_size;

            Vector ray_dir = Point(world_x, world_y, 0) - ray_origin;
            ray_dir = ray_dir.normalize();
            Ray ray(ray_origin, ray_dir);

            std::vector<Intersection> solns;
            if (s->intersects(ray, solns)) {
                canvas.set_pixel(x, y, red);
            }
        }
    }

    std::ofstream fout("silhouette.ppm");
    canvas.to_ppm(fout);
}