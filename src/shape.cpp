#include "shape.h"

bool find_hit(std::vector<Intersection>& solns, Intersection& hit) {
    double t_min_positive = -1;
    Intersection res;
    for (int i = 0; i < solns.size(); ++i) {
        if (solns[i].t > 0 && (t_min_positive < 0 || solns[i].t < t_min_positive)) {
            t_min_positive = solns[i].t;
            res = solns[i];
        }
    }

    if (t_min_positive > 0) {
        hit = res;
        return true;
    }
    else {
        return false;
    }
}

Colour Shape::pattern_at(const Point& p) const {
    if (material.pattern.get() == nullptr) {
        throw std::invalid_argument("This Shape does not have a pattern");
    }

    Point point = obj_to_world.inverse().mul(p);
    Point pattern_point = material.pattern->transform.inverse().mul(point);
    return material.pattern->at(pattern_point);
}