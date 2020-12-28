#pragma once
#include <map>
#include <vector>
#include <memory>
#include "strategy.h"
typedef std::map<std::vector<CHOICE>, std::vector<int>> MATRIX_;
typedef std::unique_ptr<Strategy> StrategyPtr;


