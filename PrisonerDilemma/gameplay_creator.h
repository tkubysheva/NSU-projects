#pragma once
#include <map>
#include <set>
#include <vector>
#include "mode.h"
#include <memory>
typedef std::map<std::vector<char>, std::vector<int>> MATRIX_;
template<typename T>
T convert_(char *arg);

class Mode {
private:
    std::string mode = "detailed";
    int step = 1000;
    std::string matrix_dir;
    std::string configs_dir;
    MATRIX_ matrix;
    std::set<std::string> names;
public:
    Mode() = delete;
    Mode(int argc, char *argv[]);
    std::unique_ptr<PlayMode> creator();
};

