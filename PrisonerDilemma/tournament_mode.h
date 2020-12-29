#pragma once
#include "mode.h"
#include "typenames.h"
#include <map>
#include <set>
#include <string>
#include <vector>


class Tournament : public PlayMode {
    void play(Gamer gamer = {}) override;
    void tour(int tour_count, std::set<std::string> &names);
    std::map<std::string, int> tournament_score;
    void UpdateScore();
};
