#include "orc.hpp"
#include "visitor.hpp"

namespace game {

Orc::Orc(const std::string& name, double x, double y)
    : Npc(name, x, y) {}

NpcType Orc::GetType() const {
    return NpcType::ORC;
}

std::string Orc::GetTypeName() const {
    return "Orc";
}

void Orc::Accept(CombatVisitor& visitor) {
    visitor.VisitOrc(*this);
}

double Orc::GetMoveRange() const {
    return 20.0;
}

double Orc::GetKillRange() const {
    return 10.0;
}

}
