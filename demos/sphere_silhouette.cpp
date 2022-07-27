#include "canvas.h"
#include "sphere.h"
#include "shape.h"
#include "transform.h"

#include <fstream>
#include <iostream>
#include <vector>

int main() {
    int canvas_size = 1000;
    int wall_size = 10;

    Canvas canvas(canvas_size, canvas_size);
    Colour red(1, 0, 0);

    double pixel_size = (double) wall_size / canvas_size;

    std::shared_ptr<Shape> s1 = create_sphere(Transform::translate(wall_size / 2., wall_size / 2., 0), 1);
    std::shared_ptr<Shape> s2 = create_sphere(Transform::translate(wall_size / 2. + 2, wall_size / 2., 0), 1);
    std::shared_ptr<Shape> s3 = create_sphere(Transform::translate(wall_size / 2. + 4, wall_size / 2., 0), 1);
    std::shared_ptr<Shape> s4 = create_sphere(Transform::translate(wall_size / 2. - 2, wall_size / 2., 0), 1);
    std::shared_ptr<Shape> s5 = create_sphere(Transform::translate(wall_size / 2. - 4, wall_size / 2., 0), 1);
    std::vector< std::shared_ptr<Shape>> spheres = {s1, s2, s3, s4, s5};

    Point ray_origin = Point(wall_size / 2, wall_size / 2, 15);
    for (int y = 0; y < canvas_size; ++y) {
        for (int x = 0; x < canvas_size; ++x) {
            double world_x = (double) x * pixel_size;
            double world_y = (double) y * pixel_size;

            if (world_x < 0 || world_y < 0) {
                std::cout << world_x << " " << world_y << "\n";
            }

            Vector ray_dir = Point(world_x, world_y, 0) - ray_origin;
            ray_dir = ray_dir.normalize();
            Ray ray(ray_origin, ray_dir);

            std::vector<Intersection> solns;
            for (const std::shared_ptr<Shape> s : spheres) {
                if (s->intersects(ray, solns)) {
                    canvas.set_pixel(x, y, red);
                }
            }
        }
    }

    std::ofstream fout("silhouette.ppm");
    canvas.to_ppm(fout);
}