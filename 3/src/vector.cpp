#include "vector.hpp"
#include "figure.hpp"
#include <iostream>
#include <stdexcept>

namespace vector {

Vector::Vector() : size_(0), capacity_(0), data_(nullptr) {}

Vector::Vector(std::initializer_list<figure::Figure*> init) 
    : size_(init.size()), capacity_(init.size()), data_(new figure::Figure*[init.size()]) {
    size_t idx = 0;
    for (auto fig : init) {
        data_[idx++] = fig;
    }
}

figure::Figure& Vector::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }
    return *data_[pos];
}

const figure::Figure& Vector::operator[](size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("index out of bounds");
    }
    return *data_[pos];
}

figure::Figure& Vector::Front() const noexcept {
    return *data_[0];
}

figure::Figure& Vector::Back() const noexcept {
    return *data_[size_ - 1];
}

figure::Figure** Vector::Data() const noexcept {
    return data_;
}

bool Vector::IsEmpty() const noexcept {
    return size_ == 0;
}

size_t Vector::Size() const noexcept {
    return size_;
}

size_t Vector::Capacity() const noexcept {
    return capacity_;
}

void Vector::Reserve(size_t new_cap) {
    if (new_cap <= capacity_) return;
    
    figure::Figure** new_data = new figure::Figure*[new_cap];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
}

void Vector::Clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void Vector::Insert(size_t pos, figure::Figure* value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    
    if (pos >= size_) {
        PushBack(value);
        return;
    }
    
    for (size_t i = size_; i > pos; --i) {
        data_[i] = data_[i - 1];
    }
    data_[pos] = value;
    ++size_;
}

void Vector::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos >= end_pos || end_pos > size_) return;
    
    size_t shift = end_pos - begin_pos;
    for (size_t i = end_pos; i < size_; ++i) {
        data_[begin_pos + i - end_pos] = data_[i];
    }
    size_ -= shift;
}

void Vector::Erase(size_t pos) {
    Erase(pos, pos + 1);
}

void Vector::PushBack(figure::Figure* value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

void Vector::PopBack() {
    if (size_ > 0) --size_;
}

double Vector::TotalArea() {
    double total = 0;
    for (size_t i = 0; i < size_; ++i) {
        total += data_[i]->Area();
    }
    return total;
}

void Vector::SeparateCenter() {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure center " << (i + 1) << ": " << data_[i]->Center() << "\n";
    }
}

void Vector::SeparateArea() {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Figure area " << (i + 1) << ": " << data_[i]->Area() << "\n";
    }
}

Vector::~Vector() {
    delete[] data_;
}

void swap(Vector& v1, Vector& v2) noexcept {
    std::swap(v1.size_, v2.size_);
    std::swap(v1.capacity_, v2.capacity_);
    std::swap(v1.data_, v2.data_);
}

}
