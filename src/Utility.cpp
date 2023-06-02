#include "../include/Utility.h"

int Utility::getInput(std::string message, const int range) {
    std::cout << message << std::endl;
    bool err;
    std::string input;
    do {
        std::cin >> input;
        if(std::stoi(input) <= 0 || std::stoi(input) > range) {
            err = true;
            std::cout << "Incorrect input!" << std::endl;
        } else {
            err = false;
        }
    } while(err);
    return std::stoi(input);
}

int Utility::getRandBetween(const int min, const int max) {
    return rand()%(max - min + 1) + min;
}
