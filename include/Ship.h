#ifndef FLOTTENKAMPF_SHIP_H
#define FLOTTENKAMPF_SHIP_H

#include <string>
#include "Utility.h"
#include "Coordinates.h"

class Ship {
public:
    Ship(int shield, int size, int damage);

    Utility::SHIP_TYPE getType() const;
    int getShield() const;
    int getSize() const;
    const Coordinates &getCoordinates() const;

    void setShield(int shield);
    void setCoordinates(const Coordinates &coordinates);

    virtual bool attack(Ship* other) = 0;
    void takeDamage(int dmg);

    friend std::ostream& operator<<(std::ostream& os, const Ship& ship);

protected:
    Utility::SHIP_TYPE type;
    int shield;
    int size;
    int damage;
    Coordinates coordinates;
};


#endif //FLOTTENKAMPF_SHIP_H
