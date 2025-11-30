#pragma once

#include "trapezoid.hpp"

namespace figure {

template<Scalar T>
Trapezoid<T>::Trapezoid() {
    points[0] = std::make_unique<Point<T>>(0, 0);
    points[1] = std::make_unique<Point<T>>(1, 0);
    points[2] = std::make_unique<Point<T>>(1, 1);
    points[3] = std::make_unique<Point<T>>(0, 1);
}

template<Scalar T>
Trapezoid<T>::Trapezoid(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    points[0] = std::make_unique<Point<T>>(p1);
    points[1] = std::make_unique<Point<T>>(p2);
    points[2] = std::make_unique<Point<T>>(p3);
    points[3] = std::make_unique<Point<T>>(p4);
}

template<Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid& other) {
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}

template<Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    return *this;
}

template<Scalar T>
Trapezoid<T>::operator double() const {
    return Area();
}

template<Scalar T>
Point<T> Trapezoid<T>::Center() const {
    T cx = 0, cy = 0;

    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        cx += points[i]->x;
        cy += points[i]->y;
    }

    return Point<T>(cx / TRAPEZOID_ANGLES, cy / TRAPEZOID_ANGLES);
}

template<Scalar T>
double Trapezoid<T>::Area() const {
    double b1 = Distance(*points[0], *points[1]);
    double b2 = Distance(*points[2], *points[3]);

    double h = std::fabs(static_cast<double>(points[0]->y - points[2]->y));

    return (b1 + b2) * h / 2.0;
}

template<Scalar T>
Point<T> Trapezoid<T>::GetVertex(int idx) const {
    if (idx < 0 || idx >= TRAPEZOID_ANGLES) {
        throw std::out_of_range("invalid vertex index");
    }

    return *points[idx];
}

template<Scalar T>
bool Trapezoid<T>::IsValid() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (*points[i] == *points[j]) return false;
        }
    }

    double vec1_x = static_cast<double>(points[1]->x - points[0]->x);
    double vec1_y = static_cast<double>(points[1]->y - points[0]->y);
    double vec2_x = static_cast<double>(points[3]->x - points[2]->x);
    double vec2_y = static_cast<double>(points[3]->y - points[2]->y);
    double cross1 = vec1_x * vec2_y - vec1_y * vec2_x;

    double vec3_x = static_cast<double>(points[2]->x - points[1]->x);
    double vec3_y = static_cast<double>(points[2]->y - points[1]->y);
    double vec4_x = static_cast<double>(points[0]->x - points[3]->x);
    double vec4_y = static_cast<double>(points[0]->y - points[3]->y);
    double cross2 = vec3_x * vec4_y - vec3_y * vec4_x;

    bool is_parallel = (std::fabs(cross1) < EPS) || (std::fabs(cross2) < EPS);

    double base1 = Distance(*points[0], *points[1]);
    double base2 = Distance(*points[2], *points[3]);
    double height = std::fabs(static_cast<double>(points[0]->y - points[2]->y));
    double area = 0.5 * (base1 + base2) * height;

    return is_parallel && area > EPS;
}

template<Scalar T>
bool operator==(const Trapezoid<T>& a, const Trapezoid<T>& b) {
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        if (*a.points[i] != *b.points[i]) {
            return false;
        }
    }
    return true;
}

template<Scalar T>
bool operator!=(const Trapezoid<T>& a, const Trapezoid<T>& b) {
    return !(a == b);
}

template<Scalar T>
std::istream& operator>>(std::istream& stream, Trapezoid<T>& trap) {
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        stream >> *trap.points[i];
    }
    return stream;
}

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Trapezoid<T>& trap) {
    for (int i = 0; i < TRAPEZOID_ANGLES; ++i) {
        stream << *trap.points[i];
    }
    return stream;
}

}
