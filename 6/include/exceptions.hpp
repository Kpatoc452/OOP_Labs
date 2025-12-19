#pragma once

#include <stdexcept>
#include <string>

namespace exception {

class InvalidNpcTypeException : public std::runtime_error {
public:
    explicit InvalidNpcTypeException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class InvalidCoordinatesException : public std::runtime_error {
public:
    explicit InvalidCoordinatesException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class DuplicateNameException : public std::runtime_error {
public:
    explicit DuplicateNameException(const std::string& msg)
        : std::runtime_error(msg) {}
};

}
