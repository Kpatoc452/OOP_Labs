#include <iostream>
#include "memory_resource.hpp"
#include "list.hpp"

struct Person {
    int id;
    double salary;
    std::string name;

    Person() : id(0), salary(0.0), name("") {}
    Person(int i, double s, const std::string& n) : id(i), salary(s), name(n) {}
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "{" << p.id << ", " << p.salary << ", \"" << p.name << "\"}";
    return os;
}

int main() {
    std::cout << "int list:\n";

    memory::FixedBlockMemoryResource mr1(1024);
    container::List<int> list1(&mr1);

    for (int i = 1; i <= 5; ++i) {
        list1.PushBack(i * 10);
    }

    for (auto val : list1) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    list1.PushFront(5);
    list1.PopBack();

    std::cout << "modified: ";
    for (auto val : list1) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    std::cout << "size: " << list1.Size() << "\n";
    std::cout << "memory: " << mr1.GetUsedMemory() << "/" << mr1.GetTotalMemory() << "\n";

    std::cout << "\nstruct list:\n";

    memory::FixedBlockMemoryResource mr2(2048);
    container::List<Person> list2(&mr2);

    list2.PushBack(Person{1, 50000.0, "Alice"});
    list2.PushBack(Person{2, 60000.0, "Bob"});
    list2.PushBack(Person{3, 55000.0, "Charlie"});

    for (const auto& p : list2) {
        std::cout << p << "\n";
    }

    container::List<Person> list2_copy = list2;
    list2.PopFront();

    std::cout << "size: " << list2.Size() << "\n";
    std::cout << "copy size: " << list2_copy.Size() << "\n";

    std::cout << "\nmemory limit:\n";

    memory::FixedBlockMemoryResource mr3(100);
    container::List<int> list3(&mr3);

    try {
        for (int i = 0; i < 50; ++i) {
            list3.PushBack(i);
        }
    } catch (const std::bad_alloc&) {
        std::cout << "out of memory! added: " << list3.Size() << "\n";
        std::cout << "used: " << mr3.GetUsedMemory() << "/" << mr3.GetTotalMemory() << "\n";
    }

    return 0;
}
