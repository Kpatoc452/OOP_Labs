#pragma once

#include "npc.hpp"
#include "observer.hpp"
#include <vector>
#include <string>

namespace game {

class Editor {
public:
    Editor();

    void AddNpc(NpcPtr npc);
    void RemoveNpc(const std::string& name);
    void PrintNpcs() const;
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void StartCombat(double range, ObserverManager& observer_manager);

    size_t GetNpcCount() const;
    NpcPtr FindNpc(const std::string& name) const;

private:
    std::vector<NpcPtr> npcs_;
};

}
