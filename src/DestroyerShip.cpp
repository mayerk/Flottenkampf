#include "../include/DestroyerShip.h"

DestroyerShip::DestroyerShip(): Ship(150, 6, 60) {
    this->type = Utility::DESTROYER;
}

bool DestroyerShip::attack(Ship *other) {
    int r = Utility::getRandBetween(1, 10);
    // Attack is 2 points easier
    if(r < other->getSize()-2) {
        return false;
    }
    other->takeDamage(this->damage);
    return true;
}
