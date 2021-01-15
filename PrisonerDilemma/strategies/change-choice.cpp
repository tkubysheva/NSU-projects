#include "change-choice.h"
#include <fstream>
#include <iostream>

Strategy *create_str(){
    return new CChoice;
}
void create(){
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("change-choice", create_str);
}
CHOICE CChoice::choice(std::vector<std::vector<CHOICE>> &history) {
    if (((history.size() - 1) / cchoice_number) % 2 != 0)
        return DEFECT;
    return COOPERATE;
}

std::string CChoice::name() {
    return "change-choice";
}
void CChoice::MaybeLoadInfo(const std::string &dir) {
    if (dir.empty()) {
        return;
    }
    std::ifstream in(dir + "change-choice.txt");
    if (in.is_open()) {
        in >> cchoice_number;
    } else if (dir.empty()) {
        return;
    } else
        throw std::runtime_error("FILE change-choice.txt NOT FOUND IN DIRECTORY " + dir);
}
