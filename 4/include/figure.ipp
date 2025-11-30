#pragma once

#include "figure.hpp"

namespace figure {

template<Scalar T>
Point<T>::Point() : x(0), y(0) {}

template<Scalar T>
Point<T>::Point(T _x, T _y) : x(_x), y(_y) {}

template<Scalar T>
bool operator==(const Point<T>& val1, const Point<T>& val2) {
    if constexpr (std::is_floating_point_v<T>) {
        return std::fabs(val1.x - val2.x) < EPS && std::fabs(val1.y - val2.y) < EPS;
    } else {
        return val1.x == val2.x && val1.y == val2.y;
    }
}

template<Scalar T>
bool operator!=(const Point<T>& val1, const Point<T>& val2) {
    return !(val1 == val2);
}

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& point) {
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

template<Scalar T>
std::istream& operator>>(std::istream& stream, Point<T>& point) {
    stream >> point.x >> point.y;
    return stream;
}

template<Scalar T>
double Distance(const Point<T>& a, const Point<T>& b) {
    double dx = static_cast<double>(a.x - b.x);
    double dy = static_cast<double>(a.y - b.y);
    return std::sqrt(dx * dx + dy * dy);
}

}
