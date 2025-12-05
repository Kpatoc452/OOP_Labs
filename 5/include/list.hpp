#pragma once

#include <memory_resource>
#include <iterator>
#include <utility>

namespace container {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        template <typename... Args>
        Node(Args&&... args)
            : data(std::forward<Args>(args)...), next(nullptr), prev(nullptr) {}
    };

    using NodeAllocator = std::pmr::polymorphic_allocator<Node>;

    Node* head_;
    Node* tail_;
    size_t size_;
    NodeAllocator allocator_;

public:
    class Iterator {
        friend class List;
        Node* current_;

        explicit Iterator(Node* node) : current_(node) {}

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator() : current_(nullptr) {}

        reference operator*() const {
            return current_->data;
        }

        pointer operator->() const {
            return &current_->data;
        }

        Iterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }
    };

    explicit List(std::pmr::memory_resource* mr = std::pmr::get_default_resource());
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    void PushBack(const T& value);
    void PushBack(T&& value);
    void PushFront(const T& value);
    void PushFront(T&& value);
    void PopBack();
    void PopFront();

    T& Front();
    const T& Front() const;
    T& Back();
    const T& Back() const;

    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    void Clear() noexcept;

    Iterator begin();
    Iterator end();
    Iterator begin() const;
    Iterator end() const;
};

}

#include "list.ipp"
