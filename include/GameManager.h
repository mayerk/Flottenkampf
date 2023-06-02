#ifndef FLOTTENKAMPF_GAMEMANAGER_H
#define FLOTTENKAMPF_GAMEMANAGER_H

#include <vector>
#include <array>
#include "Ship.h"
#include "HunterShip.h"
#include "DestroyerShip.h"
#include "CruiserShip.h"
#include "Utility.h"

class GameManager {
public:
    GameManager() = default;

    void start();

private:
    void initializeMap();
    bool manager();
    void insertFleet();
    Ship* chooseShip();
    void generateShipCoordinates();
    void printFleets();
    void startBattle();
    bool isActive();
    void processAttack(bool home);
    bool isShipAtCoordinates(Coordinates coordinates, bool isHome);
    void printResult();

    std::array<std::array<Ship*, Utility::Data::HEIGHT>, Utility::Data::WIDTH> map;
    std::vector<Ship*> homeFleet;
    std::vector<Ship*> opponentFleet;
};


#endif //FLOTTENKAMPF_GAMEMANAGER_H
