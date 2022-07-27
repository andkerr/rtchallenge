#include "geometry.h"
#include "transform.h"
#include "canvas.h"

#include <fstream>
using std::ofstream;

#include <iostream>
using std::cout;

#include <vector>
using std::vector;

int main() {
    const int clock_radius = 225;
    const int canvas_w = 500;
    const int canvas_h = 500;

    Canvas canvas(canvas_w, canvas_h);
    Colour visited(1, 1, 1);

    vector<Point> points;
    int n_points = 12;
    for (int i = 0; i < n_points; ++i) {
        Point p(clock_radius, 0, 0);
        Matrix4x4 A = Transform::rotate_z(i * 2 * M_PI / n_points);
        Matrix4x4 B = Transform::translate(canvas_w / 2, canvas_h / 2, 0);
        Matrix4x4 tot = B.mul(A);
        p = tot.mul(p);

        canvas.set_pixel(p.x, p.y, visited);
        points.push_back(p);
    }

    ofstream fout("clock.ppm");
    if (!fout.is_open()) {
        cout << "Error opening file\n";
        return 1;
    }
    canvas.to_ppm(fout);
}