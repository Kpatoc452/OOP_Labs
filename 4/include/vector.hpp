#pragma once

#include <cstdlib>
#include <initializer_list>
#include <utility>
#include <memory>
#include "figure.hpp"

namespace vector {

template<typename T>
class Vector {
    size_t size_;
    size_t capacity_;
    std::shared_ptr<T>* data_;

public:
    Vector();
    Vector(std::initializer_list<std::shared_ptr<T>> init);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    T& Front() const;
    T& Back() const;
    std::shared_ptr<T>* Data() const noexcept;

    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;

    void Reserve(size_t new_cap);
    void Clear() noexcept;
    void Insert(size_t pos, std::shared_ptr<T> value);
    void Erase(size_t begin_pos, size_t end_pos);
    void Erase(size_t pos);
    void PushBack(std::shared_ptr<T> value);
    void PopBack();

    double TotalArea();
    void SeparateCenter();
    void SeparateArea();

    template<typename U>
    friend void swap(Vector<U>& v1, Vector<U>& v2) noexcept;
};

template<typename T>
void swap(Vector<T>& v1, Vector<T>& v2) noexcept;

}

#include "vector.ipp"
