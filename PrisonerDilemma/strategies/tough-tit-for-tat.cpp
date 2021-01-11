#include "tough-tit-for-tat.h"
#include <iostream>

CHOICE TTFT::choice(std::vector<std::vector<CHOICE>> &history) {
    int s = history.size();
    if ((history[s - 1][0] == COOPERATE or number_in_history == 0) and
        (history[s - 1][1] == COOPERATE or number_in_history == 1) and
        (history[s - 1][2] == COOPERATE or number_in_history == 2))
        return COOPERATE;
    return DEFECT;
}


std::string TTFT::name() {
    return "tough-tit-for-tat";
}