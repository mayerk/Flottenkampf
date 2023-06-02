#ifndef FLOTTENKAMPF_HUNTERSHIP_H
#define FLOTTENKAMPF_HUNTERSHIP_H

#include "Ship.h"

class HunterShip: public Ship{
public:
    HunterShip();

    bool attack(Ship* other) override;
};


#endif //FLOTTENKAMPF_HUNTERSHIP_H
