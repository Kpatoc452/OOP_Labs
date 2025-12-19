#include <iostream>

#include "game.hpp"

int main() {
    std::cout << "Balagur Fate 3" << std::endl;
    std::cout << "Map size: " << game::MAP_SIZE << "x" << game::MAP_SIZE << std::endl;
    std::cout << "Game duration: " << game::GAME_DURATION_SECONDS << " seconds" << std::endl;
    std::cout << "NPC count: " << game::NPC_COUNT << std::endl;
    std::cout << "\nStarting game..." << std::endl;

    game::Game game;
    game.Start();

    game.PrintSurvivors();

    std::cout << "\nGame finished. Check log.txt for combat log." << std::endl;

    return 0;
}
