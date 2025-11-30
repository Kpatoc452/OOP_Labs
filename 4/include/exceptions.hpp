#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {
    class InvalidPointsException: public std::runtime_error {
    public:
        explicit InvalidPointsException(const std::string& error): std::runtime_error(error) {}
    };
}