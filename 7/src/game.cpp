#include "game.hpp"
#include "factory.hpp"
#include "visitor.hpp"

#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

namespace game {

Game::Game() : running_(false) {
    observer_manager_.Attach(std::make_shared<ConsoleObserver>());
    observer_manager_.Attach(std::make_shared<FileObserver>("log.txt"));
}

Game::~Game() {
    Stop();
}

void Game::GenerateNpcs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> pos_dist(0, MAP_SIZE);
    std::uniform_int_distribution<> type_dist(0, 2);

    const NpcType types[] = {NpcType::ORC, NpcType::KNIGHT, NpcType::BEAR};
    const std::string type_names[] = {"Orc", "Knight", "Bear"};

    for (int i = 0; i < NPC_COUNT; ++i) {
        NpcType type = types[type_dist(gen)];
        double x = pos_dist(gen);
        double y = pos_dist(gen);
        std::string name = type_names[static_cast<int>(type)] + "_" + std::to_string(i);

        try {
            npcs_.push_back(NpcFactory::Create(type, name, x, y));
        } catch (const std::exception& e) {
            --i;
        }
    }
}

void Game::MovementThread() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle_dist(0, 2 * M_PI);

    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::unique_lock<std::shared_mutex> lock(npcs_mutex_);

        for (auto& npc : npcs_) {
            if (!npc->IsAlive()) {
                continue;
            }

            double angle = angle_dist(gen);
            double move_range = npc->GetMoveRange();
            double dx = std::cos(angle) * move_range * 0.1;
            double dy = std::sin(angle) * move_range * 0.1;

            npc->Move(dx, dy);
        }

        for (size_t i = 0; i < npcs_.size(); ++i) {
            if (!npcs_[i]->IsAlive()) {
                continue;
            }

            for (size_t j = i + 1; j < npcs_.size(); ++j) {
                if (!npcs_[j]->IsAlive()) {
                    continue;
                }

                double distance = npcs_[i]->DistanceTo(*npcs_[j]);
                double kill_range = npcs_[i]->GetKillRange();

                if (distance <= kill_range) {
                    std::lock_guard<std::mutex> combat_lock(combat_queue_mutex_);
                    combat_queue_.push({npcs_[i], npcs_[j]});
                }
            }
        }
    }
}

void Game::CombatThread() {
    CombatResolver resolver;

    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        CombatTask task;
        {
            std::lock_guard<std::mutex> lock(combat_queue_mutex_);
            if (combat_queue_.empty()) {
                continue;
            }
            task = combat_queue_.front();
            combat_queue_.pop();
        }

        if (!task.attacker->IsAlive() || !task.defender->IsAlive()) {
            continue;
        }

        resolver.SetAttacker(task.attacker.get());
        task.defender->Accept(resolver);

        bool defender_should_die = false;
        bool attacker_should_die = false;

        if (resolver.IsDefenderKilled()) {
            int attacker_roll = RollDice();
            int defender_roll = RollDice();

            if (attacker_roll > defender_roll) {
                defender_should_die = true;
            }
        }

        if (resolver.IsAttackerKilled()) {
            int attacker_roll = RollDice();
            int defender_roll = RollDice();

            if (defender_roll > attacker_roll) {
                attacker_should_die = true;
            }
        }

        if (defender_should_die || attacker_should_die) {
            std::unique_lock<std::shared_mutex> lock(npcs_mutex_);

            if (defender_should_die) {
                task.defender->Kill();
            }

            if (attacker_should_die) {
                task.attacker->Kill();
            }

            observer_manager_.Notify(*task.attacker, *task.defender, attacker_should_die, defender_should_die);
        }
    }
}

void Game::PrintThread() {
    auto start_time = std::chrono::steady_clock::now();

    while (running_) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto current_time = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();

        std::shared_lock<std::shared_mutex> lock(npcs_mutex_);

        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
        std::cout << "\n=== Map at " << elapsed << "s ===" << std::endl;

        std::vector<std::vector<char>> map(MAP_SIZE, std::vector<char>(MAP_SIZE, '.'));

        int alive_count = 0;
        for (const auto& npc : npcs_) {
            if (npc->IsAlive()) {
                int x = static_cast<int>(npc->GetX());
                int y = static_cast<int>(npc->GetY());

                if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                    char symbol = '?';
                    switch (npc->GetType()) {
                        case NpcType::ORC: symbol = 'O'; break;
                        case NpcType::KNIGHT: symbol = 'K'; break;
                        case NpcType::BEAR: symbol = 'B'; break;
                    }
                    map[y][x] = symbol;
                    alive_count++;
                }
            }
        }

        std::cout << "Alive: " << alive_count << " / " << NPC_COUNT << std::endl;
        std::cout << "  ";
        for (int x = 0; x < MAP_SIZE; x += 10) {
            std::cout << std::setw(10) << x;
        }
        std::cout << std::endl;

        for (int y = 0; y < MAP_SIZE; y += 2) {
            std::cout << std::setw(2) << y << " ";
            for (int x = 0; x < MAP_SIZE; x += 2) {
                std::cout << map[y][x];
            }
            std::cout << std::endl;
        }
    }
}

int Game::RollDice() const {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    static thread_local std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
}

void Game::Start() {
    GenerateNpcs();

    running_ = true;

    std::thread movement_thread(&Game::MovementThread, this);
    std::thread combat_thread(&Game::CombatThread, this);
    std::thread print_thread(&Game::PrintThread, this);

    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION_SECONDS));

    running_ = false;

    movement_thread.join();
    combat_thread.join();
    print_thread.join();
}

void Game::Stop() {
    running_ = false;
}

void Game::PrintSurvivors() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex_);

    std::cout << "\n=== Survivors ===" << std::endl;
    int survivor_count = 0;

    for (const auto& npc : npcs_) {
        if (npc->IsAlive()) {
            std::cout << "  " << npc->GetTypeName() << " \"" << npc->GetName()
                      << "\" at (" << npc->GetX() << ", " << npc->GetY() << ")" << std::endl;
            survivor_count++;
        }
    }

    std::cout << "\nTotal survivors: " << survivor_count << " out of " << NPC_COUNT << std::endl;
}

}
