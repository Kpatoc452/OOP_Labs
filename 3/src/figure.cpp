#include "figure.hpp"

#include <cmath>

namespace figure {

Point::Point() : x(0), y(0) {}
Point::Point(double _x, double _y) : x(_x), y(_y) {}

bool operator==(const Point& val1, const Point& val2) {
    return fabs(val1.x - val2.x) < EPS && fabs(val1.y - val2.y) < EPS;
}

bool operator!=(const Point& val1, const Point& val2) {
    return !(val1 == val2);
}

std::ostream& operator<<(std::ostream& stream, const Point& point) {
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

std::istream& operator>>(std::istream& stream, Point& point) {
    stream >> point.x >> point.y;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Figure& fig) {
    fig.Print(stream);
    return stream;
}

double Distance(const Point& a, const Point& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

}
