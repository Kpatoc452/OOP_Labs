#include <gtest/gtest.h>
#include "rhombus.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "vector.hpp"

using namespace figure;
using namespace vector;

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_EQ(p.x, 0.0);
    EXPECT_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 4.2);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.1, 2.0);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.1, 2.0);

    EXPECT_FALSE(p1 != p2);
    EXPECT_TRUE(p1 != p3);
}

TEST(PointTest, Distance) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(3.0, 4.0);

    EXPECT_DOUBLE_EQ(Distance(p1, p2), 5.0);
}

TEST(RhombusTest, DefaultConstructor) {
    Rhombus<double> r;
    EXPECT_EQ(r.GetVertex(0), Point<double>(0, 0));
    EXPECT_EQ(r.GetVertex(1), Point<double>(1, 0));
    EXPECT_EQ(r.GetVertex(2), Point<double>(1, 1));
    EXPECT_EQ(r.GetVertex(3), Point<double>(0, 1));
}

TEST(RhombusTest, ParameterizedConstructor) {
    Rhombus<double> r({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    EXPECT_EQ(r.GetVertex(0), Point<double>(0, 0));
    EXPECT_EQ(r.GetVertex(1), Point<double>(2, 1));
    EXPECT_EQ(r.GetVertex(2), Point<double>(0, 2));
    EXPECT_EQ(r.GetVertex(3), Point<double>(-2, 1));
}

TEST(RhombusTest, CopyConstructor) {
    Rhombus<double> r1({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<double> r2(r1);

    EXPECT_EQ(r1, r2);
    EXPECT_EQ(r2.GetVertex(0), Point<double>(0, 0));
}

TEST(RhombusTest, CopyAssignment) {
    Rhombus<double> r1({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<double> r2;
    r2 = r1;

    EXPECT_EQ(r1, r2);
}

TEST(RhombusTest, Center) {
    Rhombus<double> r({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Point<double> center = r.Center();

    EXPECT_DOUBLE_EQ(center.x, 0.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RhombusTest, Area) {
    Rhombus<double> r({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    double area = r.Area();

    EXPECT_GT(area, 0.0);
}

TEST(RhombusTest, DoubleConversion) {
    Rhombus<double> r({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    double area1 = r.Area();
    double area2 = static_cast<double>(r);

    EXPECT_DOUBLE_EQ(area1, area2);
}

TEST(RhombusTest, IsValid) {
    Rhombus<double> r({0, 0}, {1, 0}, {1, 1}, {0, 1});
    EXPECT_TRUE(r.IsValid());
}

TEST(RhombusTest, GetVertexOutOfRange) {
    Rhombus<double> r;
    EXPECT_THROW(r.GetVertex(4), std::out_of_range);
    EXPECT_THROW(r.GetVertex(10), std::out_of_range);
}

TEST(RhombusTest, EqualityOperator) {
    Rhombus<double> r1({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<double> r2({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<double> r3({0, 0}, {1, 0}, {1, 1}, {0, 1});

    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
}

TEST(RhombusTest, InequalityOperator) {
    Rhombus<double> r1({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<double> r2({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<double> r3({0, 0}, {1, 0}, {1, 1}, {0, 1});

    EXPECT_FALSE(r1 != r2);
    EXPECT_TRUE(r1 != r3);
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> r;
    EXPECT_EQ(r.GetVertex(0), Point<double>(0, 0));
    EXPECT_EQ(r.GetVertex(1), Point<double>(1, 0));
    EXPECT_EQ(r.GetVertex(2), Point<double>(1, 1));
    EXPECT_EQ(r.GetVertex(3), Point<double>(0, 1));
}

TEST(RectangleTest, ParameterizedConstructor) {
    Rectangle<double> r({0, 0}, {3, 0}, {3, 2}, {0, 2});
    EXPECT_EQ(r.GetVertex(0), Point<double>(0, 0));
    EXPECT_EQ(r.GetVertex(1), Point<double>(3, 0));
    EXPECT_EQ(r.GetVertex(2), Point<double>(3, 2));
    EXPECT_EQ(r.GetVertex(3), Point<double>(0, 2));
}

TEST(RectangleTest, CopyConstructor) {
    Rectangle<double> r1({0, 0}, {3, 0}, {3, 2}, {0, 2});
    Rectangle<double> r2(r1);

    EXPECT_EQ(r1, r2);
}

TEST(RectangleTest, CopyAssignment) {
    Rectangle<double> r1({0, 0}, {3, 0}, {3, 2}, {0, 2});
    Rectangle<double> r2;
    r2 = r1;

    EXPECT_EQ(r1, r2);
}

TEST(RectangleTest, Center) {
    Rectangle<double> r({0, 0}, {4, 0}, {4, 2}, {0, 2});
    Point<double> center = r.Center();

    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, Area) {
    Rectangle<double> r({0, 0}, {3, 0}, {3, 2}, {0, 2});
    double area = r.Area();

    EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST(RectangleTest, DoubleConversion) {
    Rectangle<double> r({0, 0}, {3, 0}, {3, 2}, {0, 2});
    double area1 = r.Area();
    double area2 = static_cast<double>(r);

    EXPECT_DOUBLE_EQ(area1, area2);
}

TEST(RectangleTest, IsValid) {
    Rectangle<double> r({0, 0}, {3, 0}, {3, 2}, {0, 2});
    EXPECT_TRUE(r.IsValid());
}

TEST(RectangleTest, GetVertexOutOfRange) {
    Rectangle<double> r;
    EXPECT_THROW(r.GetVertex(4), std::out_of_range);
}

TEST(RectangleTest, IntType) {
    Rectangle<int> r({0, 0}, {5, 0}, {5, 3}, {0, 3});
    EXPECT_EQ(r.GetVertex(0), Point<int>(0, 0));
    EXPECT_EQ(r.Area(), 15.0);
}

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid<double> t;
    EXPECT_EQ(t.GetVertex(0), Point<double>(0, 0));
    EXPECT_EQ(t.GetVertex(1), Point<double>(1, 0));
    EXPECT_EQ(t.GetVertex(2), Point<double>(1, 1));
    EXPECT_EQ(t.GetVertex(3), Point<double>(0, 1));
}

TEST(TrapezoidTest, ParameterizedConstructor) {
    Trapezoid<double> t({0, 0}, {4, 0}, {3, 3}, {1, 3});
    EXPECT_EQ(t.GetVertex(0), Point<double>(0, 0));
    EXPECT_EQ(t.GetVertex(1), Point<double>(4, 0));
    EXPECT_EQ(t.GetVertex(2), Point<double>(3, 3));
    EXPECT_EQ(t.GetVertex(3), Point<double>(1, 3));
}

TEST(TrapezoidTest, CopyConstructor) {
    Trapezoid<double> t1({0, 0}, {4, 0}, {3, 3}, {1, 3});
    Trapezoid<double> t2(t1);

    EXPECT_EQ(t1, t2);
}

TEST(TrapezoidTest, CopyAssignment) {
    Trapezoid<double> t1({0, 0}, {4, 0}, {3, 3}, {1, 3});
    Trapezoid<double> t2;
    t2 = t1;

    EXPECT_EQ(t1, t2);
}

TEST(TrapezoidTest, Center) {
    Trapezoid<double> t({0, 0}, {4, 0}, {3, 3}, {1, 3});
    Point<double> center = t.Center();

    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.5);
}

TEST(TrapezoidTest, Area) {
    Trapezoid<double> t({0, 0}, {4, 0}, {3, 3}, {1, 3});
    double area = t.Area();

    EXPECT_GT(area, 0.0);
}

TEST(TrapezoidTest, DoubleConversion) {
    Trapezoid<double> t({0, 0}, {4, 0}, {3, 3}, {1, 3});
    double area1 = t.Area();
    double area2 = static_cast<double>(t);

    EXPECT_DOUBLE_EQ(area1, area2);
}

TEST(TrapezoidTest, GetVertexOutOfRange) {
    Trapezoid<double> t;
    EXPECT_THROW(t.GetVertex(4), std::out_of_range);
}

TEST(VectorTest, DefaultConstructor) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    EXPECT_TRUE(vec.IsEmpty());
    EXPECT_EQ(vec.Size(), 0);
    EXPECT_GE(vec.Capacity(), 0);
}

TEST(VectorTest, PushBack) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    EXPECT_FALSE(vec.IsEmpty());
    EXPECT_EQ(vec.Size(), 1);
}

TEST(VectorTest, MultipleElements) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Trapezoid<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{3, 3}, Point<double>{1, 3}));
    vec.PushBack(std::make_shared<Rhombus<double>>(Point<double>{0, 0}, Point<double>{2, 1}, Point<double>{0, 2}, Point<double>{-2, 1}));
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    EXPECT_EQ(vec.Size(), 3);
}

TEST(VectorTest, Indexing) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    EXPECT_DOUBLE_EQ(vec[0]->Area(), 6.0);
}

TEST(VectorTest, Erase) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    EXPECT_EQ(vec.Size(), 2);
    vec.Erase(0);
    EXPECT_EQ(vec.Size(), 1);
}

TEST(VectorTest, PopBack) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    EXPECT_EQ(vec.Size(), 2);
    vec.PopBack();
    EXPECT_EQ(vec.Size(), 1);
}

TEST(VectorTest, Clear) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    vec.Clear();
    EXPECT_TRUE(vec.IsEmpty());
    EXPECT_EQ(vec.Size(), 0);
}

TEST(VectorTest, TotalArea) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    vec.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    double total_area = 0;
    for (size_t i = 0; i < vec.Size(); ++i) {
        total_area += vec[i]->Area();
    }

    EXPECT_DOUBLE_EQ(total_area, 18.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
