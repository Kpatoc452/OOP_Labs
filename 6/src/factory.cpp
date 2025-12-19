#include "factory.hpp"
#include "orc.hpp"
#include "knight.hpp"
#include "bear.hpp"
#include "exceptions.hpp"

#include <algorithm>

namespace game {

NpcPtr NpcFactory::Create(NpcType type, const std::string& name, double x, double y) {
    switch (type) {
        case NpcType::ORC:
            return std::make_shared<Orc>(name, x, y);
        case NpcType::KNIGHT:
            return std::make_shared<Knight>(name, x, y);
        case NpcType::BEAR:
            return std::make_shared<Bear>(name, x, y);
        default:
            throw exception::InvalidNpcTypeException("Unknown NPC type");
    }
}

NpcPtr NpcFactory::CreateFromString(const std::string& type_str, const std::string& name, double x, double y) {
    std::string type_lower = type_str;
    std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(), ::tolower);

    if (type_lower == "orc") {
        return Create(NpcType::ORC, name, x, y);
    } else if (type_lower == "knight") {
        return Create(NpcType::KNIGHT, name, x, y);
    } else if (type_lower == "bear") {
        return Create(NpcType::BEAR, name, x, y);
    } else {
        throw exception::InvalidNpcTypeException("Unknown NPC type: " + type_str);
    }
}

}
