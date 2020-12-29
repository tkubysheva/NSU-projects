#pragma once
#include "gamer.h"
#include "print_results.h"
#include "strategy.h"
#include "typenames.h"
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class PlayMode {
public:
    virtual void play(Gamer gamer = {}) = 0;
    void InitialGame(const std::string &matr_conf, const size_t &steps,
                     const std::set<std::string> &names, const std::string &str_conf);

protected:
    std::vector<StrategyPtr> str;
    std::vector<size_t> score;
    std::set<std::string> names_;
    std::string configs;
    size_t steps = 1000;
    std::vector<std::vector<CHOICE>> history = {{COOPERATE, COOPERATE, COOPERATE}};
    void Initial(const std::set<std::string> &names, const std::string &configs);
    void OneGame(bool detailed = false);
    MATRIX_ matrix;
    PrintResults print;
};