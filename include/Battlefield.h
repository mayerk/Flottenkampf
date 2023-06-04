#ifndef FLOTTENKAMPF_BETTER_BATTLEFIELD_H
#define FLOTTENKAMPF_BETTER_BATTLEFIELD_H

#include <array>
#include <vector>
#include <algorithm>
#include "Ship.h"
#include "DestroyerShip.h"
#include "CruiserShip.h"
#include "HunterShip.h"
#include "Utility.h"

class Battlefield {
public:
    Battlefield();

    ~Battlefield();

    const std::vector<Ship *> &getHomeFleet() const;
    const std::vector<Ship *> &getOpponentFleet() const;

    friend std::ostream& operator<<(std::ostream& os, const Battlefield& battlefield);

    void removeShip(Ship* ship, int index);
    void moveShip(Ship* ship);
    Coordinates findValidCoords(Ship* ship);
    void update(Coordinates old, Ship* ship);

private:
    void initialize();
    void insertFleets();
    Ship* chooseShip();
    void generateShipCoordinates();
    bool isShipAtCoordinates(Coordinates coordinates);

    std::array<std::array<Ship*, Utility::Data::HEIGHT>, Utility::Data::WIDTH> map;
    std::vector<Ship*> homeFleet;
    std::vector<Ship*> opponentFleet;
};


#endif //FLOTTENKAMPF_BETTER_BATTLEFIELD_H
