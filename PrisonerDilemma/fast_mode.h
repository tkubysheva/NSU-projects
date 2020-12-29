#pragma once
#include "mode.h"
#include "typenames.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class Fast : public PlayMode {
    void play(Gamer gamer = {}) override;
};
