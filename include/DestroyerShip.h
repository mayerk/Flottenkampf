#ifndef FLOTTENKAMPF_DESTROYERSHIP_H
#define FLOTTENKAMPF_DESTROYERSHIP_H

#include "Ship.h"

class DestroyerShip: public Ship{
public:
    DestroyerShip();

    bool attack(Ship* other) override;
};


#endif //FLOTTENKAMPF_DESTROYERSHIP_H
