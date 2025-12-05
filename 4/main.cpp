#include <iostream>
#include <memory>
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "rectangle.hpp"
#include "vector.hpp"

int main() {
    using namespace figure;
    using namespace vector;

    Trapezoid<double> trap({0, 0}, {4, 0}, {3, 3}, {1, 3});
    Rhombus<double> rhomb({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rectangle<double> rect({0, 0}, {3, 0}, {3, 2}, {0, 2});

    std::cout << "Trapezoid: " << trap << "\n";
    std::cout << "Area: " << trap.Area() << "\n";
    std::cout << "Center: " << trap.Center() << "\n";
    std::cout << "Conversion to double: " << static_cast<double>(trap) << "\n\n";

    std::cout << "Rhombus: " << rhomb << "\n";
    std::cout << "Area: " << rhomb.Area() << "\n";
    std::cout << "Center: " << rhomb.Center() << "\n";
    std::cout << "Conversion to double: " << static_cast<double>(rhomb) << "\n\n";

    std::cout << "Rectangle: " << rect << "\n";
    std::cout << "Area: " << rect.Area() << "\n";
    std::cout << "Center: " << rect.Center() << "\n";
    std::cout << "Conversion to double: " << static_cast<double>(rect) << "\n\n";

    Vector<std::shared_ptr<Figure<double>>> figures;
    figures.PushBack(std::make_shared<Trapezoid<double>>(Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{3, 3}, Point<double>{1, 3}));
    figures.PushBack(std::make_shared<Rhombus<double>>(Point<double>{0, 0}, Point<double>{2, 1}, Point<double>{0, 2}, Point<double>{-2, 1}));
    figures.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0, 0}, Point<double>{3, 0}, Point<double>{3, 2}, Point<double>{0, 2}));

    std::cout << "Vector size: " << figures.Size() << "\n";
    std::cout << "Vector capacity: " << figures.Capacity() << "\n";

    double total_area = 0;
    for (size_t i = 0; i < figures.Size(); ++i) {
        total_area += figures[i]->Area();
    }
    std::cout << "Total area: " << total_area << "\n\n";

    std::cout << "Centers of figures in vector:\n";
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << "Figure " << (i + 1) << " center: " << figures[i]->Center() << "\n";
    }
    std::cout << "\n";

    std::cout << "Areas of figures in vector:\n";
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << "Figure " << (i + 1) << " area: " << figures[i]->Area() << "\n";
    }
    std::cout << "\n";

    std::cout << "Testing copy constructor:\n";
    Rectangle<double> rect_copy = rect;
    std::cout << "Original: " << rect << "\n";
    std::cout << "Copy: " << rect_copy << "\n";
    std::cout << "Are they equal? " << (rect == rect_copy ? "Yes" : "No") << "\n\n";

    std::cout << "Testing with int type:\n";
    Rectangle<int> int_rect({0, 0}, {5, 0}, {5, 3}, {0, 3});
    std::cout << "Int Rectangle: " << int_rect << "\n";
    std::cout << "Area: " << int_rect.Area() << "\n";
    std::cout << "Center: " << int_rect.Center() << "\n\n";

    std::cout << "Testing Vector with Rectangle<int>:\n";
    Vector<std::shared_ptr<Rectangle<int>>> int_rectangles;
    int_rectangles.PushBack(std::make_shared<Rectangle<int>>(Point<int>{0, 0}, Point<int>{2, 0}, Point<int>{2, 2}, Point<int>{0, 2}));
    int_rectangles.PushBack(std::make_shared<Rectangle<int>>(Point<int>{0, 0}, Point<int>{4, 0}, Point<int>{4, 3}, Point<int>{0, 3}));

    std::cout << "Number of int rectangles: " << int_rectangles.Size() << "\n";
    for (size_t i = 0; i < int_rectangles.Size(); ++i) {
        std::cout << "Rectangle " << (i + 1) << ": " << *int_rectangles[i] << ", Area: " << int_rectangles[i]->Area() << "\n";
    }
    std::cout << "\n";

    std::cout << "Erasing first figure from vector:\n";
    figures.Erase(0);
    std::cout << "New vector size: " << figures.Size() << "\n";
    std::cout << "Remaining figures:\n";
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << "Figure " << (i + 1) << " center: " << figures[i]->Center() << "\n";
    }

    return 0;
}
