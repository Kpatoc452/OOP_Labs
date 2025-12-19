#pragma once

#include "npc.hpp"

namespace game {

class Bear : public Npc {
public:
    Bear(const std::string& name, double x, double y);
    ~Bear() override = default;

    NpcType GetType() const override;
    std::string GetTypeName() const override;
    void Accept(CombatVisitor& visitor) override;
};

}
