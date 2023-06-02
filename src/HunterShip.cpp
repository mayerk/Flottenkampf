#include "../include/HunterShip.h"

HunterShip::HunterShip(): Ship( 75, 4, 30) {
    this->type = Utility::HUNTER;
}

bool HunterShip::attack(Ship *other) {
    int r = Utility::getRandBetween(1, 10);
    if(r < other->getSize()) {
        return false;
    }
    ((r >= 9) ? other->takeDamage(this->damage*2) : other->takeDamage(this->damage));
    return true;
}
