#pragma once
#include "strategy.h"
#include <map>
#include <memory>
#include <vector>
typedef std::map<std::vector<CHOICE>, std::vector<int>> MATRIX_;
typedef std::unique_ptr<Strategy> StrategyPtr;
