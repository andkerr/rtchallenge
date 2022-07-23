#ifndef CANVAS_H
#define CANVAS_H

#include "colour.h"

#include <cassert>
#include <iostream>
#include <memory>

class Canvas {
public:
    Canvas(int width, int height)
        : width(width), height(height) {
            pixels = std::unique_ptr<Colour[]>(new Colour[width * height]);
        }

    Canvas(int width, int height, const Colour &c)
        : width(width), height(height) {
            pixels = std::unique_ptr<Colour[]>(new Colour[width * height]);
            for (int offset = 0; offset < width * height; ++offset) {
                pixels[offset] = c;
            }
    }

    Colour get_pixel(int x, int y) const {
        int offset = width * y + x;
        return pixels[offset];
    }

    void set_pixel(int x, int y, const Colour &c) {
        int offset = width * y + x;
        pixels[offset] = c;
    }

    int size() const {
        return width * height;
    }

    void to_ppm(std::ostream &os);

private:
    // Private Canvas data
    std::unique_ptr<Colour[]> pixels;
    
    int width, height;

    void check_bounds(int x, int y) {
        assert(0 <= x && x < width);
        assert(0 <= y && y < height);
    }
};

#endif // CANVAS_H