#pragma once
#include <fstream>
#include <map>
#include <vector>

typedef std::map<std::vector<CHOICE>, std::vector<int>> MATRIX_;

static MATRIX_ CreateMatrix(const std::string &filename) {
    MATRIX_ T;
    if (filename.empty()) {
        T[{DEFECT, DEFECT, DEFECT}] = {1, 1, 1};
        T[{DEFECT, DEFECT, COOPERATE}] = {5, 5, 0};
        T[{DEFECT, COOPERATE, DEFECT}] = {5, 0, 5};
        T[{COOPERATE, DEFECT, DEFECT}] = {0, 5, 5};
        T[{DEFECT, COOPERATE, COOPERATE}] = {9, 3, 3};
        T[{COOPERATE, DEFECT, COOPERATE}] = {3, 9, 3};
        T[{COOPERATE, COOPERATE, DEFECT}] = {3, 3, 9};
        T[{COOPERATE, COOPERATE, COOPERATE}] = {7, 7, 7};
        return T;
    }
    std::ifstream in(filename);
    if (in.is_open()) {
        int a, b, c;
        in >> a >> b >> c;
        T[{DEFECT, DEFECT, DEFECT}] = {a, b, c};
        in >> a >> b >> c;
        T[{DEFECT, DEFECT, COOPERATE}] = {a, b, c};
        in >> a >> b >> c;
        T[{DEFECT, COOPERATE, DEFECT}] = {a, b, c};
        in >> a >> b >> c;
        T[{COOPERATE, DEFECT, DEFECT}] = {a, b, c};
        in >> a >> b >> c;
        T[{DEFECT, COOPERATE, COOPERATE}] = {a, b, c};
        in >> a >> b >> c;
        T[{COOPERATE, DEFECT, COOPERATE}] = {a, b, c};
        in >> a >> b >> c;
        T[{COOPERATE, COOPERATE, DEFECT}] = {a, b, c};
        in >> a >> b >> c;
        T[{COOPERATE, COOPERATE, COOPERATE}] = {a, b, c};
    } else
        throw std::runtime_error("file with matrix not found :(");
    in.close();
    return T;
}
