#include "all-defect.h"
#include "factory.h"
#include <iostream>

namespace {
    bool g(){
        Factory<Strategy, std::string, Strategy*(*)()>::getInstance()->addCreator("all-defect", createAllD);
        return true;
    }
    static bool b = g();
}

Strategy* createAllD(){
    return new AllD;
}

CHOICE AllD::choice(std::vector<std::vector<CHOICE>>&){
    return DEFECT;
}

std::string AllD::name(){
    return "all-defect";
}