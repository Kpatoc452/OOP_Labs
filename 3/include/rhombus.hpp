#pragma once

#include "figure.hpp"

namespace figure {

class Rhombus : public Figure {
    friend bool operator==(const Rhombus& a, const Rhombus& b);
    friend bool operator!=(const Rhombus& a, const Rhombus& b);
    friend std::istream& operator>>(std::istream& stream, Rhombus& rh);
    friend std::ostream& operator<<(std::ostream& stream, const Rhombus& rh);
    
    Point points[4];
    
public:
    Rhombus();
    Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Rhombus(const Rhombus& other) = default;
    Rhombus(Rhombus&& other) = default;
    ~Rhombus();
    
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other);
    operator double() override;

    Point Center() const override;
    double Area() const override;
    Point GetVertex(int idx) const;
    bool IsValid() const;
};

bool operator==(const Rhombus& a, const Rhombus& b);
bool operator!=(const Rhombus& a, const Rhombus& b);
std::istream& operator>>(std::istream& stream, Rhombus& rh);
std::ostream& operator<<(std::ostream& stream, const Rhombus& rh);

}
