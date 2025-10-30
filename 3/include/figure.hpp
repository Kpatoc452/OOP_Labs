#pragma once

#include <iostream>

namespace figure {

const double EPS = 1e-9;

struct Point {
    double x, y;
    
    Point();
    Point(double _x, double _y);
};

bool operator==(const Point& val1, const Point& val2);
bool operator!=(const Point& val1, const Point& val2);
std::ostream& operator<<(std::ostream& stream, const Point& point);
std::istream& operator>>(std::istream& stream, Point& point);

class Figure {
    friend std::ostream& operator<<(std::ostream& stream, const Figure& fig);
public:
    virtual Point Center() const = 0;
    virtual double Area() const = 0;
    virtual void Print(std::ostream& stream) const = 0;
    virtual operator double() = 0;
    virtual ~Figure() = default;
};

std::ostream& operator<<(std::ostream& stream, const Figure& fig);

}
