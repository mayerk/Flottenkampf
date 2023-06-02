#include "../include/CruiserShip.h"

CruiserShip::CruiserShip(): Ship( 250, 8, 50) {
    this->type = Utility::CRUISER;
}

bool CruiserShip::attack(Ship *other) {
    int r = Utility::getRandBetween(1, 10);
    if(r < other->getSize()) {
        return false;
    }
    other->takeDamage(this->damage);
    return true;
}
