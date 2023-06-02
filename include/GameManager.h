#ifndef FLOTTENKAMPF_GAMEMANAGER_H
#define FLOTTENKAMPF_GAMEMANAGER_H

#include <vector>
#include <array>
#include "Ship.h"
#include "HunterShip.h"
#include "DestroyerShip.h"
#include "CruiserShip.h"
#include "Utility.h"
#include "Battlefield.h"

class GameManager {
public:
    GameManager();

    void start();

private:
    bool manager();
    void insertFleet();
    Ship* chooseShip();
    void generateShipCoordinates();
    void printFleets();
    void startBattle();
    bool isActive();
    void processAttack(bool home);
    void removeShip(Ship* ship, int index);
    bool isShipAtCoordinates(Coordinates coordinates, bool isHome);
    void printResult();

    Battlefield* battlefield;
    std::vector<Ship*> homeFleet;
    std::vector<Ship*> opponentFleet;
};


#endif //FLOTTENKAMPF_GAMEMANAGER_H
