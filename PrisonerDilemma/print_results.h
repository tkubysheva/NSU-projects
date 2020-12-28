#include <vector>
#include <map>

#pragma once
#include "typenames.h"
class PrintResults{
    std::vector<std::string> str;
    std::vector<size_t> res_score;
    std::string what_choice(CHOICE c);
public:
    void tour(int tour_count);
    void tournament(const std::map<std::string, int>& tournament_score);
    void detailed(const std::vector<CHOICE> &choice, const std::vector<int> &res);
    void fast();
    void update_res(const std::vector<int> &res);
    void initialization(const std::vector<std::string> & s);
};