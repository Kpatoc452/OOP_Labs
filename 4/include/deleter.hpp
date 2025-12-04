#pragma once

#include "figure.hpp"
#include <iostream>
#include <atomic>
#include <memory>

namespace figure {

// Статистика удалений
class DeletionStats {
private:
    static std::atomic<size_t> total_deletions_;
    static std::atomic<size_t> point_deletions_;

public:
    static void IncrementTotal() { ++total_deletions_; }
    static void IncrementPoints() { ++point_deletions_; }

    static size_t GetTotalDeletions() { return total_deletions_.load(); }
    static size_t GetPointDeletions() { return point_deletions_.load(); }

    static void Reset() {
        total_deletions_ = 0;
        point_deletions_ = 0;
    }
};

// Базовый deleter с логированием
template<typename T>
struct LoggingDeleter {
    void operator()(T* ptr) const {
        if (ptr) {
            std::cout << "[Deleter] Deleting object at address: " << ptr << std::endl;
            DeletionStats::IncrementTotal();
            delete ptr;
        }
    }
};

// Специализированный deleter для Point с выводом координат
template<Scalar T>
struct PointDeleter {
    void operator()(Point<T>* ptr) const {
        if (ptr) {
            std::cout << "[PointDeleter] Deleting Point("
                      << ptr->x << ", " << ptr->y << ") at "
                      << ptr << std::endl;
            DeletionStats::IncrementTotal();
            DeletionStats::IncrementPoints();
            delete ptr;
        }
    }
};

// Тихий deleter (без логирования, только статистика)
template<typename T>
struct SilentDeleter {
    void operator()(T* ptr) const {
        if (ptr) {
            DeletionStats::IncrementTotal();
            delete ptr;
        }
    }
};

// Deleter с пользовательским сообщением
template<typename T>
class CustomMessageDeleter {
    std::string message_;

public:
    explicit CustomMessageDeleter(const std::string& msg = "") : message_(msg) {}

    void operator()(T* ptr) const {
        if (ptr) {
            if (!message_.empty()) {
                std::cout << "[CustomDeleter] " << message_ << " (address: " << ptr << ")" << std::endl;
            }
            DeletionStats::IncrementTotal();
            delete ptr;
        }
    }
};

// Deleter для массивов (если понадобится)
template<typename T>
struct ArrayDeleter {
    void operator()(T* ptr) const {
        if (ptr) {
            std::cout << "[ArrayDeleter] Deleting array at address: " << ptr << std::endl;
            DeletionStats::IncrementTotal();
            delete[] ptr;
        }
    }
};

}
