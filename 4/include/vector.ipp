#pragma once

#include "vector.hpp"
#include <iostream>
#include <stdexcept>

namespace vector {

template<typename T>
Vector<T>::Vector() : size_(0), capacity_(0), data_(nullptr) {}

template<typename T>
Vector<T>::Vector(std::initializer_list<std::shared_ptr<T>> init)
    : size_(init.size()), capacity_(init.size()), data_(new std::shared_ptr<T>[init.size()]) {
    size_t idx = 0;
    for (auto& item : init) {
        data_[idx++] = item;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new std::shared_ptr<T>[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new std::shared_ptr<T>[capacity_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;

    return *this;
}

template<typename T>
T& Vector<T>::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }
    return *data_[pos];
}

template<typename T>
const T& Vector<T>::operator[](size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }
    return *data_[pos];
}

template<typename T>
T& Vector<T>::Front() const {
    if (size_ == 0) {
        throw std::out_of_range("vector is empty");
    }
    return *data_[0];
}

template<typename T>
T& Vector<T>::Back() const {
    if (size_ == 0) {
        throw std::out_of_range("vector is empty");
    }
    return *data_[size_ - 1];
}

template<typename T>
std::shared_ptr<T>* Vector<T>::Data() const noexcept {
    return data_;
}

template<typename T>
bool Vector<T>::IsEmpty() const noexcept {
    return size_ == 0;
}

template<typename T>
size_t Vector<T>::Size() const noexcept {
    return size_;
}

template<typename T>
size_t Vector<T>::Capacity() const noexcept {
    return capacity_;
}

template<typename T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap <= capacity_) return;

    std::shared_ptr<T>* new_data = new std::shared_ptr<T>[new_cap];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
}

template<typename T>
void Vector<T>::Clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template<typename T>
void Vector<T>::Insert(size_t pos, std::shared_ptr<T> value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    if (pos >= size_) {
        PushBack(value);
        return;
    }

    for (size_t i = size_; i > pos; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[pos] = std::move(value);
    ++size_;
}

template<typename T>
void Vector<T>::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos >= end_pos || end_pos > size_) return;

    size_t shift = end_pos - begin_pos;
    for (size_t i = end_pos; i < size_; ++i) {
        data_[begin_pos + i - end_pos] = std::move(data_[i]);
    }
    size_ -= shift;
}

template<typename T>
void Vector<T>::Erase(size_t pos) {
    Erase(pos, pos + 1);
}

template<typename T>
void Vector<T>::PushBack(std::shared_ptr<T> value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template<typename T>
void Vector<T>::PopBack() {
    if (size_ > 0) {
        --size_;
        data_[size_].reset();
    }
}

template<typename T>
double Vector<T>::TotalArea() {
    double total = 0;
    for (size_t i = 0; i < size_; ++i) {
        total += data_[i]->Area();
    }
    return total;
}

template<typename T>
void Vector<T>::SeparateCenter() {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure center " << (i + 1) << ": " << data_[i]->Center() << "\n";
    }
}

template<typename T>
void Vector<T>::SeparateArea() {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure area " << (i + 1) << ": " << data_[i]->Area() << "\n";
    }
}

template<typename T>
void swap(Vector<T>& v1, Vector<T>& v2) noexcept {
    std::swap(v1.size_, v2.size_);
    std::swap(v1.capacity_, v2.capacity_);
    std::swap(v1.data_, v2.data_);
}

}
