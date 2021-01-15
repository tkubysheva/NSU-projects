#pragma once
#include "../strategy.h"
#include "../factory.h"
#include <iostream>
#include <vector>

#define EXPORT extern "C" __declspec (dllexport)

class CChoice : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
    int cchoice_number = 10;
    void MaybeLoadInfo(const std::string &) override;
};






