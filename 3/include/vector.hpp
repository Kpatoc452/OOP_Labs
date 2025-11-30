#pragma once

#include <cstdlib>
#include <initializer_list>
#include <utility>
#include "figure.hpp"

namespace vector {

class Vector {
    friend void swap(Vector& v1, Vector& v2) noexcept;
    
    size_t size_;
    size_t capacity_;
    figure::Figure** data_;
    
public:
    Vector();
    Vector(std::initializer_list<figure::Figure*> init);
    
    figure::Figure& operator[](size_t pos);
    const figure::Figure& operator[](size_t pos) const;
    
    figure::Figure& Front() const noexcept;
    figure::Figure& Back() const noexcept;
    figure::Figure** Data() const noexcept;
    
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    
    void Reserve(size_t new_cap);
    void Clear() noexcept;
    void Insert(size_t pos, figure::Figure* value);
    void Erase(size_t begin_pos, size_t end_pos);
    void Erase(size_t pos);
    void PushBack(figure::Figure* value);
    void PopBack();
    
    double TotalArea();
    void SeparateCenter();
    void SeparateArea();
    
    ~Vector();
};

void swap(Vector& v1, Vector& v2) noexcept;

}
