#include "../include/DestroyerShip.h"

DestroyerShip::DestroyerShip(): Ship(150, 6, 60) {
    this->shipType = Utility::DESTROYER;
}

DestroyerShip::~DestroyerShip() {}

bool DestroyerShip::attack(Ship *other) {
    std::cout << *this << ((this->getFleetType() == Utility::HOME) ? "(Home)" : "(Opponent)") << " attacks " << *other << ((other->getFleetType() == Utility::HOME) ? "(Home)" : "(Opponent)");
    float damageMultiplier = 1;
    // Damage reduction depending on range
    if(other->getCoordinates().getY() - this->getCoordinates().getY() > 10) {
        damageMultiplier = 0.6;
    } else if(other->getCoordinates().getY() - this->getCoordinates().getY() > 6) {
        damageMultiplier = 0.8;
    }
    int r = Utility::getRandBetween(1, 10);
    // Attack is 2 points easier
    if(r < other->getSize()-2) {
        std::cout << " - Attack missed it's target" << std::endl;
        return false;
    }
    std::cout << " - The attack was successful" << std::endl;
    other->takeDamage(roundf(this->damage*damageMultiplier));
    return true;
}

char DestroyerShip::getFirstLetter() {
    return 'D';
}
