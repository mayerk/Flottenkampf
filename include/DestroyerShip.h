#ifndef FLOTTENKAMPF_DESTROYERSHIP_H
#define FLOTTENKAMPF_DESTROYERSHIP_H

#include "Ship.h"

class DestroyerShip: public Ship{
public:
    DestroyerShip();
    virtual ~DestroyerShip();

    bool attack(Ship* other) override;
    char getFirstLetter() override;
};


#endif //FLOTTENKAMPF_DESTROYERSHIP_H
