#pragma once
#include "../strategy.h"
#include "../factory.h"
#include <iostream>
#include <vector>

#define EXPORT extern "C" __declspec (dllexport)

class FR : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
};

Strategy *create_str(){
    return new FR;
}

EXPORT void create(){
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("forgive-revenge", create_str);
}

