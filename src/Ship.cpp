#include "../include/Ship.h"

Ship::Ship(int shield, int size, int damage) {
    this->shield = shield;
    this->size = size;
    this->damage = damage;
}

Utility::SHIP_TYPE Ship::getType() const {
    return type;
}

int Ship::getShield() const {
    return shield;
}

int Ship::getSize() const {
    return size;
}

const Coordinates &Ship::getCoordinates() const {
    return coordinates;
}

void Ship::setShield(int shield) {
    this->shield = shield;
}

void Ship::setCoordinates(const Coordinates &coordinates) {
    this->coordinates = coordinates;
}

void Ship::takeDamage(int dmg) {
    this->shield = (this->shield - dmg > 0) ? this->shield - dmg : 0;
}

std::ostream &operator<<(std::ostream &os, const Ship &ship) {
    switch (ship.getType()) {
        case Utility::HUNTER: {
            os << "Hunter";
            break;
        }
        case Utility::DESTROYER: {
            os << "Destroyer";
            break;
        }
        case Utility::CRUISER: {
            os << "Cruiser";
            break;
        }
    }
    return os;
}
