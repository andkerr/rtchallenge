#include "double.h"

#include <cmath>

bool doubleEqual(double l, double r, double e) {
    return abs(l - r) < e;
}