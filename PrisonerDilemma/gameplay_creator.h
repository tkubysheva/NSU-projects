#pragma once
#include "mode.h"
#include "typenames.h"
#include <map>
#include <memory>
#include <set>
#include <vector>
template<typename T>
T convert_(char *arg);

class Gameplay {
private:
    std::string mode = "detailed";
    size_t step = 1000;
    std::string matrix_dir;
    std::string configs_dir;
    MATRIX_ matrix;
    std::set<std::string> names;
public:
    Gameplay() = delete;
    Gameplay(int argc, char *argv[]);
    std::unique_ptr<PlayMode> creator();
};
