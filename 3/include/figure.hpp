#pragma once

#include <iostream>

namespace figure {

const double EPS = 1e-9;
constexpr const int PENTAGON_ANGLES = 5;
constexpr const int RHOMBUS_ANGLES = 4;
constexpr const int TRAPEZOID_ANGLES = 4;

struct Point {
    double x, y;
    
    Point();
    Point(double _x, double _y);
};

bool operator==(const Point& val1, const Point& val2);
bool operator!=(const Point& val1, const Point& val2);
std::ostream& operator<<(std::ostream& stream, const Point& point);
std::istream& operator>>(std::istream& stream, Point& point);
double Distance(const Point& a, const Point& b);

class Figure {
public:
    virtual Point Center() const = 0;
    virtual double Area() const = 0;
    virtual operator double() = 0;
    virtual ~Figure() = default;
};
}
