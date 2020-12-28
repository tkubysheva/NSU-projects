#include "strategy.h"
#include <vector>
#include <iostream>


class AllD : public Strategy {
public:
    CHOICE choice (std::vector<std::vector<CHOICE>>&) override;
    std::string name() override;
};

Strategy *createAllD ();