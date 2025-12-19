#pragma once

#include "npc.hpp"

namespace game {

class Orc : public Npc {
public:
    Orc(const std::string& name, double x, double y);
    ~Orc() override = default;

    NpcType GetType() const override;
    std::string GetTypeName() const override;
    void Accept(CombatVisitor& visitor) override;
};

}
