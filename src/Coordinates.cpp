#include "../include/Coordinates.h"

Coordinates::Coordinates() {
    this->x = 0;
    this->y = 0;
}

Coordinates::Coordinates(int x, int y) {
    if(x < 0 || x >= Utility::Data::WIDTH) {
        throw std::out_of_range("Parameter is out of field range");
    }
    if(y < 0 || y >= Utility::Data::HEIGHT) {
        throw std::out_of_range("Parameter is out of field range");
    }
    this->x = x;
    this->y = y;
}

int Coordinates::getX() const {
    return x;
}

int Coordinates::getY() const {
    return y;
}

void Coordinates::generate(bool isHome) {
    this->x = Utility::getRandBetween(0, 14);
    if(isHome) {
        this->y = Utility::getRandBetween(0, 6);
    } else {
        this->y = Utility::getRandBetween(8, 14);
    }
}
