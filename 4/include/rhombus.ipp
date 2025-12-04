#pragma once

#include "rhombus.hpp"

namespace figure {

template<Scalar T>
Rhombus<T>::Rhombus() {
    points[0] = PointPtr(new Point<T>(0, 0), PointDeleter<T>());
    points[1] = PointPtr(new Point<T>(1, 0), PointDeleter<T>());
    points[2] = PointPtr(new Point<T>(1, 1), PointDeleter<T>());
    points[3] = PointPtr(new Point<T>(0, 1), PointDeleter<T>());
}

template<Scalar T>
Rhombus<T>::Rhombus(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    points[0] = PointPtr(new Point<T>(p1), PointDeleter<T>());
    points[1] = PointPtr(new Point<T>(p2), PointDeleter<T>());
    points[2] = PointPtr(new Point<T>(p3), PointDeleter<T>());
    points[3] = PointPtr(new Point<T>(p4), PointDeleter<T>());
}

template<Scalar T>
Rhombus<T>::Rhombus(const Rhombus& other) {
    for (size_t i = 0; i < RHOMBUS_ANGLES; ++i) {
        points[i] = PointPtr(new Point<T>(*other.points[i]), PointDeleter<T>());
    }
}

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus& other) {
    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < RHOMBUS_ANGLES; ++i) {
        points[i] = PointPtr(new Point<T>(*other.points[i]), PointDeleter<T>());
    }

    return *this;
}

template<Scalar T>
Rhombus<T>::operator double() const {
    return Area();
}

template<Scalar T>
Point<T> Rhombus<T>::Center() const {
    T cx = 0, cy = 0;

    for (size_t i = 0; i < RHOMBUS_ANGLES; ++i) {
        cx += points[i]->x;
        cy += points[i]->y;
    }

    return Point<T>(cx / RHOMBUS_ANGLES, cy / RHOMBUS_ANGLES);
}

template<Scalar T>
double Rhombus<T>::Area() const {
    double diag1 = Distance(*points[0], *points[2]);
    double diag2 = Distance(*points[1], *points[3]);

    return diag1 * diag2 * 0.5;
}

template<Scalar T>
Point<T> Rhombus<T>::GetVertex(size_t idx) const {
    if (idx >= RHOMBUS_ANGLES) {
        throw std::out_of_range("invalid vertex index");
    }

    return *points[idx];
}

template<Scalar T>
bool Rhombus<T>::IsValid() const {
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = i + 1; j < 4; ++j) {
            if (*points[i] == *points[j]) return false;
        }
    }

    double sides[4];
    for (size_t i = 0; i < 4; ++i) {
        size_t next = (i + 1) % 4;
        sides[i] = Distance(*points[i], *points[next]);
    }

    for (size_t i = 1; i < 4; ++i) {
        if (std::fabs(sides[i] - sides[0]) > EPS) return false;
    }

    double area = Area();
    return area > EPS;
}

template<Scalar T>
bool operator==(const Rhombus<T>& a, const Rhombus<T>& b) {
    for (size_t i = 0; i < RHOMBUS_ANGLES; ++i) {
        if (*a.points[i] != *b.points[i]) {
            return false;
        }
    }
    return true;
}

template<Scalar T>
bool operator!=(const Rhombus<T>& a, const Rhombus<T>& b) {
    return !(a == b);
}

template<Scalar T>
std::istream& operator>>(std::istream& stream, Rhombus<T>& rh) {
    for (size_t i = 0; i < RHOMBUS_ANGLES; ++i) {
        stream >> *rh.points[i];
    }
    return stream;
}

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Rhombus<T>& rh) {
    for (size_t i = 0; i < RHOMBUS_ANGLES; ++i) {
        stream << *rh.points[i];
    }
    return stream;
}

}
