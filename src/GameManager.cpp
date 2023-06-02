#include "../include/GameManager.h"

void GameManager::start() {
    while (manager());
    int x;
    std::cin >> x;
}

bool GameManager::manager() {
    // TODO: Play again?
    insertFleet();
    initializeMap();
    printFleets();
    //startBattle();
    //printFleets();
    //printResult();
    return true;
}

void GameManager::initializeMap() {
    for(auto& x: this->map) {
        for(auto &y: x) {
            y = nullptr;
        }
    }
}

void GameManager::insertFleet() {
    int size = Utility::getInput("Please choose a fleet size", 9);

    for(int i=0; i < 2; ++i) {
        std::cout << "Now choosing battleships for fleet " << i+1;
        if(i == 0) {
            std::cout << " (Home fleet)" << std::endl;
        } else {
            std::cout << " (Opposition fleet)" << std::endl;
        }
        for(int j=0; j < size; ++j) {
            if(i == 0) {
                this->homeFleet.emplace_back(chooseShip());
            } else {
                this->opponentFleet.emplace_back(chooseShip());
            }
        }
    }
    generateShipCoordinates();
}

Ship *GameManager::chooseShip() {
    int x = Utility::getInput("Please choose a battleship: (1)Hunter ship, (2)Destroyer ship, (3)Cruiser ship", 3);
    switch (x) {
        case 1: return new HunterShip();
        case 2: return new DestroyerShip();
        case 3: return new CruiserShip();
        default: break;
    }
    return nullptr;
}

void GameManager::generateShipCoordinates() {
    for(Ship* ship: this->homeFleet) {
        Coordinates tmp = Coordinates();
        do {
            tmp.generate(true);
        } while(isShipAtCoordinates(tmp, true));
        ship->setCoordinates(tmp);
        this->map[ship->getCoordinates().getY()][ship->getCoordinates().getX()] = ship;
    }
    for(Ship* ship: this->opponentFleet) {
        Coordinates tmp = Coordinates();
        do {
            tmp.generate(false);
        } while(isShipAtCoordinates(tmp, false));
        ship->setCoordinates(tmp);
        this->map[ship->getCoordinates().getY()][ship->getCoordinates().getX()] = ship;
    }
}

void GameManager::printFleets() {
    std::cout << std::endl << "--- Home fleet ---" << std::endl;
    int i=1;
    for(Ship* ship: this->homeFleet) {
        std::cout << "(" << i << ") " << *ship << " - " << ship->getCoordinates().getX() << " | " << ship->getCoordinates().getY() << std::endl;
        ++i;
    }
    i = 1;
    std::cout << "--- Opposition fleet ---" << std::endl;
    for(Ship* ship: this->opponentFleet) {
        std::cout << "(" << i << ") " << *ship << " - " << ship->getCoordinates().getX() << " | " << ship->getCoordinates().getY() << std::endl;
        ++i;
    }
}

void GameManager::startBattle() {
    bool home = true;
    do {
        processAttack(home);
        home = !home;
    } while(isActive());
}

