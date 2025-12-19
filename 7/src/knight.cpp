#include "knight.hpp"
#include "visitor.hpp"

namespace game {

Knight::Knight(const std::string& name, double x, double y)
    : Npc(name, x, y) {}

NpcType Knight::GetType() const {
    return NpcType::KNIGHT;
}

std::string Knight::GetTypeName() const {
    return "Knight";
}

void Knight::Accept(CombatVisitor& visitor) {
    visitor.VisitKnight(*this);
}

double Knight::GetMoveRange() const {
    return 30.0;
}

double Knight::GetKillRange() const {
    return 10.0;
}

}
