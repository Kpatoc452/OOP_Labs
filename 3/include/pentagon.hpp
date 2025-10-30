#pragma once
#include "figure.hpp"

namespace figure {

class Pentagon : public Figure {
    friend bool operator==(const Pentagon& a, const Pentagon& b);
    friend bool operator!=(const Pentagon& a, const Pentagon& b);
    friend std::istream& operator>>(std::istream& stream, Pentagon& pent);
    friend std::ostream& operator<<(std::ostream& stream, const Pentagon& pent);
    
    Point points[5];
    
public:
    Pentagon();
    Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);
    Pentagon(const Pentagon& other) = default;
    Pentagon(Pentagon&& other) = default;
    ~Pentagon();
    
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other);
    operator double() override;
    
    void Print(std::ostream& stream) const override;
    Point Center() const override;
    double Area() const override;
    Point GetVertex(int idx) const;
    bool IsValid() const;
};

bool operator==(const Pentagon& a, const Pentagon& b);
bool operator!=(const Pentagon& a, const Pentagon& b);
std::istream& operator>>(std::istream& stream, Pentagon& pent);
std::ostream& operator<<(std::ostream& stream, const Pentagon& pent);

}
