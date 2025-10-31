#include "rhombus.hpp"

#include <cmath>

namespace figure {

Rhombus::Rhombus() : points{{0, 0}, {1, 0}, {1, 1}, {0, 1}} {}

Rhombus::Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : points{p1, p2, p3, p4} {}

Rhombus::~Rhombus() {}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < RHOMBUS_ANGLES; i++) {
        points[i] = other.points[i];
    }
    
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) {
    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < RHOMBUS_ANGLES; i++) {
        points[i] = std::move(other.points[i]);
    }

    return *this;
}

Rhombus::operator double() {
    return Area();
}

Point Rhombus::Center() const {
    double cx = 0, cy = 0;

    for (size_t i = 0; i < RHOMBUS_ANGLES; i++) {
        cx += points[i].x;
        cy += points[i].y;
    }

    return Point(cx / RHOMBUS_ANGLES, cy / RHOMBUS_ANGLES);
}

double Rhombus::Area() const {
    double diag1 = sqrt(pow(points[2].x - points[0].x, 2) + pow(points[2].y - points[0].y, 2));
    double diag2 = sqrt(pow(points[3].x - points[1].x, 2) + pow(points[3].y - points[1].y, 2));
    
    return diag1 * diag2 * 0.5;
}

Point Rhombus::GetVertex(int idx) const {
    if (idx < 0 || idx >= RHOMBUS_ANGLES) {
        throw std::out_of_range("invalid vertex index");
    }

    return points[idx];
}

void Rhombus::Print(std::ostream& stream) const {
    stream << "rhombus\n";

    for (size_t i = 0; i < RHOMBUS_ANGLES; i++) {
        stream << points[i];

        if (i < RHOMBUS_ANGLES - 1) {
            stream << ", ";
        }
    }
}

bool Rhombus::IsValid() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (points[i] == points[j]) return false;
        }
    }
    
    double sides[4];
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        sides[i] = Distance(points[i], points[next]);
    }
    
    for (int i = 1; i < 4; ++i) {
        if (fabs(sides[i] - sides[0]) > EPS) return false;
    }
    
    double area = Area();
    return area > EPS;
}


bool operator==(const Rhombus& a, const Rhombus& b) {
    for (size_t i = 0; i < RHOMBUS_ANGLES; i++) {
        if (fabs(a.points[i].x - b.points[i].x) > EPS || 
            fabs(a.points[i].y - b.points[i].y) > EPS) {
                return false;
            }
    }

    return true;
}

bool operator!=(const Rhombus& a, const Rhombus& b) {
    return !(a == b);
}

std::istream& operator>>(std::istream& stream, Rhombus& rh) {
    for (size_t i = 0; i < RHOMBUS_ANGLES; i++) {
        stream >> rh.points[i];
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Rhombus& rh) {
    rh.Print(stream);
    return stream;
}

}
