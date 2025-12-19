#include "visitor.hpp"
#include "orc.hpp"
#include "knight.hpp"
#include "bear.hpp"

namespace game {

void CombatVisitor::SetAttacker(Npc* attacker) {
    attacker_ = attacker;
}

Npc* CombatVisitor::GetAttacker() const {
    return attacker_;
}

CombatResolver::CombatResolver()
    : defender_killed_(false), attacker_killed_(false) {
    attacker_ = nullptr;
}

void CombatResolver::VisitOrc(Orc& orc) {
    if (!attacker_) {
        return;
    }

    defender_killed_ = false;
    attacker_killed_ = false;

    switch (attacker_->GetType()) {
        case NpcType::ORC:
            break;
        case NpcType::KNIGHT:
            defender_killed_ = true;
            break;
        case NpcType::BEAR:
            break;
    }
}

void CombatResolver::VisitKnight(Knight& knight) {
    if (!attacker_) {
        return;
    }

    defender_killed_ = false;
    attacker_killed_ = false;

    switch (attacker_->GetType()) {
        case NpcType::ORC:
            break;
        case NpcType::KNIGHT:
            break;
        case NpcType::BEAR:
            defender_killed_ = true;
            break;
    }
}

void CombatResolver::VisitBear(Bear& bear) {
    if (!attacker_) {
        return;
    }

    defender_killed_ = false;
    attacker_killed_ = false;

    switch (attacker_->GetType()) {
        case NpcType::ORC:
            defender_killed_ = true;
            break;
        case NpcType::KNIGHT:
            break;
        case NpcType::BEAR:
            break;
    }
}

bool CombatResolver::IsDefenderKilled() const {
    return defender_killed_;
}

bool CombatResolver::IsAttackerKilled() const {
    return attacker_killed_;
}

}
