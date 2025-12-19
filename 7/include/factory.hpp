#pragma once

#include "npc.hpp"
#include <string>

namespace game {

class NpcFactory {
public:
    static NpcPtr Create(NpcType type, const std::string& name, double x, double y);
    static NpcPtr CreateFromString(const std::string& type_str, const std::string& name, double x, double y);
};

}
