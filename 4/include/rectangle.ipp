#pragma once

#include "rectangle.hpp"

namespace figure {

template<Scalar T>
Rectangle<T>::Rectangle() {
    points[0] = std::make_unique<Point<T>>(0, 0);
    points[1] = std::make_unique<Point<T>>(1, 0);
    points[2] = std::make_unique<Point<T>>(1, 1);
    points[3] = std::make_unique<Point<T>>(0, 1);
}

template<Scalar T>
Rectangle<T>::Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    points[0] = std::make_unique<Point<T>>(p1);
    points[1] = std::make_unique<Point<T>>(p2);
    points[2] = std::make_unique<Point<T>>(p3);
    points[3] = std::make_unique<Point<T>>(p4);
}

template<Scalar T>
Rectangle<T>::Rectangle(const Rectangle& other) {
    for (int i = 0; i < RECTANGLE_ANGLES; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < RECTANGLE_ANGLES; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    return *this;
}

template<Scalar T>
Rectangle<T>::operator double() const {
    return Area();
}

template<Scalar T>
Point<T> Rectangle<T>::Center() const {
    T cx = 0, cy = 0;

    for (int i = 0; i < RECTANGLE_ANGLES; ++i) {
        cx += points[i]->x;
        cy += points[i]->y;
    }

    return Point<T>(cx / RECTANGLE_ANGLES, cy / RECTANGLE_ANGLES);
}

template<Scalar T>
double Rectangle<T>::Area() const {
    double side1 = Distance(*points[0], *points[1]);
    double side2 = Distance(*points[1], *points[2]);

    return side1 * side2;
}

template<Scalar T>
Point<T> Rectangle<T>::GetVertex(int idx) const {
    if (idx < 0 || idx >= RECTANGLE_ANGLES) {
        throw std::out_of_range("invalid vertex index");
    }

    return *points[idx];
}

template<Scalar T>
bool Rectangle<T>::IsValid() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (*points[i] == *points[j]) return false;
        }
    }

    double sides[4];
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        sides[i] = Distance(*points[i], *points[next]);
    }

    if (std::fabs(sides[0] - sides[2]) > EPS || std::fabs(sides[1] - sides[3]) > EPS) {
        return false;
    }

    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        int next2 = (i + 2) % 4;

        double vec1_x = static_cast<double>(points[next]->x - points[i]->x);
        double vec1_y = static_cast<double>(points[next]->y - points[i]->y);
        double vec2_x = static_cast<double>(points[next2]->x - points[next]->x);
        double vec2_y = static_cast<double>(points[next2]->y - points[next]->y);

        double dot_product = vec1_x * vec2_x + vec1_y * vec2_y;

        if (std::fabs(dot_product) > EPS) {
            return false;
        }
    }

    double area = Area();
    return area > EPS;
}

template<Scalar T>
bool operator==(const Rectangle<T>& a, const Rectangle<T>& b) {
    for (int i = 0; i < RECTANGLE_ANGLES; ++i) {
        if (*a.points[i] != *b.points[i]) {
            return false;
        }
    }
    return true;
}

template<Scalar T>
bool operator!=(const Rectangle<T>& a, const Rectangle<T>& b) {
    return !(a == b);
}

template<Scalar T>
std::istream& operator>>(std::istream& stream, Rectangle<T>& rect) {
    for (int i = 0; i < RECTANGLE_ANGLES; ++i) {
        stream >> *rect.points[i];
    }
    return stream;
}

template<Scalar T>
std::ostream& operator<<(std::ostream& stream, const Rectangle<T>& rect) {
    for (int i = 0; i < RECTANGLE_ANGLES; ++i) {
        stream << *rect.points[i];
    }
    return stream;
}

}
