#include "forgive-revenge.h"
#include "factory.h"
#include <iostream>

namespace {
    bool g() {
        Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("forgive-revenge", createFR);
        return true;
    }
    static bool b = g();
}// namespace

Strategy *createFR() {
    return new FR;
}

CHOICE FR::choice(std::vector<std::vector<CHOICE>> &h) {
    size_t s = h.size();
    if ((h[s - 1][0] == DEFECT or number_in_history == 0) and
        (h[s - 1][1] == DEFECT or number_in_history == 1) and
        (h[s - 1][2] == DEFECT or number_in_history == 2))
        return DEFECT;
    if ((h[s - 1][0] == COOPERATE or number_in_history == 0) and
        (h[s - 1][1] == COOPERATE or number_in_history == 1) and
        (h[s - 1][2] == COOPERATE or number_in_history == 2))
        return COOPERATE;
    return h[s - 1][number_in_history];
}

std::string FR::name() {
    return "forgive-revenge";
}