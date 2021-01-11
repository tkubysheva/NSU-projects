#pragma once
#include "../strategy.h"
#include <iostream>
#include <vector>

class CChoice : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
    int cchoice_number = 10;
    void MaybeLoadInfo(const std::string &) override;
};