#pragma once

#include <iostream>
#include <memory>
#include <concepts>
#include <cmath>

namespace figure {

const double EPS = 1e-9;
constexpr const int PENTAGON_ANGLES = 5;
constexpr const int RHOMBUS_ANGLES = 4;
constexpr const int TRAPEZOID_ANGLES = 4;
constexpr const int RECTANGLE_ANGLES = 4;

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
struct Point {
    T x, y;

    Point();
    Point(T _x, T _y);

    Point(const Point& other) = default;
    Point(Point&& other) = default;
    Point& operator=(const Point& other) = default;
    Point& operator=(Point&& other) = default;
};

template<Scalar T>
bool operator==(const Point<T>& val1, const Point<T>& val2);

template<Scalar T>
bool operator!=(const Point<T>& val1, const Point<T>& val2);

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& point);

template<Scalar T>
std::istream& operator>>(std::istream& stream, Point<T>& point);

template<Scalar T>
double Distance(const Point<T>& a, const Point<T>& b);

template<Scalar T>
class Figure {
public:
    virtual Point<T> Center() const = 0;
    virtual double Area() const = 0;
    virtual operator double() const = 0;
    virtual ~Figure() = default;
};

}

#include "figure.ipp"
