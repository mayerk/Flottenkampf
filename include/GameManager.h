#ifndef FLOTTENKAMPF_BETTER_GAMEMANAGER_H
#define FLOTTENKAMPF_BETTER_GAMEMANAGER_H

#include "Battlefield.h"

class GameManager {
public:
    GameManager();

    ~GameManager();

    void start();

private:
    void manager();
    bool isActive();
    void processAttack(bool home);
    void printResults();

    Battlefield* battlefield;
};


#endif //FLOTTENKAMPF_BETTER_GAMEMANAGER_H
