#ifndef FLOTTENKAMPF_BATTLEFIELD_H
#define FLOTTENKAMPF_BATTLEFIELD_H

#include <array>
#include "Ship.h"

class Battlefield {
    Battlefield();

private:
    std::array<std::array<Ship*, Utility::Data::HEIGHT>, Utility::Data::WIDTH> map;
};


#endif //FLOTTENKAMPF_BATTLEFIELD_H
