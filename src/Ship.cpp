#include "../include/Ship.h"

Ship::Ship(int shield, int size, int damage) {
    this->shield = shield;
    this->size = size;
    this->damage = damage;
    this->experience = 0;
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
    if(shield < 0) {
        throw std::out_of_range("Parameter is out of range");
    }
    this->shield = shield;
}

void Ship::setCoordinates(const Coordinates &coordinates) {
    if(coordinates.getX() < 0 || coordinates.getX() > Utility::Data::WIDTH-1 || coordinates.getY() < 0 || coordinates.getY() > Utility::Data::HEIGHT-1) {
        throw std::out_of_range("Parameter is out of range");
    }
    this->coordinates = coordinates;
}

void Ship::takeDamage(int dmg) {
    if(dmg < 0) {
        throw std::out_of_range("Not able to take negative damage");
    }
    this->shield = (this->shield - dmg > 0) ? this->shield - dmg : 0;
}

void Ship::gainExperience() {
    this->experience++;
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
