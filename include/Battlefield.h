#ifndef FLOTTENKAMPF_BATTLEFIELD_H
#define FLOTTENKAMPF_BATTLEFIELD_H

#include <array>
#include "Ship.h"

class Battlefield {
public:
    Battlefield();

    void placeShip(Ship* ship);
    void removeShip(Ship* ship);

    friend std::ostream& operator<<(std::ostream& os, const Battlefield& battlefield);

private:
    std::array<std::array<Ship*, Utility::Data::HEIGHT>, Utility::Data::WIDTH> map;
};


#endif //FLOTTENKAMPF_BATTLEFIELD_H
