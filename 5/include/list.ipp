#pragma once

namespace container {

template <typename T>
List<T>::List(std::pmr::memory_resource* mr)
    : head_(nullptr), tail_(nullptr), size_(0), allocator_(mr) {}

template <typename T>
List<T>::List(const List& other)
    : head_(nullptr), tail_(nullptr), size_(0), allocator_(other.allocator_) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        PushBack(*it);
    }
}

template <typename T>
List<T>::List(List&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_),
      allocator_(std::move(other.allocator_)) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
List<T>::~List() {
    Clear();
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this == &other) {
        return *this;
    }

    Clear();

    for (auto it = other.begin(); it != other.end(); ++it) {
        PushBack(*it);
    }

    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Clear();

    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;

    return *this;
}

template <typename T>
void List<T>::PushBack(const T& value) {
    Node* new_node = allocator_.allocate(1);
    allocator_.construct(new_node, value);

    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        tail_->next = new_node;
        new_node->prev = tail_;
        tail_ = new_node;
    }

    ++size_;
}

template <typename T>
void List<T>::PushBack(T&& value) {
    Node* new_node = allocator_.allocate(1);
    allocator_.construct(new_node, std::move(value));

    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        tail_->next = new_node;
        new_node->prev = tail_;
        tail_ = new_node;
    }

    ++size_;
}

template <typename T>
void List<T>::PushFront(const T& value) {
    Node* new_node = allocator_.allocate(1);
    allocator_.construct(new_node, value);

    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        new_node->next = head_;
        head_->prev = new_node;
        head_ = new_node;
    }

    ++size_;
}

template <typename T>
void List<T>::PushFront(T&& value) {
    Node* new_node = allocator_.allocate(1);
    allocator_.construct(new_node, std::move(value));

    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        new_node->next = head_;
        head_->prev = new_node;
        head_ = new_node;
    }

    ++size_;
}

template <typename T>
void List<T>::PopBack() {
    if (!tail_) {
        return;
    }

    Node* old_tail = tail_;

    if (head_ == tail_) {
        head_ = tail_ = nullptr;
    } else {
        tail_ = tail_->prev;
        tail_->next = nullptr;
    }

    allocator_.destroy(old_tail);
    allocator_.deallocate(old_tail, 1);
    --size_;
}

template <typename T>
void List<T>::PopFront() {
    if (!head_) {
        return;
    }

    Node* old_head = head_;

    if (head_ == tail_) {
        head_ = tail_ = nullptr;
    } else {
        head_ = head_->next;
        head_->prev = nullptr;
    }

    allocator_.destroy(old_head);
    allocator_.deallocate(old_head, 1);
    --size_;
}

template <typename T>
T& List<T>::Front() {
    return head_->data;
}

template <typename T>
const T& List<T>::Front() const {
    return head_->data;
}

template <typename T>
T& List<T>::Back() {
    return tail_->data;
}

template <typename T>
const T& List<T>::Back() const {
    return tail_->data;
}

template <typename T>
bool List<T>::IsEmpty() const noexcept {
    return size_ == 0;
}

template <typename T>
size_t List<T>::Size() const noexcept {
    return size_;
}

template <typename T>
void List<T>::Clear() noexcept {
    while (!IsEmpty()) {
        PopFront();
    }
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head_);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head_);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}

}
