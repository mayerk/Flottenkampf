#include "../include/Ship.h"

Ship::Ship(int shield, int size, int damage) {
    this->shield = shield;
    this->size = size;
    this->damage = damage;
}

Ship::~Ship() {}

Utility::SHIP_TYPE Ship::getShipType() const {
    return shipType;
}

Utility::FLEET_TYPE Ship::getFleetType() const {
    return fleetType;
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

void Ship::setFleetType(Utility::FLEET_TYPE fleetType) {
    this->fleetType = fleetType;
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
    switch (ship.getShipType()) {
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
