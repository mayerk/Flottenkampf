#include "../include/Battlefield.h"

Battlefield::Battlefield() {
    for(auto& x: this->map) {
        for(auto &y: x) {
            y = nullptr;
        }
    }
}

void Battlefield::placeShip(Ship *ship) {
    this->map[ship->getCoordinates().getY()][ship->getCoordinates().getX()] = ship;
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

void Battlefield::removeShip(Ship *ship) {
    this->map[ship->getCoordinates().getY()][ship->getCoordinates().getX()] = nullptr;
    delete ship;
}
