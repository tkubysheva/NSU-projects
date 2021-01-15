#pragma once
#include "../strategy.h"
#include "../factory.h"
#include <iostream>
#include <vector>
#include <windows.h>
#define EXPORT extern "C" __declspec (dllexport)

class STFT : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
};


