#include "../strategy.h"
#include "../factory.h"
#include <iostream>
#include <vector>
#include <windows.h>
#define EXPORT extern "C" __declspec (dllexport)

class TTFT : public Strategy {
public:
    CHOICE choice(std::vector<std::vector<CHOICE>> &) override;
    std::string name() override;
};

Strategy *create_str(){
    return new TTFT;
}

EXPORT void  create(){
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("tough-tit-for-tat", create_str);
}

