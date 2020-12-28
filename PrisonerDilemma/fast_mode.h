#pragma once
#include "mode.h"
#include <map>
#include <set>
#include <string>
#include <vector>
#include "typenames.h"

class Fast : public PlayMode {
    void play(Gamer gamer = {}) override;
};
