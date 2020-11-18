#pragma once
#include "strategy.h"
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "gamer.h"

typedef std::map<std::vector<char>, std::vector<int>> MATRIX_;
typedef std::shared_ptr<Strategy> StrategyPtr;


class PlayMode {
public:
    virtual void play(MATRIX_ &M, std::set<std::string> &names, int N, std::string configs, Gamer gamer = {}) = 0;
    int steps_counter = 0;
protected:

    std::vector<std::vector<char>> history = {{'C', 'C', 'C'}};
    void Initial(std::set<std::string> &names, std::string &configs);
    void OneGame(bool detailed = false);
    virtual void PrintRes(const std::vector<char> &choice = {}, const std::vector<int> &res = {});
    MATRIX_ T;
    std::vector<StrategyPtr> str;


};
