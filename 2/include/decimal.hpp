#pragma once

#include "array.hpp"

#include <initializer_list>
#include <string>

namespace Decimal{
class Decimal {
public:
    Decimal();
    Decimal(const size_t& size, const unsigned char ch);
    Decimal(const std::string& str);
    Decimal(const std::initializer_list<unsigned char>& list);
    Decimal(const Array::Array& arr);
    Decimal(const Decimal& other);
    Decimal(Decimal&& other);

    ~Decimal() noexcept = default;

    void Copy(const Decimal& other);

    static Decimal Add(const Decimal& other1, const Decimal& other2);

    static Decimal Sub(const Decimal& other1, const Decimal& other2);

    static Decimal Multi(const Decimal& other1, const Decimal& other2);

    bool    Less(const Decimal& val) const;
    bool    Greater(const Decimal& val) const;
    bool    Equals(const Decimal& val) const;

    std::string String() const;

private:
    int8_t      Cmp(const Decimal& val) const;

    Array::Array digits_;
};
}