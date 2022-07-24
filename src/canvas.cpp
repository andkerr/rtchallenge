#include "canvas.h"

static const int COLOUR_MAX = 255;

static int scale(double val, int min, int max) {
    if (val <= 0) {
        return 0;
    }
    else if (val >= 1) {
        return max;
    }
    else {
        return int(val * max);
    }
}

// TODO: I might need to implemet line wrapping at 70 characters
void Canvas::to_ppm(std::ostream& os) {
    os << "P3" << "\n"
       << width << " " << height << "\n"
       << COLOUR_MAX << "\n";

    Colour p;
    int r_scaled, g_scaled, b_scaled;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            p = get_pixel(x, y);
            r_scaled = scale(p.r, 0, COLOUR_MAX);
            g_scaled = scale(p.g, 0, COLOUR_MAX);
            b_scaled = scale(p.b, 0, COLOUR_MAX);

            os << r_scaled << " " << g_scaled << " " << b_scaled << " ";
        }
        os << "\n";
    }
}