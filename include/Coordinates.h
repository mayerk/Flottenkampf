#ifndef FLOTTENKAMPF_COORDINATES_H
#define FLOTTENKAMPF_COORDINATES_H

#include "Utility.h"

class Coordinates {
public:
    Coordinates();
    Coordinates(int x, int y);

    int getX() const;
    int getY() const;

    void generate(bool isHome);

private:
    int x;
    int y;
};


#endif //FLOTTENKAMPF_COORDINATES_H
