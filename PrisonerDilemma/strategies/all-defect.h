#pragma once
#include "../strategy.h"
#include "../factory.h"
#include <iostream>
#include <vector>
#define EXPORT extern "C" __declspec (dllexport)
EXPORT void create();

class AllD : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
};