#include "trapezoid.hpp"
#include <cmath>

namespace figure {

Trapezoid::Trapezoid() : points{{0, 0}, {1, 0}, {1, 1}, {0, 1}} {}

Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : points{p1, p2, p3, p4} {}

Trapezoid::~Trapezoid() {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}

Point Trapezoid::Center() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 4; ++i) {
        cx += points[i].x;
        cy += points[i].y;
    }
    return Point(cx / 4.0, cy / 4.0);
}

double Trapezoid::Area() const {
    double b1 = sqrt(pow(points[1].x - points[0].x, 2) + pow(points[1].y - points[0].y, 2));
    double b2 = sqrt(pow(points[3].x - points[2].x, 2) + pow(points[3].y - points[2].y, 2));
    double h = fabs(points[0].y - points[2].y);
    return (b1 + b2) * h / 2.0;
}

Trapezoid::operator double() {
    return Area();
}

void Trapezoid::Print(std::ostream& stream) const {
    stream << "trapezoid\n";
    for (int i = 0; i < 4; ++i) {
        stream << points[i];
        if (i < 3) stream << ", ";
    }
}

Point Trapezoid::GetVertex(int idx) const {
    if (idx < 0 || idx >= 4) {
        throw std::out_of_range("invalid vertex index");
    }
    return points[idx];
}

bool Trapezoid::IsValid() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (points[i] == points[j]) return false;
        }
    }
    
    double s1 = (points[1].y - points[0].y) / (points[1].x - points[0].x);
    double s2 = (points[3].y - points[2].y) / (points[3].x - points[2].x);
    return fabs(s1 - s2) < EPS;
}

bool operator==(const Trapezoid& a, const Trapezoid& b) {
    for (int i = 0; i < 4; ++i) {
        if (fabs(a.points[i].x - b.points[i].x) > EPS || 
            fabs(a.points[i].y - b.points[i].y) > EPS) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Trapezoid& a, const Trapezoid& b) {
    return !(a == b);
}

std::istream& operator>>(std::istream& stream, Trapezoid& trap) {
    for (int i = 0; i < 4; ++i) {
        stream >> trap.points[i];
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Trapezoid& trap) {
    trap.Print(stream);
    return stream;
}

}
