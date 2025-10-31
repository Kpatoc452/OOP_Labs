#include "trapezoid.hpp"

#include <cmath>

namespace figure {

Trapezoid::Trapezoid() : points{{0, 0}, {1, 0}, {1, 1}, {0, 1}} {}

Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : points{p1, p2, p3, p4} {}

Trapezoid::~Trapezoid() {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        points[i] = other.points[i];
    }

    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        points[i] = std::move(other.points[i]);
    }

    return *this;
}

Point Trapezoid::Center() const {
    double cx = 0, cy = 0;

    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        cx += points[i].x;
        cy += points[i].y;
    }

    return Point(cx / TRAPEZOID_ANGLES, cy / TRAPEZOID_ANGLES);
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
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        stream << points[i];
        if (i < TRAPEZOID_ANGLES - 1) {
            stream << ", ";
        }
    }
}

Point Trapezoid::GetVertex(int idx) const {
    if (idx < 0 || idx >= TRAPEZOID_ANGLES) {
        throw std::out_of_range("invalid vertex index");
    }
    return points[idx];
}

/*
bool Trapezoid::Validate(Point p1, Point p2, Point p3, Point p4) const {
    Point points_arr[TRAPEZOIDANGLES] = {p1, p2, p3, p4};
    for (size_t i = 0; i != TRAPEZOIDANGLES; ++i) {
        for (size_t j = i + 1; j != TRAPEZOIDANGLES; ++j) {
            if (points_arr[i] == points_arr[j]) {
                return false;
            }
        }
    }
    double vec1_x = p2.x - p1.x; 
    double vec1_y = p2.y - p1.y;
    double vec2_x = p4.x - p3.x;
    double vec2_y = p4.y - p3.y;
    double cross = vec1_x * vec2_y - vec1_y * vec2_x;

    double vec3_x = p3.x - p2.x;
    double vec3_y = p3.y - p2.y;
    double vec4_x = p1.x - p4.x;
    double vec4_y = p1.y - p4.y;
    double cross2 = vec3_x * vec4_y - vec3_y * vec4_x;

    bool is_sides_parallel = (std::fabs(cross) < EPS) || (std::fabs(cross2) < EPS);
    double base1 = Distance(p1, p2);
    double base2 = Distance(p3, p4);
    double height = std::fabs(p1.y - p3.y);
    double temp_area = 0.5 * (base1 + base2) * height;

    return is_sides_parallel && temp_area > EPS;
}
*/
bool Trapezoid::IsValid() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (points[i] == points[j]) return false;
        }
    }
    
    double vec1_x = points[1].x - points[0].x;
    double vec1_y = points[1].y - points[0].y;
    double vec2_x = points[3].x - points[2].x;
    double vec2_y = points[3].y - points[2].y;
    double cross1 = vec1_x * vec2_y - vec1_y * vec2_x;
    
    double vec3_x = points[2].x - points[1].x;
    double vec3_y = points[2].y - points[1].y;
    double vec4_x = points[0].x - points[3].x;
    double vec4_y = points[0].y - points[3].y;
    double cross2 = vec3_x * vec4_y - vec3_y * vec4_x;
    
    bool is_parallel = (fabs(cross1) < EPS) || (fabs(cross2) < EPS);
    
    double base1 = Distance(points[0], points[1]);
    double base2 = Distance(points[2], points[3]);
    double height = fabs(points[0].y - points[2].y);
    double area = 0.5 * (base1 + base2) * height;
    
    return is_parallel && area > EPS;
}


bool operator==(const Trapezoid& a, const Trapezoid& b) {
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
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
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        stream >> trap.points[i];
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Trapezoid& trap) {
    trap.Print(stream);
    return stream;
}

}
