#ifndef FLOTTENKAMPF_CRUISERSHIP_H
#define FLOTTENKAMPF_CRUISERSHIP_H

#include "Ship.h"

class CruiserShip: public Ship{
public:
    CruiserShip();
    virtual ~CruiserShip();

    bool attack(Ship* other) override;
    char getFirstLetter() override;
};


#endif //FLOTTENKAMPF_CRUISERSHIP_H
