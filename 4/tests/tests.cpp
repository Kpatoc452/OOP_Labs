#include <gtest/gtest.h>
#include "rhombus.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "array.hpp"
#include "deleter.hpp"

using namespace figure;
using namespace containers;

// ========== Point Tests ==========

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

// ========== Rhombus Tests ==========

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

// ========== Rectangle Tests ==========

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

// ========== Trapezoid Tests ==========

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

// ========== Array Tests ==========

TEST(ArrayTest, DefaultConstructor) {
    Array<Figure<double>> arr;
    EXPECT_TRUE(arr.IsEmpty());
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_GE(arr.Capacity(), 0);
}

TEST(ArrayTest, PushBack) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    EXPECT_FALSE(arr.IsEmpty());
    EXPECT_EQ(arr.Size(), 1);
}

TEST(ArrayTest, MultipleElements) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Trapezoid<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{3, 3}, Point<double>{1, 3}));
    arr.PushBack(std::make_shared<Rhombus<double>>(Point<double>{0, 0}, Point<double>{2, 1}, Point<double>{0, 2}, Point<double>{-2, 1}));
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    EXPECT_EQ(arr.Size(), 3);
}

TEST(ArrayTest, Indexing) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    EXPECT_DOUBLE_EQ(arr[0].Area(), 6.0);
}

TEST(ArrayTest, Erase) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    EXPECT_EQ(arr.Size(), 2);
    arr.Erase(0);
    EXPECT_EQ(arr.Size(), 1);
}

TEST(ArrayTest, PopBack) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    EXPECT_EQ(arr.Size(), 2);
    arr.PopBack();
    EXPECT_EQ(arr.Size(), 1);
}

TEST(ArrayTest, Clear) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    arr.Clear();
    EXPECT_TRUE(arr.IsEmpty());
    EXPECT_EQ(arr.Size(), 0);
}

TEST(ArrayTest, TotalArea) {
    Array<Figure<double>> arr;
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));
    arr.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}));

    double total_area = 0;
    for (size_t i = 0; i < arr.Size(); ++i) {
        total_area += arr[i].Area();
    }

    EXPECT_DOUBLE_EQ(total_area, 18.0);
}

// ========== Deleter Tests ==========

TEST(DeleterTest, DeletionStatsReset) {
    DeletionStats::Reset();
    EXPECT_EQ(DeletionStats::GetTotalDeletions(), 0);
    EXPECT_EQ(DeletionStats::GetPointDeletions(), 0);
}

TEST(DeleterTest, PointDeleterIncrementsStats) {
    DeletionStats::Reset();

    {
        Rhombus<double> r({0, 0}, {1, 0}, {1, 1}, {0, 1});
    }

    EXPECT_GT(DeletionStats::GetTotalDeletions(), 0);
    EXPECT_GT(DeletionStats::GetPointDeletions(), 0);
}

TEST(DeleterTest, MultipleRhombusesIncrementCorrectly) {
    DeletionStats::Reset();

    {
        Rhombus<double> r1({0, 0}, {1, 0}, {1, 1}, {0, 1});
        Rhombus<double> r2({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    }

    size_t expected_points = 8;
    EXPECT_EQ(DeletionStats::GetPointDeletions(), expected_points);
    EXPECT_EQ(DeletionStats::GetTotalDeletions(), expected_points);
}

TEST(DeleterTest, SilentDeleterWorks) {
    DeletionStats::Reset();

    {
        using SilentPoint = std::unique_ptr<Point<int>, SilentDeleter<Point<int>>>;
        SilentPoint p(new Point<int>(10, 20), SilentDeleter<Point<int>>());
    }

    EXPECT_EQ(DeletionStats::GetTotalDeletions(), 1);
}

TEST(DeleterTest, CustomMessageDeleterWorks) {
    DeletionStats::Reset();

    {
        using CustomPoint = std::unique_ptr<Point<double>, CustomMessageDeleter<Point<double>>>;
        CustomPoint p(new Point<double>(3.5, 4.2),
                     CustomMessageDeleter<Point<double>>("Test Point"));
    }

    EXPECT_EQ(DeletionStats::GetTotalDeletions(), 1);
}

TEST(DeleterTest, RhombusCopyConstructorDeletesCorrectly) {
    DeletionStats::Reset();

    {
        Rhombus<double> r1({0, 0}, {1, 0}, {1, 1}, {0, 1});
        {
            Rhombus<double> r2(r1);
        }
    }

    size_t expected_points = 8;
    EXPECT_EQ(DeletionStats::GetPointDeletions(), expected_points);
}

TEST(DeleterTest, RhombusAssignmentDeletesCorrectly) {
    DeletionStats::Reset();

    {
        Rhombus<double> r1({0, 0}, {1, 0}, {1, 1}, {0, 1});
        Rhombus<double> r2;
        r2 = r1;
    }

    EXPECT_GT(DeletionStats::GetPointDeletions(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
