#pragma once

#include <stdexcept>
#include <string>

namespace exception {
    class NaNException: public std::runtime_error {
    public:
        explicit NaNException(const std::string& error): std::runtime_error(error) {}
    };

    class NegativeException: public std::runtime_error {
    public:
        explicit NegativeException(const std::string& error): std::runtime_error(error) {}
    };
}