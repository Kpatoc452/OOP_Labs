#pragma once

#include "figure.hpp"
#include <memory>
#include <stdexcept>

namespace figure {

template<Scalar T>
class Trapezoid : public Figure<T> {
    std::unique_ptr<Point<T>> points[TRAPEZOID_ANGLES];

public:
    Trapezoid();
    Trapezoid(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) = default;
    ~Trapezoid() = default;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) = default;
    operator double() const override;

    Point<T> Center() const override;
    double Area() const override;
    Point<T> GetVertex(size_t idx) const;
    bool IsValid() const;

    template<Scalar U>
    friend bool operator==(const Trapezoid<U>& a, const Trapezoid<U>& b);

    template<Scalar U>
    friend bool operator!=(const Trapezoid<U>& a, const Trapezoid<U>& b);

    template<Scalar U>
    friend std::istream& operator>>(std::istream& stream, Trapezoid<U>& trap);

    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& stream, const Trapezoid<U>& trap);
};

template<Scalar T>
bool operator==(const Trapezoid<T>& a, const Trapezoid<T>& b);

template<Scalar T>
bool operator!=(const Trapezoid<T>& a, const Trapezoid<T>& b);

template<Scalar T>
std::istream& operator>>(std::istream& stream, Trapezoid<T>& trap);

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Trapezoid<T>& trap);

}

#include "trapezoid.ipp"
