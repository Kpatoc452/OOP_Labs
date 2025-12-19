#pragma once

#include "npc.hpp"

namespace game {

class Orc;
class Knight;
class Bear;

class CombatVisitor {
public:
    virtual ~CombatVisitor() = default;

    virtual void VisitOrc(Orc& orc) = 0;
    virtual void VisitKnight(Knight& knight) = 0;
    virtual void VisitBear(Bear& bear) = 0;

    void SetAttacker(Npc* attacker);
    Npc* GetAttacker() const;

protected:
    Npc* attacker_;
};

class CombatResolver : public CombatVisitor {
public:
    CombatResolver();

    void VisitOrc(Orc& orc) override;
    void VisitKnight(Knight& knight) override;
    void VisitBear(Bear& bear) override;

    bool IsDefenderKilled() const;
    bool IsAttackerKilled() const;

private:
    bool defender_killed_;
    bool attacker_killed_;
};

}
