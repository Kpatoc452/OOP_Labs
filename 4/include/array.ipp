#pragma once

#include "array.hpp"

namespace containers {

template<typename T>
Array<T>::Array() : size_(0), capacity_(0), data_(nullptr) {}

template<typename T>
Array<T>::Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new std::shared_ptr<T>[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
Array<T>::Array(Array&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template<typename T>
Array<T>::~Array() {
    delete[] data_;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
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
Array<T>& Array<T>::operator=(Array&& other) noexcept {
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
T& Array<T>::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }
    return *data_[pos];
}

template<typename T>
const T& Array<T>::operator[](size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }
    return *data_[pos];
}

template<typename T>
T& Array<T>::Front() const {
    if (size_ == 0) {
        throw std::out_of_range("array is empty");
    }
    return *data_[0];
}

template<typename T>
T& Array<T>::Back() const {
    if (size_ == 0) {
        throw std::out_of_range("array is empty");
    }
    return *data_[size_ - 1];
}

template<typename T>
std::shared_ptr<T>* Array<T>::Data() const noexcept {
    return data_;
}

template<typename T>
bool Array<T>::IsEmpty() const noexcept {
    return size_ == 0;
}

template<typename T>
size_t Array<T>::Size() const noexcept {
    return size_;
}

template<typename T>
size_t Array<T>::Capacity() const noexcept {
    return capacity_;
}

template<typename T>
void Array<T>::Reserve(size_t new_cap) {
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
void Array<T>::Clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template<typename T>
void Array<T>::PushBack(std::shared_ptr<T> value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template<typename T>
void Array<T>::PopBack() {
    if (size_ > 0) {
        --size_;
        data_[size_].reset();
    }
}

template<typename T>
void Array<T>::Erase(size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }

    for (size_t i = pos; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }

    --size_;
    data_[size_].reset();
}

template<typename T>
void Array<T>::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos >= end_pos || end_pos > size_) {
        throw std::out_of_range("invalid range");
    }

    size_t shift = end_pos - begin_pos;
    for (size_t i = end_pos; i < size_; ++i) {
        data_[begin_pos + i - end_pos] = std::move(data_[i]);
    }

    size_ -= shift;
}

template<typename T>
void swap(Array<T>& a1, Array<T>& a2) noexcept {
    std::swap(a1.size_, a2.size_);
    std::swap(a1.capacity_, a2.capacity_);
    std::swap(a1.data_, a2.data_);
}

}
