#ifndef DOUBLE_H
#define DOUBLE_H

static constexpr double EPSILON = 0.0001;

bool doubleEqual(double l, double r, double e = EPSILON);

#endif // DOUBLE_H