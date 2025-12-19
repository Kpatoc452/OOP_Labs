#include <iostream>

#include "editor.hpp"
#include "factory.hpp"
#include "observer.hpp"
#include "exceptions.hpp"

int main() {
    try {
        game::Editor editor;

        std::cout << "Balagur Fate 3" << std::endl << std::endl;

        std::cout << "Adding NPCs to the dungeon..." << std::endl;
        editor.AddNpc(game::NpcFactory::Create(game::NpcType::ORC, "Grom", 100, 100));
        editor.AddNpc(game::NpcFactory::Create(game::NpcType::KNIGHT, "Arthur", 120, 105));
        editor.AddNpc(game::NpcFactory::Create(game::NpcType::BEAR, "Mishka", 250, 250));
        editor.AddNpc(game::NpcFactory::Create(game::NpcType::ORC, "Thrall", 260, 255));
        editor.AddNpc(game::NpcFactory::Create(game::NpcType::KNIGHT, "Lancelot", 400, 400));
        editor.AddNpc(game::NpcFactory::Create(game::NpcType::BEAR, "Baloo", 410, 395));

        std::cout << std::endl;
        editor.PrintNpcs();

        std::cout << std::endl << "Saving NPCs to file 'dungeon.txt'..." << std::endl;
        editor.SaveToFile("dungeon.txt");

        std::cout << std::endl << "Starting Combat (range = 50 meters)" << std::endl << std::endl;

        game::ObserverManager observer_manager;
        auto console_observer = std::make_shared<game::ConsoleObserver>();
        auto file_observer = std::make_shared<game::FileObserver>("log.txt");

        observer_manager.Attach(console_observer);
        observer_manager.Attach(file_observer);

        editor.StartCombat(50.0, observer_manager);

        std::cout << std::endl << "After Combat" << std::endl << std::endl;
        editor.PrintNpcs();

        std::cout << std::endl << "Loading NPCs from file 'dungeon.txt'..." << std::endl;
        game::Editor editor2;
        editor2.LoadFromFile("dungeon.txt");

        std::cout << std::endl << "Loaded NPCs:" << std::endl;
        editor2.PrintNpcs();

    } catch (const exception::InvalidCoordinatesException& e) {
        std::cerr << "Coordinate error: " << e.what() << std::endl;
        return 1;
    } catch (const exception::DuplicateNameException& e) {
        std::cerr << "Duplicate name error: " << e.what() << std::endl;
        return 1;
    } catch (const exception::FileException& e) {
        std::cerr << "File error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
