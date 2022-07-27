#include <iostream>
using std::cout;

#include <memory>

#include <string>
using std::string;

class Shape {
public:
    virtual string to_string() const = 0;
    virtual ~Shape() { }
};

class Sphere : public Shape {
public:
    Sphere(int x, int rad)
        : x(x), rad(rad) { }

    virtual string to_string() const override {
        string res = "Sphere(" + std::to_string(x) + ", " + std::to_string(rad) + ")";
        return res;
    }

    int x;
    int rad;
};

class Square : public Shape {
public:
    Square(int x, int side_len)
        : x(x), side_len(side_len) { }

    virtual string to_string() const override {
        string res = "Square(" + std::to_string(x) + ", " + std::to_string(side_len) + ")";
        return res;
    }

    int x;
    int side_len;
};

std::unique_ptr<Shape> create_sphere(int x, int rad) {
    return std::make_unique<Sphere>(x, rad);
}

struct Intersection {
    Intersection(int t, std::unique_ptr<Shape> s)
        : t(t), obj(std::move(s)) { }

    int t;
    std::unique_ptr<Shape> obj;
};

std::ostream& operator<<(std::ostream& os, const Shape& s) {
    os << s.to_string();
    return os;
}

int main() {
    Intersection i(2, create_sphere(2, 4));

    cout << i.t << ", " << *(i.obj) << "\n";
}