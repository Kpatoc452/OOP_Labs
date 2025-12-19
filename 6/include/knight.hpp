#pragma once

#include "npc.hpp"

namespace game {

class Knight : public Npc {
public:
    Knight(const std::string& name, double x, double y);
    ~Knight() override = default;

    NpcType GetType() const override;
    std::string GetTypeName() const override;
    void Accept(CombatVisitor& visitor) override;
};

}
