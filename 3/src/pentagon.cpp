#include "pentagon.hpp"
#include <cmath>
#include <algorithm>

namespace figure {

Pentagon::Pentagon() 
    : points{{1.0, 0.0}, {0.309, 0.951}, {-0.809, 0.588}, {-0.809, -0.588}, {0.309, -0.951}} {}

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5) 
    : points{p1, p2, p3, p4, p5} {}

Pentagon::~Pentagon() {}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this == &other) return *this;
    std::copy(other.points, other.points + 5, points);
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) {
    if (this == &other) return *this;
    std::copy(other.points, other.points + 5, points);
    return *this;
}

Point Pentagon::Center() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 5; i++) {
        cx += points[i].x;
        cy += points[i].y;
    }
    return Point(cx / 5, cy / 5);
}

double Pentagon::Area() const {
    double sum = 0;
    for (int i = 0; i < 5; i++) {
        int next = (i + 1) % 5;
        sum += points[i].x * points[next].y - points[next].x * points[i].y;
    }
    return fabs(sum) / 2;
}

Pentagon::operator double() {
    return Area();
}

void Pentagon::Print(std::ostream& stream) const {
    stream << "pentagon\n";
    for (int i = 0; i < 5; i++) {
        stream << points[i];
        if (i < 4) stream << ", ";
    }
}

Point Pentagon::GetVertex(int idx) const {
    if (idx < 0 || idx >= 5) throw std::out_of_range("invalid vertex index");
    return points[idx];
}

bool Pentagon::IsValid() const {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (points[i] == points[j]) return false;
        }
    }
    return true;
}

bool operator==(const Pentagon& a, const Pentagon& b) {
    for (int i = 0; i < 5; i++) {
        if (fabs(a.points[i].x - b.points[i].x) > EPS || 
            fabs(a.points[i].y - b.points[i].y) > EPS) return false;
    }
    return true;
}

bool operator!=(const Pentagon& a, const Pentagon& b) {
    return !(a == b);
}

std::istream& operator>>(std::istream& stream, Pentagon& pent) {
    for (int i = 0; i < 5; i++) stream >> pent.points[i];
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Pentagon& pent) {
    pent.Print(stream);
    return stream;
}

}
