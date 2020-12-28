#include "mode.h"
#include "factory.h"
#include "table.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

void PlayMode::InitialGame(const std::string &matr_conf, const size_t &steps_, const std::set<std::string> &names, const std::string &str_conf) {
    matrix = CreateMatrix(matr_conf);
    steps = steps_;
    names_ = names;
    configs = str_conf;
}


//один шаг от каждой стратегии, запись в исторю, вывод результатов для детализированной игры
void PlayMode::OneGame(bool detailed) {
    std::vector<CHOICE> choice = {str[0]->choice(history), str[1]->choice(history), str[2]->choice(history)};
    history.push_back(choice);
    std::vector<int> res = matrix.at(choice);
    for (size_t i = 0; i < 3; ++i) {
        score[i] += res[i];
    }
    print.update_res(res);
    if (detailed) {
        print.detailed(choice, res);
    }
}
void PlayMode::Initial(const std::set<std::string> &names, const std::string &configs) {
    std::string n1, n2, n3;
    auto n = names.begin();
    n1 = *n;
    n2 = *(++n);
    n3 = *(++n);
    str.clear();
    str.emplace_back(Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->makeObject(n1));
    str.emplace_back(Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->makeObject(n2));
    str.emplace_back(Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->makeObject(n3));
    print.initialization({n1, n2, n3});
    for (size_t i = 0; i < str.size(); ++i) {
        str[i]->assign_number(i);
        str[i]->MaybeLoadInfo(configs);
    }
    score = {0, 0, 0};
}

