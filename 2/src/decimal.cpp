#include<decimal.hpp>
#include<exceptions.hpp>

namespace Decimal {
    Decimal::Decimal() : digits_() {};

    Decimal::Decimal(const size_t& size, const unsigned char ch): digits_(Array::Array(size, ch)) {}

    Decimal::Decimal(const std::string& str) : digits_(std::move(Array::Array())) {
        if (str.empty()) {
            digits_.PushBack(0);
            return;
        }

        for (auto it = str.rbegin(); it != str.rend(); ++it) {
            const unsigned char& ch = *it;
            if (ch > '9' || ch < '0') {
                throw exception::NaNException("Invalid number");
            }
            digits_.PushBack(ch - '0');
        }

        while (digits_.Size() > 1 && digits_.Back() == 0) {
            digits_.PopBack();
        }
    }

    Decimal::Decimal(const std::initializer_list<unsigned char>& list)
        : digits_(Array::Array(list.size(), 0)) {
        size_t idx = 0;
        
        for (auto it = list.end(); it != list.begin(); ) {
            --it;
            digits_.GetByIdx(idx++) = *it;
        }

        while (digits_.Size() > 1 && digits_.Back() == 0) {
            digits_.PopBack();
        }
    }

    Decimal::Decimal(const Array::Array& arr): digits_() {
        for (size_t i = 0; i < arr.Size(); ++i) {
            const unsigned char& ch = arr.GetByIdx(i);
            if (ch > 9) {
                throw exception::NaNException("Invalid num");
            }
            digits_.PushBack(ch);
        }
        while (digits_.Size() > 1 && digits_.Back() == 0) {
            digits_.PopBack();
        }
    }

    Decimal::Decimal(const Decimal& other): digits_(other.digits_) {}
    
    Decimal::Decimal(Decimal&& other) :digits_(other.digits_) {}

    void Decimal::Copy(const Decimal& other) {
        digits_.Copy(other.digits_);
    }

    Decimal Decimal::Add(const Decimal& val1, const Decimal& val2) {
        Decimal res;
        uint8_t mem = 0;
        size_t idx = 0;

        for (; idx < std::min(val1.digits_.Size(), val2.digits_.Size()); ++idx) {
            const unsigned char& num1 = val1.digits_.GetByIdx(idx);
            const unsigned char& num2 = val2.digits_.GetByIdx(idx);

            uint8_t sum = num1 + num2 + mem;
            mem = sum / 10;
            sum = sum % 10;

            res.digits_.PushBack(sum);
        }

        const Decimal& big_num = val1.Greater(val2) ? val1 : val2;

        for (; idx < big_num.digits_.Size(); ++idx) {
            uint8_t sum = big_num.digits_.GetByIdx(idx) + mem;
            mem = sum / 10;
            sum = sum % 10;
            res.digits_.PushBack(sum);
        }

        if (mem > 0) {
            res.digits_.PushBack(mem);
        }

        return res;
    }

    Decimal Decimal::Sub(const Decimal& val1, const Decimal& val2) {
        if(val1.Less(val2)) {
            throw exception::NegativeException("Invalid arguments. Val1 must be great or equal then Val2");
        }

        if (val1.Equals(val2)) {
            return Decimal();
        }

        Decimal res = Decimal(val1.digits_.Size(), 0);
        int mem = 0;

        for (size_t i = 0; i < val1.digits_.Size(); ++i) {
            int num1 = val1.digits_.GetByIdx(i);
            int num2 = (i < val2.digits_.Size()) ? val2.digits_.GetByIdx(i) : 0;

            num1 -= mem;
            if (num1 < num2) {
                res.digits_.GetByIdx(i) = num1 + 10 - num2;
                mem = 1;
            } else {
                res.digits_.GetByIdx(i) = num1 - num2;
                mem = 0;
            }
        }
    
        while (res.digits_.Size() > 1 && res.digits_.Back() == 0) {
            res.digits_.PopBack();
        } 
        return res;
    }

    Decimal Decimal::Multi(const Decimal& val1, const Decimal& val2) {
        if (val1.digits_.Size() == 1 && val1.digits_.GetByIdx(0) == 0) {
            return Decimal();
        }
        if (val2.digits_.Size() == 1 && val2.digits_.GetByIdx(0) == 0) {
            return Decimal();
        }

        Decimal res = Decimal(val1.digits_.Size() + val2.digits_.Size(), 0);

        for (size_t i = 0; i != val1.digits_.Size(); ++i) {
            for (size_t j = 0; j != val2.digits_.Size(); ++j) {
                res.digits_.GetByIdx(i + j) += val1.digits_.GetByIdx(i) * val2.digits_.GetByIdx(j); 
            }
        }

        uint16_t mem = 0;

        for (size_t i = 0; i != res.digits_.Size(); ++i) {
            uint16_t sum = res.digits_.GetByIdx(i) + mem;

            res.digits_.GetByIdx(i) = sum % 10;
            mem = sum / 10;
        }

        while (res.digits_.Size() > 1 && res.digits_.Back() == 0) {
            res.digits_.PopBack();
        } 

        return res;
    }

    bool Decimal::Less(const Decimal& val) const { 
        return Cmp(val) < 0; 
    }

    bool Decimal::Greater(const Decimal& val) const { 
        return Cmp(val) > 0; 
    }

    bool Decimal::Equals(const Decimal& val) const { 
        return Cmp(val) == 0; 
    }

    std::string Decimal::String() const {
        if (digits_.IsEmpty()) {
            return "0";
        }

        std::string res;

        for (int64_t i = digits_.Size() - 1; i >= 0; --i) {
            res += (digits_.GetByIdx(i) + '0');
        }

        return res;
    }

    int8_t Decimal::Cmp(const Decimal& val) const {
        if (digits_.Size() > val.digits_.Size()) {
            return 1;
        }
        if (digits_.Size() < val.digits_.Size()) {
            return -1;
        }
        if (digits_.Size() == 0) {
            return 0;
        }

        for (size_t i = digits_.Size(); i > 0; --i) {
            size_t idx = i - 1;
            if (digits_.GetByIdx(idx) > val.digits_.GetByIdx(idx)) {
                return 1;
            }
            if (digits_.GetByIdx(idx) < val.digits_.GetByIdx(idx)) {
                return -1;
            }
        }

        return 0;
    }
}