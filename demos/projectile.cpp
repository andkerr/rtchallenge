#include "canvas.h"
#include "colour.h"
#include "geometry.h"

#include <fstream>
#include <iostream>

using namespace std;


int main() {
    Point pos(0, 0, 0);
    Vector velocity(1.65, 6, 0);
    const Vector gravity(0, -0.05, 0);

    Canvas canvas(400, 400);
    Colour visited(0, 0, 1);

    int x_in = pos.x;
    int y_in = canvas.get_width() - pos.y - 1;

    canvas.set_pixel(x_in, y_in, visited);

    for (int i = 0; i < 250; ++i) {
        pos += velocity;
        velocity += gravity;

        x_in = pos.x;
        y_in = canvas.get_width() - pos.y - 1;

        canvas.set_pixel(x_in, y_in, visited);
    }

    ofstream fout("trajectory.ppm");
    if (!fout.is_open()) {
        cout << "Unable to open file\n";
        return -1;
    }

    canvas.to_ppm(fout);
}