void GameManager::processAttack(bool home) {
    int attackerIndex, defenderIndex;
    if(home) {
        attackerIndex = Utility::getRandBetween(0, (int)this->homeFleet.size()-1);
        defenderIndex = Utility::getRandBetween(0, (int)this->opponentFleet.size()-1);
        if(this->homeFleet.at(attackerIndex)->getType() != Utility::CRUISER) {
            std::cout << *this->homeFleet.at(attackerIndex) << "(Home) attacks " << *this->opponentFleet.at(defenderIndex) << "(Opponent)";
            if(this->homeFleet.at(attackerIndex)->attack(this->opponentFleet.at(defenderIndex))) {
                std::cout << " - The attack was successful" << std::endl;
                if(this->opponentFleet.at(defenderIndex)->getShield() < 1) {
                    this->opponentFleet.erase(this->opponentFleet.begin() + defenderIndex);
                    std::cout << "Ship was destroyed" << std::endl;
                }
            } else {
                std::cout << " - " << *this->homeFleet.at(attackerIndex) << " missed it's target" << std::endl;
            }
        } else {
            bool success;
            do {
                defenderIndex = Utility::getRandBetween(0, (int)this->opponentFleet.size()-1);
                std::cout << *this->homeFleet.at(attackerIndex) << "(Home) attacks " << *this->opponentFleet.at(defenderIndex) << "(Opponent)";
                success = this->homeFleet.at(attackerIndex)->attack(this->opponentFleet.at(defenderIndex));
                if(success) {
                    std::cout << " - The attack was successful" << std::endl;
                    if(this->opponentFleet.at(defenderIndex)->getShield() < 1) {
                        this->opponentFleet.erase(this->opponentFleet.begin() + defenderIndex);
                        std::cout << "Ship was destroyed" << std::endl;
                    }
                } else {
                    std::cout << " - " << *this->homeFleet.at(attackerIndex) << " missed it's target" << std::endl;
                }
            } while(success && isActive());
        }
    } else {
        attackerIndex = Utility::getRandBetween(0, (int)this->opponentFleet.size()-1);
        defenderIndex = Utility::getRandBetween(0, (int)this->homeFleet.size()-1);
        if(this->opponentFleet.at(attackerIndex)->getType() != Utility::CRUISER) {
            std::cout << *this->opponentFleet.at(attackerIndex) << "(Opponent) attacks " << *this->homeFleet.at(defenderIndex) << "(Home)";
            if(this->opponentFleet.at(attackerIndex)->attack(this->homeFleet.at(defenderIndex))) {
                std::cout << " - The attack was successful" << std::endl;
                if(this->homeFleet.at(defenderIndex)->getShield() < 1) {
                    this->homeFleet.erase(this->homeFleet.begin() + defenderIndex);
                    std::cout << "Ship was destroyed" << std::endl;
                }
            } else {
                std::cout << " - " << *this->opponentFleet.at(attackerIndex) << " missed it's target" << std::endl;
            }
        } else {
            bool success;
            do {
                defenderIndex = Utility::getRandBetween(0, (int)this->homeFleet.size()-1);
                std::cout << *this->opponentFleet.at(attackerIndex) << "(Opponent) attacks " << *this->homeFleet.at(defenderIndex) << "(Home)";
                success = this->opponentFleet.at(attackerIndex)->attack(this->homeFleet.at(defenderIndex));
                if(success) {
                    std::cout << " - The attack was successful" << std::endl;
                    if(this->homeFleet.at(defenderIndex)->getShield() < 1) {
                        this->homeFleet.erase(this->homeFleet.begin() + defenderIndex);
                        std::cout << "Ship was destroyed" << std::endl;
                    }
                } else {
                    std::cout << " - " << *this->opponentFleet.at(attackerIndex) << " missed it's target" << std::endl;
                }
            } while(success && isActive());
        }
    }
}

bool GameManager::isActive() {
    int shield1 = 0, shield2 = 0;
    for(Ship* ship: this->homeFleet) {
        shield1 += ship->getShield();
    }
    for(Ship* ship: this->opponentFleet) {
        shield2 += ship->getShield();
    }
    return (shield1 > 0 && shield2 > 0);
}

bool GameManager::isShipAtCoordinates(Coordinates coordinates, bool isHome) {
    if(isHome) {
        for(Ship* ship: this->homeFleet) {
            if(ship->getCoordinates().getX() == coordinates.getX() && ship->getCoordinates().getY() == coordinates.getY()) {
                return true;
            }
        }
    } else {
        for(Ship* ship: this->opponentFleet) {
            if(ship->getCoordinates().getX() == coordinates.getX() && ship->getCoordinates().getY() == coordinates.getY()) {
                return true;
            }
        }
    }
    return false;
}

void GameManager::printResult() {
    int sp = 0;
    std::cout << std::endl << "Winning fleet - ";
    if(this->homeFleet.empty()) {
        std::cout << "Opponent fleet" << std::endl;
        for(Ship* ship: this->opponentFleet) {
            sp += ship->getShield();
        }
    } else {
        std::cout << "Home fleet" << std::endl;
        for(Ship* ship: this->homeFleet) {
            sp += ship->getShield();
        }
    }
    std::cout << "Total shield points left: " << sp << std::endl;
}

