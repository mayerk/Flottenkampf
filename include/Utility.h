#ifndef FLOTTENKAMPF_UTILITY_H
#define FLOTTENKAMPF_UTILITY_H

#include <string>
#include <iostream>

namespace Utility {

    namespace Data {
        const int WIDTH = 15;
        const int HEIGHT = 15;
    }

    enum SHIP_TYPE {HUNTER, DESTROYER, CRUISER};

    int getInput(std::string message, int range);
    int getRandBetween(int min, int max);
};


#endif //FLOTTENKAMPF_UTILITY_H
