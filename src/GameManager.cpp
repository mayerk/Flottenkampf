#include "../include/GameManager.h"

GameManager::GameManager() {
    this->battlefield = new Battlefield();
}

GameManager::~GameManager() {
    delete this->battlefield;
}

void GameManager::start() {
    std::cout << std::endl << "----Game starts----" << std::endl;
    manager();
    printResults();
}

void GameManager::manager() {
    bool home = true;
    do {
        processAttack(home);
        std::cout << *this->battlefield << std::endl;
        home = !home;
    } while(isActive());
}

bool GameManager::isActive() {
    int shield1 = 0, shield2 = 0;
    for(Ship* ship: this->battlefield->getHomeFleet()) {
        shield1 += ship->getShield();
    }
    for(Ship* ship: this->battlefield->getOpponentFleet()) {
        shield2 += ship->getShield();
    }
    return (shield1 > 0 && shield2 > 0);
}

// Returns defending ship
void GameManager::processAttack(bool home) {
    int attackerIndex, defenderIndex;
    Coordinates old;
    if(home) {
        attackerIndex = Utility::getRandBetween(0, (int)this->battlefield->getHomeFleet().size()-1);
        defenderIndex = Utility::getRandBetween(0, (int)this->battlefield->getOpponentFleet().size()-1);
        if(this->battlefield->getHomeFleet().at(attackerIndex)->getShipType() != Utility::CRUISER) {
            if(this->battlefield->getHomeFleet().at(attackerIndex)->attack(this->battlefield->getOpponentFleet().at(defenderIndex))) {
                if(this->battlefield->getOpponentFleet().at(defenderIndex)->getShield() < 1) {
                    this->battlefield->removeShip(this->battlefield->getOpponentFleet().at(defenderIndex), defenderIndex);
                } else {
                    old = this->battlefield->getOpponentFleet().at(defenderIndex)->getCoordinates();
                    this->battlefield->moveShip(this->battlefield->getOpponentFleet().at(defenderIndex));
                    this->battlefield->update(old, this->battlefield->getOpponentFleet().at(defenderIndex));
                }
            }
        } else {
            bool success;
            do {
                defenderIndex = Utility::getRandBetween(0, (int)this->battlefield->getOpponentFleet().size()-1);
                success = this->battlefield->getHomeFleet().at(attackerIndex)->attack(this->battlefield->getOpponentFleet().at(defenderIndex));
                if(success) {
                    if(this->battlefield->getOpponentFleet().at(defenderIndex)->getShield() < 1) {
                        this->battlefield->removeShip(this->battlefield->getOpponentFleet().at(defenderIndex), defenderIndex);
                    } else {
                        old = this->battlefield->getOpponentFleet().at(defenderIndex)->getCoordinates();
                        this->battlefield->moveShip(this->battlefield->getOpponentFleet().at(defenderIndex));
                        this->battlefield->update(old, this->battlefield->getOpponentFleet().at(defenderIndex));
                    }
                }
            } while(success && isActive());
        }
    } else {
        attackerIndex = Utility::getRandBetween(0, (int)this->battlefield->getOpponentFleet().size()-1);
        defenderIndex = Utility::getRandBetween(0, (int)this->battlefield->getHomeFleet().size()-1);
        if(this->battlefield->getOpponentFleet().at(attackerIndex)->getShipType() != Utility::CRUISER) {
            if(this->battlefield->getOpponentFleet().at(attackerIndex)->attack(this->battlefield->getHomeFleet().at(defenderIndex))) {
                if(this->battlefield->getHomeFleet().at(defenderIndex)->getShield() < 1) {
                    this->battlefield->removeShip(this->battlefield->getHomeFleet().at(defenderIndex), defenderIndex);
                } else {
                    old = this->battlefield->getHomeFleet().at(defenderIndex)->getCoordinates();
                    this->battlefield->moveShip(this->battlefield->getHomeFleet().at(defenderIndex));
                    this->battlefield->update(old, this->battlefield->getHomeFleet().at(defenderIndex));
                }
            }
        } else {
            bool success;
            do {
                defenderIndex = Utility::getRandBetween(0, (int)this->battlefield->getHomeFleet().size()-1);
                success = this->battlefield->getOpponentFleet().at(attackerIndex)->attack(this->battlefield->getHomeFleet().at(defenderIndex));
                if(success) {
                    if(this->battlefield->getHomeFleet().at(defenderIndex)->getShield() < 1) {
                        this->battlefield->removeShip(this->battlefield->getHomeFleet().at(defenderIndex), defenderIndex);
                    } else {
                        old = this->battlefield->getHomeFleet().at(defenderIndex)->getCoordinates();
                        this->battlefield->moveShip(this->battlefield->getHomeFleet().at(defenderIndex));
                        this->battlefield->update(old, this->battlefield->getHomeFleet().at(defenderIndex));
                    }
                }
            } while(success && isActive());
        }
    }
}

void GameManager::printResults() {
    int sp = 0;
    std::cout << std::endl << "----Results----" << std::endl << "Winning fleet - ";
    if(this->battlefield->getHomeFleet().empty()) {
        std::cout << "Opponent fleet" << std::endl;
        for(Ship* ship: this->battlefield->getOpponentFleet()) {
            sp += ship->getShield();
        }
    } else {
        std::cout << "Home fleet" << std::endl;
        for(Ship* ship: this->battlefield->getHomeFleet()) {
            sp += ship->getShield();
        }
    }
    std::cout << "Total shield points left: " << sp << std::endl;
}
