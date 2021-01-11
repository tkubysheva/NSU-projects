#include "all-defect.h"
#include <iostream>




CHOICE AllD::choice(std::vector<std::vector<CHOICE>> &) {
    return DEFECT;
}
std::string AllD::name() {
    return "all-defect";
}
