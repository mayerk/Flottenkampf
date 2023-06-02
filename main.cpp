#include <iostream>

#include "include/GameManager.h"
#include <ctime>

int main() {
    srand(time(NULL));
    GameManager manager = GameManager();
    manager.start();
    return 0;
}
