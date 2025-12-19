#pragma once

#include "npc.hpp"
#include "observer.hpp"

#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <atomic>

namespace game {

constexpr int MAP_SIZE = 100;
constexpr int GAME_DURATION_SECONDS = 30;
constexpr int NPC_COUNT = 50;

struct CombatTask {
    NpcPtr attacker;
    NpcPtr defender;
};

class Game {
public:
    Game();
    ~Game();

    void Start();
    void Stop();
    void PrintSurvivors() const;

private:
    void GenerateNpcs();
    void MovementThread();
    void CombatThread();
    void PrintThread();

    int RollDice() const;

    std::vector<NpcPtr> npcs_;
    std::queue<CombatTask> combat_queue_;

    mutable std::shared_mutex npcs_mutex_;
    std::mutex combat_queue_mutex_;
    std::mutex cout_mutex_;

    std::atomic<bool> running_;

    ObserverManager observer_manager_;
};

}
