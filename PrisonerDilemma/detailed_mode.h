#pragma once
#include "mode.h"
#include <map>
#include <set>
#include <string>
#include <vector>
#include "typenames.h"
class Detailed : public PlayMode {
public:
    void play(Gamer gamer) override;
};
