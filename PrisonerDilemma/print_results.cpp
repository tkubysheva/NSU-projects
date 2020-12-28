#include "print_results.h"
#include <iomanip>
#include <iostream>
#include <algorithm>

std::string PrintResults::what_choice(CHOICE c){
    return c?"defect":"cooperate";
}

void PrintResults::detailed(const std::vector<CHOICE> &choice, const std::vector<int> &res) {
    std::cout.setf(std::ios::fixed);
    std::cout << std::setw(20) << std::left << "Strategy's name" << std::setw(10) << "choice" << std::setw(8) << "points" << std::setw(10) << "score" << std::endl;
    for (int i = 0; i < 3; ++i)
        std::cout << std::setw(20) << std::left << str[i] << std::setw(10)
                  << what_choice(choice[i]) << std::setw(8) << res[i] << std::setw(10) << res_score[i] << std::endl;
    std::cout << "Press any key to continue or 'q' to exit:" << std::endl;
}
void PrintResults::update_res(const std::vector<int> &res) {
    for (size_t i = 0; i < res_score.size(); ++i) {
        res_score[i] += res[i];
    }
}
void PrintResults::initialization(const std::vector<std::string> &s) {
    str = s;
    res_score.resize(str.size());
    std::fill(res_score.begin(), res_score.end(), 0);
}
void PrintResults::fast() {
    std::cout.setf(std::ios::fixed);
    std::cout << std::setw(20) << std::left << "Strategy's name"
              << std::setw(10) << "score" << std::endl;
    for (size_t i = 0; i < str.size(); ++i) {
        std::cout << std::setw(20) << std::left << str[i]
                  << std::setw(10) << res_score[i] << std::endl;
    }
    size_t best = *std::max_element(res_score.begin(), res_score.end());
    for (size_t i = 0; i < str.size(); ++i) {
        if (res_score[i] == best) {
            std::cout << str[i] << " ";
        }
    }
    std::cout << "WIN with score " << best << std::endl
              << std::endl;
}
void PrintResults::tournament(const std::map<std::string, int>& tournament_score) {
    std::string n;
    int max = 0;
    std::cout.setf(std::ios::fixed);
    std::cout << std::setw(20) << "         RESULTS" << std::endl;
    std::cout << std::setw(20) << std::left << "Strategy's name" << std::setw(10) << "score" << std::endl;
    for (const auto &i : tournament_score) {
        std::cout << std::setw(20) << std::left << i.first << std::setw(10) << i.second << std::endl;
        if (i.second > max) {
            max = i.second;
            n = i.first;
        }
    }
    std::cout << std::endl
              << n << " TOTAL WIN" << std::endl;
}
void PrintResults::tour(int tour_count) {
    std::cout << "         TOUR #" << tour_count << std::endl;
    fast();
}
