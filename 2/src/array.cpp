#include <array.hpp>
#include <cstring>
#include <utility>

namespace Array {
    Array::Array(): sz_(0), cap_(0), arr_(nullptr) {}

    Array::Array(const size_t& size, const unsigned char value)
        : sz_(size), cap_(size), arr_(size > 0 ? new unsigned char[size] : nullptr) {
        if (arr_ != nullptr) {
            memset(arr_, value, size);
        }
    }

    Array::Array(const Array& other) 
        : sz_(other.sz_), cap_(other.cap_), arr_(other.sz_ > 0 ? new unsigned char[other.sz_] : nullptr) {
        if (arr_ != nullptr) {
            memcpy(arr_, other.arr_, sz_);
        }
    }

    Array::Array(const std::string& str)
        : sz_(str.size()), cap_(str.size()), arr_(str.size() > 0 ? new unsigned char[str.size()] : nullptr) {
        if (arr_ != nullptr) {
            memcpy(arr_, str.data(), sz_);
        }
    }

    Array::Array(Array&& other) noexcept 
        : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
        other.arr_ = nullptr;
        other.sz_ = 0;
        other.cap_ = 0;
    }

    Array::Array(const std::initializer_list<unsigned char>& list)
        : sz_(list.size()), cap_(list.size()), arr_(list.size() > 0 ? new unsigned char[list.size()] : nullptr) {
        if (arr_ != nullptr) {
            size_t i = 0;
            for (const unsigned char& val : list) {
                arr_[i++] = val;
            }
        }
    }
    Array& Array::Copy(const Array& other) {
        if (this != &other) {
            Array tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    void Array::Swap(Array& other) noexcept {
        std::swap(arr_, other.arr_);
        std::swap(sz_, other.sz_);
        std::swap(cap_, other.cap_);
    }

    void Array::Clear() noexcept {
        delete[] arr_;
        arr_ = nullptr;
        sz_ = 0;
        cap_ = 0;
    }

    unsigned char& Array::GetByIdx(size_t pos) {
        return arr_[pos];
    }

    const unsigned char& Array::GetByIdx(size_t pos) const {
        return arr_[pos];
    }

    unsigned char& Array::Front() {
        return arr_[0];
    }

    const unsigned char& Array::Front() const noexcept {
        return arr_[0];
    }

    unsigned char& Array::Back() {
        return arr_[sz_ - 1];
    }

    const unsigned char& Array::Back() const noexcept {
        return arr_[sz_ - 1];
    }

    void Array::PushBack(unsigned char value) {
        if (sz_ == cap_) {
            size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
            unsigned char* new_arr = new unsigned char[new_cap];
            
            if (arr_ != nullptr) {
                memcpy(new_arr, arr_, sz_);
                delete[] arr_;
            }
            
            arr_ = new_arr;
            cap_ = new_cap;
        }
        
        arr_[sz_++] = value;
    }

    void Array::PopBack() {
        if (sz_ > 0) {
            --sz_;
        }
    }

    bool Array::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    size_t Array::Size() const noexcept {
        return sz_;
    }

    size_t Array::Capacity() const noexcept {
        return cap_;
    }

    Array::~Array() {
        delete[] arr_;
    }
}
