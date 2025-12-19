#include "npc.hpp"
#include "exceptions.hpp"

#include <cmath>

namespace game {

Npc::Npc(const std::string& name, double x, double y)
    : name_(name), x_(x), y_(y), alive_(true) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw exception::InvalidCoordinatesException("Coordinates must be in range [0, 500]");
    }
}

std::string Npc::GetName() const {
    return name_;
}

double Npc::GetX() const {
    return x_;
}

double Npc::GetY() const {
    return y_;
}

bool Npc::IsAlive() const {
    return alive_;
}

void Npc::Kill() {
    alive_ = false;
}

double Npc::DistanceTo(const Npc& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}

}
