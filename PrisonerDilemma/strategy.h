#pragma once
#include <string>
#include <vector>

enum CHOICE {
    COOPERATE,
    DEFECT
};

class Strategy {
public:
    virtual CHOICE choice(std::vector<std::vector<CHOICE>> &history) = 0;
    virtual std::string name() = 0;
    void assign_number(int n) { number_in_history = n; }
    virtual void MaybeLoadInfo(const std::string &dir) {}

protected:
    int number_in_history = 0;
};
