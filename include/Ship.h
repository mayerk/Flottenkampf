#ifndef FLOTTENKAMPF_SHIP_H
#define FLOTTENKAMPF_SHIP_H

#include <string>
#include "Utility.h"
#include "Coordinates.h"

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

    virtual bool attack(Ship* other) = 0;
    // TODO: evtl -= operator overloading
    void takeDamage(int dmg);

    friend std::ostream& operator<<(std::ostream& os, const Ship& ship);

    void setFleetType(Utility::FLEET_TYPE fleetType);

protected:
    Utility::SHIP_TYPE shipType;
    Utility::FLEET_TYPE fleetType;
    int shield;
    int size;
    int damage;
    Coordinates coordinates;
};


#endif //FLOTTENKAMPF_SHIP_H
