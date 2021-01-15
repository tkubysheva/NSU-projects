#pragma once
#include "../strategy.h"
#include "../factory.h"
#include <iostream>
#include <vector>
#include <windows.h>
#define EXPORT extern "C" __declspec (dllexport)

class PTF : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
};
Strategy *create_str(){
    return new PTF;
}
EXPORT void create(){
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("poor-trusting-fool", create_str);
}

