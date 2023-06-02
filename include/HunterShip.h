#ifndef FLOTTENKAMPF_HUNTERSHIP_H
#define FLOTTENKAMPF_HUNTERSHIP_H

#include "Ship.h"

class HunterShip: public Ship{
public:
    HunterShip();
    virtual ~HunterShip();

    bool attack(Ship* other) override;
    char getFirstLetter() override;
};


#endif //FLOTTENKAMPF_HUNTERSHIP_H
