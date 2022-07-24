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
        assert(in_bounds(x, y));
        int offset = width * y + x;
        return pixels[offset];
    }

    void set_pixel(int x, int y, const Colour &c) {
        if (in_bounds(x, y)) {
            int offset = width * y + x;
            pixels[offset] = c;
        }
    }

    int size() const {
        return width * height;
    }

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }

    void to_ppm(std::ostream &os);

private:
    std::unique_ptr<Colour[]> pixels;
    
    int width, height;

    bool in_bounds(int x, int y) const {
        return (0 <= x && x < width &&
                0 <= y && y < height);
    }
};

#endif // CANVAS_H