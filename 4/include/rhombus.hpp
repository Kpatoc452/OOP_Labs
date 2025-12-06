#pragma once

#include "figure.hpp"
#include <memory>
#include <stdexcept>

namespace figure {

template<Scalar T>
class Rhombus : public Figure<T> {
    std::unique_ptr<Point<T>> points[RHOMBUS_ANGLES];

public:
    Rhombus();
    Rhombus(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) = default;
    ~Rhombus() = default;

    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) = default;
    operator double() const override;

    Point<T> Center() const override;
    double Area() const override;
    Point<T> GetVertex(size_t idx) const;
    bool IsValid() const;

    template<Scalar U>
    friend bool operator==(const Rhombus<U>& a, const Rhombus<U>& b);

    template<Scalar U>
    friend bool operator!=(const Rhombus<U>& a, const Rhombus<U>& b);

    template<Scalar U>
    friend std::istream& operator>>(std::istream& stream, Rhombus<U>& rh);

    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& stream, const Rhombus<U>& rh);
};

template<Scalar T>
bool operator==(const Rhombus<T>& a, const Rhombus<T>& b);

template<Scalar T>
bool operator!=(const Rhombus<T>& a, const Rhombus<T>& b);

template<Scalar T>
std::istream& operator>>(std::istream& stream, Rhombus<T>& rh);

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Rhombus<T>& rh);

}

#include "rhombus.ipp"
