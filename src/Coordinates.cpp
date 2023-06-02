#include "../include/Coordinates.h"

Coordinates::Coordinates() {
    this->x = 0;
    this->y = 0;
}

Coordinates::Coordinates(int x, int y) {
    this->x = (x < 0) ? 0 : (x >= Utility::Data::WIDTH) ? Utility::Data::WIDTH-1 : x;
    this->y = (y < 0) ? 0 : (y >= Utility::Data::HEIGHT) ? Utility::Data::HEIGHT-1 : y;
}

int Coordinates::getX() const {
    return x;
}

int Coordinates::getY() const {
    return y;
}

void Coordinates::update(const int newX, const int newY) {
    this->x = (newX < 0) ? 0 : (newX >= Utility::Data::WIDTH) ? Utility::Data::WIDTH-1 : newX;
    this->y = (newY < 0) ? 0 : (newY >= Utility::Data::HEIGHT) ? Utility::Data::HEIGHT-1 : newY;
}

void Coordinates::generate(bool isHome) {
    this->x = Utility::getRandBetween(0, 14);
    if(isHome) {
        this->y = Utility::getRandBetween(0, 6);
    } else {
        this->y = Utility::getRandBetween(8, 14);
    }
}
