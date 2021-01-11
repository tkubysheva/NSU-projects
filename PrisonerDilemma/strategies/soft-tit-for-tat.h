#pragma once
#include "../strategy.h"
#include <iostream>
#include <vector>

class STFT : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
};
