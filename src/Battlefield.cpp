#include "../include/Battlefield.h"

Battlefield::Battlefield() {
    for(auto& x: this->map) {
        for(auto &y: x) {
            y = nullptr;
        }
    }
}
