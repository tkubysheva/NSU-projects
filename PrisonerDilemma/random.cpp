#include "random.h"
#include "factory.h"
#include <iostream>


namespace {
    bool g() {
        Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("random", createRand);
        return true;
    }
    static bool b = g();
}// namespace

Strategy *createRand() {
    return new Rand;
}

CHOICE Rand::choice(std::vector<std::vector<CHOICE>> &) {
    if (rand() % 2 == 1)
        return DEFECT;
    return COOPERATE;
}

std::string Rand::name() {
    return "random";
}