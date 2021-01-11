#include "poor-trusting-fool.h"
#include <iostream>



CHOICE PTF::choice(std::vector<std::vector<CHOICE>> &) {
    return COOPERATE;
}

std::string PTF::name() {
    return "poor-trusting-fool";
}