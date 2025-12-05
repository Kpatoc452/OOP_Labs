#include <gtest/gtest.h>
#include "memory_resource.hpp"
#include "list.hpp"

using namespace memory;
using namespace container;

TEST(MemoryResourceTest, BasicAllocation) {
    FixedBlockMemoryResource mr(1024);

    EXPECT_EQ(mr.GetAllocatedCount(), 0);
    EXPECT_EQ(mr.GetUsedMemory(), 0);
    EXPECT_EQ(mr.GetTotalMemory(), 1024);

    void* ptr = mr.allocate(64, 8);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(mr.GetAllocatedCount(), 1);
    EXPECT_GT(mr.GetUsedMemory(), 0);

    mr.deallocate(ptr, 64, 8);
    EXPECT_EQ(mr.GetAllocatedCount(), 0);
}

TEST(MemoryResourceTest, MultipleAllocations) {
    FixedBlockMemoryResource mr(1024);

    void* ptr1 = mr.allocate(32, 8);
    void* ptr2 = mr.allocate(64, 8);
    void* ptr3 = mr.allocate(16, 8);

    EXPECT_EQ(mr.GetAllocatedCount(), 3);
    EXPECT_NE(ptr1, ptr2);
    EXPECT_NE(ptr2, ptr3);
    EXPECT_NE(ptr1, ptr3);

    mr.deallocate(ptr2, 64, 8);
    EXPECT_EQ(mr.GetAllocatedCount(), 2);

    mr.deallocate(ptr1, 32, 8);
    mr.deallocate(ptr3, 16, 8);
    EXPECT_EQ(mr.GetAllocatedCount(), 0);
}

TEST(MemoryResourceTest, OutOfMemory) {
    FixedBlockMemoryResource mr(64);

    EXPECT_THROW(mr.allocate(128, 8), std::bad_alloc);
}

TEST(ListTest, EmptyList) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    EXPECT_TRUE(list.IsEmpty());
    EXPECT_EQ(list.Size(), 0);
}

TEST(ListTest, PushBackAndIterate) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    EXPECT_EQ(list.Size(), 3);
    EXPECT_FALSE(list.IsEmpty());

    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, PushFront) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushFront(10);
    list.PushFront(20);
    list.PushFront(30);

    EXPECT_EQ(list.Size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
}

TEST(ListTest, FrontAndBack) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    EXPECT_EQ(list.Front(), 10);
    EXPECT_EQ(list.Back(), 30);

    list.Front() = 100;
    list.Back() = 300;

    EXPECT_EQ(list.Front(), 100);
    EXPECT_EQ(list.Back(), 300);
}

TEST(ListTest, PopBack) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    list.PopBack();
    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(list.Back(), 20);

    list.PopBack();
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Back(), 10);

    list.PopBack();
    EXPECT_TRUE(list.IsEmpty());
}

TEST(ListTest, PopFront) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    list.PopFront();
    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(list.Front(), 20);

    list.PopFront();
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Front(), 30);

    list.PopFront();
    EXPECT_TRUE(list.IsEmpty());
}

TEST(ListTest, Clear) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    EXPECT_EQ(list.Size(), 3);

    list.Clear();
    EXPECT_TRUE(list.IsEmpty());
    EXPECT_EQ(list.Size(), 0);
}

TEST(ListTest, CopyConstructor) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    List<int> list_copy(list);

    EXPECT_EQ(list.Size(), list_copy.Size());

    auto it1 = list.begin();
    auto it2 = list_copy.begin();

    while (it1 != list.end() && it2 != list_copy.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(ListTest, MoveConstructor) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    List<int> list_moved(std::move(list));

    EXPECT_EQ(list_moved.Size(), 3);
    EXPECT_TRUE(list.IsEmpty());

    auto it = list_moved.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

TEST(ListTest, CopyAssignment) {
    FixedBlockMemoryResource mr(1024);
    List<int> list1(&mr);
    List<int> list2(&mr);

    list1.PushBack(10);
    list1.PushBack(20);

    list2.PushBack(100);
    list2.PushBack(200);
    list2.PushBack(300);

    list2 = list1;

    EXPECT_EQ(list2.Size(), 2);

    auto it = list2.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(ListTest, MoveAssignment) {
    FixedBlockMemoryResource mr(1024);
    List<int> list1(&mr);
    List<int> list2(&mr);

    list1.PushBack(10);
    list1.PushBack(20);

    list2.PushBack(100);
    list2.PushBack(200);

    list2 = std::move(list1);

    EXPECT_EQ(list2.Size(), 2);
    EXPECT_TRUE(list1.IsEmpty());

    auto it = list2.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

struct ComplexType {
    int id;
    double value;

    ComplexType(int i = 0, double v = 0.0) : id(i), value(v) {}

    bool operator==(const ComplexType& other) const {
        return id == other.id && value == other.value;
    }
};

TEST(ListTest, ComplexType) {
    FixedBlockMemoryResource mr(2048);
    List<ComplexType> list(&mr);

    list.PushBack(ComplexType{1, 1.5});
    list.PushBack(ComplexType{2, 2.5});
    list.PushBack(ComplexType{3, 3.5});

    EXPECT_EQ(list.Size(), 3);

    auto it = list.begin();
    EXPECT_EQ(it->id, 1);
    EXPECT_DOUBLE_EQ(it->value, 1.5);
    ++it;
    EXPECT_EQ(it->id, 2);
    EXPECT_DOUBLE_EQ(it->value, 2.5);
    ++it;
    EXPECT_EQ(it->id, 3);
    EXPECT_DOUBLE_EQ(it->value, 3.5);
}

TEST(ListTest, RangeBasedFor) {
    FixedBlockMemoryResource mr(1024);
    List<int> list(&mr);

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);

    int sum = 0;
    for (int val : list) {
        sum += val;
    }

    EXPECT_EQ(sum, 15);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
