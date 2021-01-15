#include "soft-tit-for-tat.h"
#include <iostream>
Strategy *create_str(){
    return new STFT;
}
void create(){
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("soft-tit-for-tat", create_str);
}
CHOICE STFT::choice(std::vector<std::vector<CHOICE>> &h) {
    int s = h.size();
    if ((h[s - 1][0] == DEFECT or number_in_history == 0) and
        (h[s - 1][1] == DEFECT or number_in_history == 1) and
        (h[s - 1][2] == DEFECT or number_in_history == 2))
        return DEFECT;
    return COOPERATE;
}

std::string STFT::name() {
    return "soft-tit-for-tat";
}