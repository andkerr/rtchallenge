#include "geometry.h"
#include "light.h"

Colour lighting(const Material& m,
                const Light* light,
                const Point& pos,
                const Vector& camera,
                const Vector& normal) {
    Colour c_effective, ambient, diffuse, specular;
    c_effective = m.colour * light->intensity;
    ambient = c_effective * m.ambient;

    Vector light_vec = Vector(light->position - pos).normalize();
    double light_dot_normal = light_vec.dot(normal);
    
    if (light_dot_normal < 0) {
        diffuse = Colour(0, 0, 0);
        specular = Colour(0, 0, 0);
    }
    else {
        diffuse = c_effective * m.diffuse * light_dot_normal;
        Vector reflection_vec = reflect(-light_vec, normal);
        double reflect_dot_camera = reflection_vec.dot(camera);

        if (reflect_dot_camera <= 0) {
            specular = Colour(0, 0, 0);
        }
        else {
            double factor = pow(reflect_dot_camera, m.shininess);
            specular = light->intensity * m.specular * factor;
        }
    }

    return Colour(ambient + diffuse + specular);
}