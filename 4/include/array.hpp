#pragma once

#include <cstdlib>
#include <memory>
#include <utility>
#include <stdexcept>
#include <iostream>

namespace containers {

template<typename T>
class Array {
    size_t size_;
    size_t capacity_;
    std::shared_ptr<T>* data_;

public:
    Array();
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

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
    void PushBack(std::shared_ptr<T> value);
    void PopBack();
    void Erase(size_t pos);
    void Erase(size_t begin_pos, size_t end_pos);
};

template<typename T>
void swap(Array<T>& a1, Array<T>& a2) noexcept;

}

#include "array.ipp"
