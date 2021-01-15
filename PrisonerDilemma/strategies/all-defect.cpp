#include "all-defect.h"
#include <iostream>


Strategy *create_str(){
    return new AllD;
}

void create() {
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("all-defect", create_str);
}

CHOICE AllD::choice(std::vector<std::vector<CHOICE>> &) {
    return DEFECT;
}
std::string AllD::name() {
    return "all-defect";
}
