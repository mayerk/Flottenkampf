#include "../include/CruiserShip.h"

CruiserShip::CruiserShip(): Ship( 250, 8, 50) {
    this->shipType = Utility::CRUISER;
}

CruiserShip::~CruiserShip() {}

bool CruiserShip::attack(Ship *other) {
    std::cout << *this << ((this->getFleetType() == Utility::HOME) ? "(Home)" : "(Opponent)") << " attacks " << *other << ((other->getFleetType() == Utility::HOME) ? "(Home)" : "(Opponent)");
    float damageMultiplier = 1;
    // Damage reduction depending on range
    if(other->getCoordinates().getY() - this->getCoordinates().getY() > 10) {
        damageMultiplier = 0.6;
    } else if(other->getCoordinates().getY() - this->getCoordinates().getY() > 6) {
        damageMultiplier = 0.8;
    }
    int r = Utility::getRandBetween(1, 10);
    if(r < other->getSize()) {
        std::cout << " - Attack missed it's target" << std::endl;
        return false;
    }
    std::cout << " - The attack was successful" << std::endl;
    this->gainExperience();
    if(this->experience > 3) {
        int rand = Utility::getRandBetween(1, 2);
        // Special ability - heal
        try {
            other->takeDamage(roundf(this->damage*damageMultiplier));
        } catch (const std::out_of_range& e) {
            std::cout << e.what();
        }
        if(rand == 1) {
            try {
                this->setShield(this->shield + 20);
            } catch (const std::out_of_range& e) {
                std::cout << e.what();
            }
        }
    }
    return true;
}

char CruiserShip::getFirstLetter() {
    return 'C';
}
