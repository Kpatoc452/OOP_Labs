#pragma once

#include <initializer_list>
#include <utility>
#include <string>

namespace Array{
class Array {
public:
    Array();

    Array(const size_t& size, const unsigned char& value);

    Array(const Array& other);

    Array(Array&& other) noexcept;

    Array(const std::initializer_list<unsigned char>& list);

    Array(const std::string& str);

    Array& Copy(const Array& other);

    unsigned char& GetByIdx(size_t pos);

    const unsigned char& GetByIdx(size_t pos) const;

    unsigned char& Front();
    
    const unsigned char& Front() const noexcept;

    unsigned char& Back();

    const unsigned char& Back() const noexcept;

    const unsigned char& Data() const noexcept;

    bool IsEmpty() const noexcept;

    size_t Size() const noexcept;

    size_t Capacity() const noexcept;

    //void Reserve(size_t new_cap);

    //void Clear() noexcept;

    void PushBack(unsigned char value);

    void PopBack();

    void Clear() noexcept;

    ~Array();

private:
    size_t sz_;
    size_t cap_;
    unsigned char* arr_;

    void Resize(size_t size, const unsigned char& value);

    void Swap(Array& v) noexcept;
};
}