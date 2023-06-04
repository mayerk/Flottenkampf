#include "../include/Battlefield.h"

Battlefield::Battlefield() {
    for(auto& y: this->map) {
        for(auto& ship: y) {
            ship = nullptr;
        }
    }
    initialize();
}

Battlefield::~Battlefield() {
    for(Ship* ship: this->homeFleet) {
        delete ship;
        this->homeFleet.clear();
    }
    for(Ship* ship: this->opponentFleet) {
        delete ship;
        this->opponentFleet.clear();
    }
}

const std::vector<Ship *> &Battlefield::getHomeFleet() const {
    return homeFleet;
}

const std::vector<Ship *> &Battlefield::getOpponentFleet() const {
    return opponentFleet;
}

std::ostream &operator<<(std::ostream &os, const Battlefield &battlefield) {
    os << "------Map------" << std::endl;
    int i=0;
    for(auto& y: battlefield.map) {
        if(i != 7) {
            for(auto& ship: y) {
                if(ship != nullptr) {
                    os << ship->getFirstLetter();
                } else {
                    os << char(176);
                }
            }
        } else {
            os << "---------------";
        }
        os << std::endl;
        ++i;
    }
    return os;
}

void Battlefield::removeShip(Ship *ship, int index) {
    if(ship->getFleetType() == Utility::HOME) {
        this->homeFleet.erase(this->homeFleet.begin() + index);
    } else {
        this->opponentFleet.erase(this->opponentFleet.begin() + index);
    }
    this->map[ship->getCoordinates().getY()][ship->getCoordinates().getX()] = nullptr;
    delete ship;
    std::cout << "Ship was destroyed" << std::endl;
}

void Battlefield::initialize() {
    insertFleets();
    generateShipCoordinates();
}

void Battlefield::insertFleets() {
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
}

Ship *Battlefield::chooseShip() {
    int x = Utility::getInput("Please choose a battleship: (1)Hunter ship, (2)Destroyer ship, (3)Cruiser ship", 3);
    switch (x) {
        case 1: return new HunterShip();
        case 2: return new DestroyerShip();
        case 3: return new CruiserShip();
        default: break;
    }
    return nullptr;
}

void Battlefield::generateShipCoordinates() {
    for(Ship* ship: this->homeFleet) {
        Coordinates tmp = Coordinates();
        do {
            tmp.generate(true);
        } while(isShipAtCoordinates(tmp));
        try {
            ship->setCoordinates(tmp);
        } catch (const std::out_of_range& e) {
            std::cout << e.what();
        }
        this->map[tmp.getY()][tmp.getX()] = ship;
    }
    for(Ship* ship: this->opponentFleet) {
        Coordinates tmp = Coordinates();
        do {
            tmp.generate(false);
        } while(isShipAtCoordinates(tmp));
        try {
            ship->setCoordinates(tmp);
        } catch (const std::out_of_range& e) {
            std::cout << e.what();
        }
        this->map[tmp.getY()][tmp.getX()] = ship;
    }
}

bool Battlefield::isShipAtCoordinates(Coordinates coordinates) {
    // Home fleet
    if(coordinates.getY() <= 6) {
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

void Battlefield::moveShip(Ship* ship) {
    Coordinates newCoords = findValidCoords(ship);
    try {
        ship->setCoordinates(newCoords);
    } catch (const std::out_of_range& e) {
        std::cout << e.what();
    }
}

Coordinates Battlefield::findValidCoords(Ship* ship) {
    Coordinates current = ship->getCoordinates();
    std::vector<int> trys;
    int upperBorder = (ship->getFleetType() == Utility::HOME) ? 0 : 8;
    int lowerBorder = (ship->getFleetType() == Utility::HOME) ? 6 : 14;
    do {
        // 1..north, 2..east, 3..south, 4..west
        int x = Utility::getRandBetween(1, 4);
        switch (x) {
            case 1: {
                if(std::find(trys.begin(), trys.end(), 1) != trys.end()) {}
                else {
                    if(current.getY() > upperBorder && !isShipAtCoordinates({current.getX(), current.getY()-1})) {
                        return {current.getX(), current.getY()-1};
                    }
                    trys.emplace_back(1);
                }
                break;
            }
            case 2: {
                if(std::find(trys.begin(), trys.end(), 2) != trys.end()) {

                } else {
                    if(current.getX() < Utility::Data::WIDTH-1 && !isShipAtCoordinates({current.getX()+1, current.getY()})) {
                        return {current.getX()+1, current.getY()};
                    }
                    trys.emplace_back(2);
                }
                break;
            }
            case 3: {
                if(std::find(trys.begin(), trys.end(), 3) != trys.end()) {

                } else {
                    if(current.getY() < lowerBorder && !isShipAtCoordinates({current.getX(), current.getY()+1})) {
                        return {current.getX(), current.getY()+1};
                    }
                    trys.emplace_back(3);
                }
                break;
            }
            case 4: {
                if(std::find(trys.begin(), trys.end(), 4) != trys.end()) {

                } else {
                    if(current.getX() > 0 && !isShipAtCoordinates({current.getX()-1, current.getY()})) {
                        return {current.getX()-1, current.getY()};
                    }
                    trys.emplace_back(4);
                }
                break;
            }
            default: break;
        }
    } while (trys.size() < 4);
    return current;
}

void Battlefield::update(Coordinates old, Ship* ship) {
    this->map[old.getY()][old.getX()] = nullptr;
    this->map[ship->getCoordinates().getY()][ship->getCoordinates().getX()] = ship;
}
