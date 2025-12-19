#pragma once

#include <string>
#include <memory>

namespace game {

class CombatVisitor;

enum class NpcType {
    ORC,
    KNIGHT,
    BEAR
};

class Npc {
public:
    Npc(const std::string& name, double x, double y);
    virtual ~Npc() = default;

    virtual NpcType GetType() const = 0;
    virtual std::string GetTypeName() const = 0;
    virtual void Accept(CombatVisitor& visitor) = 0;

    std::string GetName() const;
    double GetX() const;
    double GetY() const;
    bool IsAlive() const;
    void Kill();

    double DistanceTo(const Npc& other) const;

protected:
    std::string name_;
    double x_;
    double y_;
    bool alive_;
};

using NpcPtr = std::shared_ptr<Npc>;

}
