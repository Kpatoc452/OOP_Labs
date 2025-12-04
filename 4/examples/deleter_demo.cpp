#include <iostream>
#include "rhombus.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "deleter.hpp"

using namespace figure;

int main() {
    std::cout << "=== Deleter Demo ===" << std::endl << std::endl;

    // Сброс статистики
    DeletionStats::Reset();

    std::cout << "1. Creating Rhombus with PointDeleter:" << std::endl;
    {
        Rhombus<double> r({0, 0}, {2, 1}, {0, 2}, {-2, 1});
        std::cout << "Rhombus created. Area: " << r.Area() << std::endl;
        std::cout << "Leaving scope - Rhombus will be destroyed..." << std::endl;
    }
    std::cout << "Rhombus destroyed." << std::endl << std::endl;

    std::cout << "2. Statistics after Rhombus destruction:" << std::endl;
    std::cout << "Total deletions: " << DeletionStats::GetTotalDeletions() << std::endl;
    std::cout << "Point deletions: " << DeletionStats::GetPointDeletions() << std::endl;
    std::cout << std::endl;

    std::cout << "3. Creating multiple figures:" << std::endl;
    DeletionStats::Reset();
    {
        Rhombus<double> r1({0, 0}, {1, 0}, {1, 1}, {0, 1});
        Rhombus<double> r2({0, 0}, {2, 1}, {0, 2}, {-2, 1});
        std::cout << "Two rhombuses created." << std::endl;
        std::cout << "Leaving scope..." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "4. Final statistics:" << std::endl;
    std::cout << "Total deletions: " << DeletionStats::GetTotalDeletions() << std::endl;
    std::cout << "Point deletions: " << DeletionStats::GetPointDeletions() << std::endl;
    std::cout << std::endl;

    std::cout << "5. Testing custom message deleter:" << std::endl;
    {
        using CustomPoint = std::unique_ptr<Point<double>, CustomMessageDeleter<Point<double>>>;
        CustomPoint p(new Point<double>(3.5, 4.2),
                     CustomMessageDeleter<Point<double>>("Custom Point"));
        std::cout << "Custom Point created at " << p.get() << std::endl;
        std::cout << "Leaving scope..." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "6. Testing silent deleter (no output, only stats):" << std::endl;
    DeletionStats::Reset();
    {
        using SilentPoint = std::unique_ptr<Point<int>, SilentDeleter<Point<int>>>;
        SilentPoint p(new Point<int>(10, 20), SilentDeleter<Point<int>>());
        std::cout << "Silent Point created. No deletion message will be shown." << std::endl;
    }
    std::cout << "Deleted. Total deletions: " << DeletionStats::GetTotalDeletions() << std::endl;
    std::cout << std::endl;

    std::cout << "=== Demo Complete ===" << std::endl;

    return 0;
}
