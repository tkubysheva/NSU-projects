#include "random.h"
#include <iostream>

CHOICE Rand::choice(std::vector<std::vector<CHOICE>> &) {
    if (rand() % 2 == 1)
        return DEFECT;
    return COOPERATE;
}

std::string Rand::name() {
    return "random";
}