#include "poor-trusting-fool.h"
#include "factory.h"
#include <iostream>


namespace {
    Strategy *createPTF() {
        return new PTF;
    }
    bool g() {
        Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("poor-trusting-fool", createPTF);
        return true;
    }
    static bool b = g();
}// namespace


CHOICE PTF::choice(std::vector<std::vector<CHOICE>> &) {
    return COOPERATE;
}

std::string PTF::name() {
    return "poor-trusting-fool";
}