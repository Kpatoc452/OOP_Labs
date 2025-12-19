#include "observer.hpp"
#include "exceptions.hpp"

#include <iostream>
#include <algorithm>

namespace game {

void ConsoleObserver::OnCombat(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed) {
    if (defender_killed) {
        std::cout << attacker.GetTypeName() << " " << attacker.GetName()
                  << " killed " << defender.GetTypeName() << " " << defender.GetName() << std::endl;
    }

    if (attacker_killed) {
        std::cout << defender.GetTypeName() << " " << defender.GetName()
                  << " killed " << attacker.GetTypeName() << " " << attacker.GetName() << std::endl;
    }
}

FileObserver::FileObserver(const std::string& filename)
    : file_(filename, std::ios::out | std::ios::app) {
    if (!file_.is_open()) {
        throw exception::FileException("Cannot open file: " + filename);
    }
}

FileObserver::~FileObserver() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileObserver::OnCombat(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed) {
    if (defender_killed) {
        file_ << attacker.GetTypeName() << " " << attacker.GetName()
              << " killed " << defender.GetTypeName() << " " << defender.GetName() << std::endl;
    }

    if (attacker_killed) {
        file_ << defender.GetTypeName() << " " << defender.GetName()
              << " killed " << attacker.GetTypeName() << " " << attacker.GetName() << std::endl;
    }
}

void ObserverManager::Attach(ObserverPtr observer) {
    observers_.push_back(observer);
}

void ObserverManager::Detach(ObserverPtr observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void ObserverManager::Notify(const Npc& attacker, const Npc& defender, bool attacker_killed, bool defender_killed) {
    for (auto& observer : observers_) {
        observer->OnCombat(attacker, defender, attacker_killed, defender_killed);
    }
}

}
