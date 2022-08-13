#include "camera.h"
#include "plane.h"
#include "sphere.h"
#include "transform.h"
#include "world.h"

#include <fstream>
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<Shape> floor = create_plane(Matrix4x4());
    floor->material.colour = Colour(1, 0.9, 0.9);
    floor->material.specular = 0;

    Matrix4x4 transform = Transform::translate(-0.5, 1, 0.5);
    std::shared_ptr<Shape> middle = create_sphere(transform, 1);
    // middle->material = Material();
    middle->material.colour = Colour(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;

    transform = Transform::translate(1.5, 0.5, -0.5)
           .mul(Transform::scale(0.5, 0.5, 0.5));
    std::shared_ptr<Shape> right = create_sphere(transform, 1);
    right->material.colour = Colour(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;

    transform = Transform::translate(-1.5, 0.33, -0.75)
           .mul(Transform::scale(0.33, 0.33, 0.33));
    std::shared_ptr<Shape> left = create_sphere(transform, 1);
    left->material.colour = Colour(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    
    World w;
    w.light = std::make_shared<Light>(PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));
    w.add_shape(floor);
    w.add_shape(left);
    w.add_shape(middle);
    w.add_shape(right);

    Camera c(500, 250, M_PI / 3);
    c.transform = view_transformation(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

    Canvas img = c.render(std::make_shared<World>(w));

    std::ofstream fout("plane_demo.ppm");
    if (!fout.is_open()) {
        std::cout << "error opening file\n";
    }

    img.to_ppm(fout);

    fout.close();
}