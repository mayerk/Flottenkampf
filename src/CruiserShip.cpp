#include "../include/CruiserShip.h"

CruiserShip::CruiserShip(): Ship( 250, 8, 50) {
    this->shipType = Utility::CRUISER;
}

CruiserShip::~CruiserShip() {}

bool CruiserShip::attack(Ship *other) {
    int r = Utility::getRandBetween(1, 10);
    if(r < other->getSize()) {
        return false;
    }
    other->takeDamage(this->damage);
    return true;
}

char CruiserShip::getFirstLetter() {
    return 'C';
}
