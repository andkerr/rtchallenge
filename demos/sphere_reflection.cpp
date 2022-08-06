#include "canvas.h"
#include "light.h"
#include "sphere.h"
#include "shape.h"
#include "transform.h"

#include <fstream>
#include <iostream>
#include <vector>

int main() {
    int canvas_size = 400;
    int wall_size = 10;

    Canvas canvas(canvas_size, canvas_size);

    double pixel_size = (double) wall_size / canvas_size;

    Matrix4x4 transform = Transform::translate(wall_size / 2., wall_size / 2., 10);
    std::shared_ptr<Shape> s = create_sphere(transform, 1);
    s->material = Material(Colour(0.2, 0.4, 1));

    PointLight light(Point(0, 0, 15), Colour(1, 1, 1));

    Point ray_origin = Point(wall_size / 2, wall_size / 2, 15);
    for (int y = 0; y < canvas_size; ++y) {
        for (int x = 0; x < canvas_size; ++x) {
            double world_x = (double) x * pixel_size;
            double world_y = (double) y * pixel_size;

            Vector ray_dir = Point(world_x, world_y, 0) - ray_origin;
            ray_dir = ray_dir.normalize();
            Ray ray(ray_origin, ray_dir);

            std::vector<Intersection> solns;
            Intersection hit;
            if (s->intersects(ray, solns)) {
                find_hit(solns, hit);
                Point point_to_colour = ray_origin + ray_dir * hit.t;
                Vector normal = s->normal_at(point_to_colour);
                Vector camera = -ray_dir;
                Colour c = lighting(s->material, &light, point_to_colour, camera, normal);
                canvas.set_pixel(x, y, c);
            }
        }
    }

    std::ofstream fout("sphere_reflection.ppm");
    canvas.to_ppm(fout);
}