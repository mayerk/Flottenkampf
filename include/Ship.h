#ifndef FLOTTENKAMPF_SHIP_H
#define FLOTTENKAMPF_SHIP_H

#include <string>
#include "Utility.h"
#include "Coordinates.h"
#include <cmath>

class Ship {
public:
    Ship(int shield, int size, int damage);

    virtual ~Ship();

    Utility::SHIP_TYPE getShipType() const;
    Utility::FLEET_TYPE getFleetType() const;
    int getShield() const;
    int getSize() const;
    const Coordinates &getCoordinates() const;
    virtual char getFirstLetter() = 0;

    void setShield(int shield);
    void setCoordinates(const Coordinates &coordinates);
    void setFleetType(Utility::FLEET_TYPE fleetType);

    virtual bool attack(Ship* other) = 0;
    void takeDamage(int dmg);
    void gainExperience();

    friend std::ostream& operator<<(std::ostream& os, const Ship& ship);

protected:
    Utility::SHIP_TYPE shipType;
    Utility::FLEET_TYPE fleetType;
    Coordinates coordinates;
    int shield;
    int size;
    int damage;
    int experience;
};


#endif //FLOTTENKAMPF_SHIP_H
