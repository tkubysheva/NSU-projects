#pragma once
#include "mode.h"
#include "typenames.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class Detailed : public PlayMode {
public:
    void play(Gamer gamer) override;
};
