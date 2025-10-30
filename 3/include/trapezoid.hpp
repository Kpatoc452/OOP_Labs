#pragma once
#include "figure.hpp"

namespace figure {

class Trapezoid : public Figure {
    friend bool operator==(const Trapezoid& a, const Trapezoid& b);
    friend bool operator!=(const Trapezoid& a, const Trapezoid& b);
    friend std::istream& operator>>(std::istream& stream, Trapezoid& trap);
    friend std::ostream& operator<<(std::ostream& stream, const Trapezoid& trap);
    
    Point points[4];
    
public:
    Trapezoid();
    Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Trapezoid(const Trapezoid& other) = default;
    Trapezoid(Trapezoid&& other) = default;
    ~Trapezoid();
    
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other);
    operator double() override;
    
    void Print(std::ostream& stream) const override;
    Point Center() const override;
    double Area() const override;
    Point GetVertex(int idx) const;
    bool IsValid() const;
};

bool operator==(const Trapezoid& a, const Trapezoid& b);
bool operator!=(const Trapezoid& a, const Trapezoid& b);
std::istream& operator>>(std::istream& stream, Trapezoid& trap);
std::ostream& operator<<(std::ostream& stream, const Trapezoid& trap);

}
