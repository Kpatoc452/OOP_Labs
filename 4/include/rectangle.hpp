#pragma once

#include "figure.hpp"
#include <memory>
#include <stdexcept>

namespace figure {

template<Scalar T>
class Rectangle : public Figure<T> {
    std::unique_ptr<Point<T>> points[RECTANGLE_ANGLES];

public:
    Rectangle();
    Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) = default;
    ~Rectangle() = default;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) = default;
    operator double() const override;

    Point<T> Center() const override;
    double Area() const override;
    Point<T> GetVertex(size_t idx) const;
    bool IsValid() const;

    template<Scalar U>
    friend bool operator==(const Rectangle<U>& a, const Rectangle<U>& b);

    template<Scalar U>
    friend bool operator!=(const Rectangle<U>& a, const Rectangle<U>& b);

    template<Scalar U>
    friend std::istream& operator>>(std::istream& stream, Rectangle<U>& rect);

    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& stream, const Rectangle<U>& rect);
};

template<Scalar T>
bool operator==(const Rectangle<T>& a, const Rectangle<T>& b);

template<Scalar T>
bool operator!=(const Rectangle<T>& a, const Rectangle<T>& b);

template<Scalar T>
std::istream& operator>>(std::istream& stream, Rectangle<T>& rect);

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Rectangle<T>& rect);

}

#include "rectangle.ipp"
