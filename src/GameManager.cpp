#include "../include/GameManager.h"

GameManager::GameManager() {
    this->battlefield = new Battlefield();
}

void GameManager::start() {
    while (manager());
}

bool GameManager::manager() {
    insertFleet();
    std::cout << *this->battlefield << std::endl;
    printFleets();
    startBattle();
    std::cout << *this->battlefield << std::endl;
    printResult();

    bool err = false;
    char input;
    do {
        std::cout << "Do you want to play again? (y/n)";
        std::cin >> input;
        if(input != 'y' && input != 'n') {
            err = true;
            std::cout << "Incorrect input!" << std::endl;
        } else {
            err = false;
        }
    } while (err);

    return (input == 'y');
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
                this->homeFleet.back()->setFleetType(Utility::HOME);
            } else {
                this->opponentFleet.emplace_back(chooseShip());
                this->opponentFleet.back()->setFleetType(Utility::OPPONENT);
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
        this->battlefield->placeShip(ship);
    }
    for(Ship* ship: this->opponentFleet) {
        Coordinates tmp = Coordinates();
        do {
            tmp.generate(false);
        } while(isShipAtCoordinates(tmp, false));
        ship->setCoordinates(tmp);
        this->battlefield->placeShip(ship);
    }
}

void GameManager::printFleets() {
    std::cout << "--- Home fleet ---" << std::endl;
    int i=1;
    for(Ship* ship: this->homeFleet) {
        std::cout << "(" << i << ") " << *ship << std::endl;
        ++i;
    }
    i = 1;
    std::cout << "--- Opposition fleet ---" << std::endl;
    for(Ship* ship: this->opponentFleet) {
        std::cout << "(" << i << ") " << *ship << std::endl;
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
        if(this->homeFleet.at(attackerIndex)->getShipType() != Utility::CRUISER) {
            if(this->homeFleet.at(attackerIndex)->attack(this->opponentFleet.at(defenderIndex))) {
                if(this->opponentFleet.at(defenderIndex)->getShield() < 1) {
                    removeShip(this->opponentFleet.at(defenderIndex), defenderIndex);
                }
            }
        } else {
            bool success;
            do {
                defenderIndex = Utility::getRandBetween(0, (int)this->opponentFleet.size()-1);
                success = this->homeFleet.at(attackerIndex)->attack(this->opponentFleet.at(defenderIndex));
                if(success) {
                    if(this->opponentFleet.at(defenderIndex)->getShield() < 1) {
                        removeShip(this->opponentFleet.at(defenderIndex), defenderIndex);
                    }
                }
            } while(success && isActive());
        }
    } else {
        attackerIndex = Utility::getRandBetween(0, (int)this->opponentFleet.size()-1);
        defenderIndex = Utility::getRandBetween(0, (int)this->homeFleet.size()-1);
        if(this->opponentFleet.at(attackerIndex)->getShipType() != Utility::CRUISER) {
            if(this->opponentFleet.at(attackerIndex)->attack(this->homeFleet.at(defenderIndex))) {
                if(this->homeFleet.at(defenderIndex)->getShield() < 1) {
                    removeShip(this->homeFleet.at(defenderIndex), defenderIndex);
                }
            }
        } else {
            bool success;
            do {
                defenderIndex = Utility::getRandBetween(0, (int)this->homeFleet.size()-1);
                success = this->opponentFleet.at(attackerIndex)->attack(this->homeFleet.at(defenderIndex));
                if(success) {
                    if(this->homeFleet.at(defenderIndex)->getShield() < 1) {
                        removeShip(this->homeFleet.at(defenderIndex), defenderIndex);
                    }
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

void GameManager::removeShip(Ship *ship, int index) {
    if(ship->getFleetType() == Utility::HOME) {
        this->homeFleet.erase(this->homeFleet.begin() + index);
    } else {
        this->opponentFleet.erase(this->opponentFleet.begin() + index);
    }
    this->battlefield->removeShip(ship);
    std::cout << "Ship was destroyed" << std::endl;
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


