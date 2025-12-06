#include <iostream>
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "vector.hpp"

int main() {
    using namespace figure;
    using namespace vector;

    Trapezoid trap({0, 0}, {4, 0}, {3, 3}, {1, 3});
    Rhombus rhomb({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Pentagon penta;
    
    std::cout << "Trapezoid: " << trap << "\n";
    std::cout << "Area: " << trap.Area() << "\n";
    std::cout << "Center: " << trap.Center() << "\n\n";
    
    std::cout << "Rhombus: " << rhomb << "\n";
    std::cout << "Area: " << rhomb.Area() << "\n";
    std::cout << "Center: " << rhomb.Center() << "\n\n";
    
    std::cout << "Pentagon: " << penta << "\n";
    std::cout << "Area: " << penta.Area() << "\n";
    std::cout << "Center: " << penta.Center() << "\n\n";

    Vector v;
    v.PushBack(new Trapezoid({0, 0}, {4, 0}, {3, 3}, {1, 3}));
    v.PushBack(new Rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1}));
    v.PushBack(new Pentagon());
    
    std::cout << "Vector size: " << v.Size() << "\n";
    std::cout << "Vector capacity: " << v.Capacity() << "\n";
    std::cout << "Total area: " << v.TotalArea() << "\n\n";
    
    v.SeparateCenter();
    std::cout << "\n";
    v.SeparateArea();

    return 0;
}
