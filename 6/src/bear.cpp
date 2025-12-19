#include "bear.hpp"
#include "visitor.hpp"

namespace game {

Bear::Bear(const std::string& name, double x, double y)
    : Npc(name, x, y) {}

NpcType Bear::GetType() const {
    return NpcType::BEAR;
}

std::string Bear::GetTypeName() const {
    return "Bear";
}

void Bear::Accept(CombatVisitor& visitor) {
    visitor.VisitBear(*this);
}

}
