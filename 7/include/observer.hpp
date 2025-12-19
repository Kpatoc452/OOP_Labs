#pragma once

#include "npc.hpp"
#include <vector>
#include <memory>
#include <fstream>

namespace game {

class CombatObserver {
public:
    virtual ~CombatObserver() = default;
    virtual void OnCombat(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed) = 0;
};

using ObserverPtr = std::shared_ptr<CombatObserver>;

class ConsoleObserver : public CombatObserver {
public:
    ConsoleObserver() = default;
    ~ConsoleObserver() override = default;

    void OnCombat(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed) override;
};

class FileObserver : public CombatObserver {
public:
    FileObserver(const std::string& filename);
    ~FileObserver() override;

    void OnCombat(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed) override;

private:
    std::ofstream file_;
};

class ObserverManager {
public:
    ObserverManager() = default;

    void Attach(ObserverPtr observer);
    void Detach(ObserverPtr observer);
    void Notify(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed);

private:
    std::vector<ObserverPtr> observers_;
};

}
