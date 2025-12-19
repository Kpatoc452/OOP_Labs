#include "editor.hpp"
#include "factory.hpp"
#include "visitor.hpp"
#include "exceptions.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace game {

Editor::Editor() {}

void Editor::AddNpc(NpcPtr npc) {
    for (const auto& existing : npcs_) {
        if (existing->GetName() == npc->GetName()) {
            throw exception::DuplicateNameException("NPC with name '" + npc->GetName() + "' already exists");
        }
    }
    npcs_.push_back(npc);
}

void Editor::RemoveNpc(const std::string& name) {
    npcs_.erase(
        std::remove_if(npcs_.begin(), npcs_.end(),
            [&name](const NpcPtr& npc) { return npc->GetName() == name; }),
        npcs_.end()
    );
}

void Editor::PrintNpcs() const {
    if (npcs_.empty()) {
        std::cout << "No NPCs in the editor." << std::endl;
        return;
    }

    std::cout << "NPCs in the editor:" << std::endl;
    for (const auto& npc : npcs_) {
        if (npc->IsAlive()) {
            std::cout << "  " << npc->GetTypeName() << " \"" << npc->GetName()
                      << "\" at (" << npc->GetX() << ", " << npc->GetY() << ")" << std::endl;
        }
    }
}

void Editor::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw exception::FileException("Cannot open file for writing: " + filename);
    }

    for (const auto& npc : npcs_) {
        if (npc->IsAlive()) {
            file << npc->GetTypeName() << " " << npc->GetName() << " "
                 << npc->GetX() << " " << npc->GetY() << std::endl;
        }
    }

    file.close();
}

void Editor::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw exception::FileException("Cannot open file for reading: " + filename);
    }

    npcs_.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, name;
        double x, y;

        if (iss >> type >> name >> x >> y) {
            try {
                NpcPtr npc = NpcFactory::CreateFromString(type, name, x, y);
                npcs_.push_back(npc);
            } catch (const std::exception& e) {
                std::cerr << "Error loading NPC: " << e.what() << std::endl;
            }
        }
    }

    file.close();
}

void Editor::StartCombat(double range, ObserverManager& observer_manager) {
    CombatResolver resolver;

    for (size_t i = 0; i < npcs_.size(); ++i) {
        if (!npcs_[i]->IsAlive()) {
            continue;
        }

        for (size_t j = i + 1; j < npcs_.size(); ++j) {
            if (!npcs_[j]->IsAlive()) {
                continue;
            }

            double distance = npcs_[i]->DistanceTo(*npcs_[j]);
            if (distance <= range) {
                resolver.SetAttacker(npcs_[i].get());
                npcs_[j]->Accept(resolver);

                bool defender_killed = resolver.IsDefenderKilled();
                bool attacker_killed = resolver.IsAttackerKilled();

                if (defender_killed || attacker_killed) {
                    observer_manager.Notify(*npcs_[i], *npcs_[j], attacker_killed, defender_killed);
                }

                if (defender_killed) {
                    npcs_[j]->Kill();
                }

                if (attacker_killed) {
                    npcs_[i]->Kill();
                }
            }
        }
    }

    npcs_.erase(
        std::remove_if(npcs_.begin(), npcs_.end(),
            [](const NpcPtr& npc) { return !npc->IsAlive(); }),
        npcs_.end()
    );
}

size_t Editor::GetNpcCount() const {
    return npcs_.size();
}

NpcPtr Editor::FindNpc(const std::string& name) const {
    for (const auto& npc : npcs_) {
        if (npc->GetName() == name) {
            return npc;
        }
    }
    return nullptr;
}

}
