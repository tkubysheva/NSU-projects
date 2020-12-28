#include <QFileDialog>
#include <QString>
#include <fstream>
#include <iostream>
#include <vector>

struct load_data {
    bool success;
    int x, y;
    std::vector<int> b;
    std::vector<int> s;
    std::vector<bool> field;
};

struct SaveLoad {
    std::vector<int> stay_rules;
    std::vector<int> born_rules;
    SaveLoad();
    void clear_file(std::string filename) {
        std::ofstream ofs;
        ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }
    void Save(size_t x, size_t y, const std::vector<bool> &field, const std::string &dead, const std::string &alive) {
        stay_rules.clear();
        born_rules.clear();
        QString str = QFileDialog::getSaveFileName(0, "Open Dialog", "", "*.txt");
        if (str.isEmpty()) {
            return;
        }
        std::string filename = str.toStdString();
        clear_file(filename);
        std::fstream f(filename);

        f << "x = " << x << "; y = " << y << std::endl;
        f << "b" << dead << "s" << alive << std::endl;
        int count = 0;
        for (size_t i = 0; i < y; ++i) {
            for (size_t j = 0; j < x; ++j) {
                if (j == 0) {
                    if (i != 0) {
                        f << count << "$" << (field[j + x * i] ? "o" : "b");
                    } else {
                        f << (field[j + x * i] ? "o" : "b");
                    }
                    count = 1;
                } else {
                    if (field[j + x * i] == field[(j - 1) + x * i]) {
                        count++;
                    } else {
                        f << count << (field[j + x * i] ? "o" : "b");
                        count = 1;
                    }
                }
            }
            if (i == y - 1) {
                f << count << "$" << std::endl;
            }
        }
    }
    bool change_rules_file(const std::string &rules) {
        auto pos1 = rules.find("b");
        auto pos2 = rules.find("s");

        if (pos1 != std::string::npos and pos2 != std::string::npos) {

            std::string arg1 = rules.substr(pos1 + 1, -pos1 - 1 + pos2);
            std::string arg2 = rules.substr(pos2 + 1, rules.size() - 1 - pos2);
            for (const auto &i : arg1) {
                if (i - '0' > 0 and i - '0' < 10) {
                    born_rules.push_back(i - '0');
                } else {
                    return false;
                }
            }
            for (const auto &i : arg2) {
                if (i - '0' > 0 and i - '0' < 10) {
                    stay_rules.push_back(i - '0');
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
        return true;
    }

    load_data Load() {
        stay_rules.clear();
        born_rules.clear();
        QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");
        if (str.isEmpty()) {
            return {false, 0, 0, {}, {}, {}};
        }
        std::string filename = str.toStdString();
        std::fstream f(filename);
        std::string size, data, x_s, y_s, r_s;
        int x, y;
        std::getline(f, size);
        std::getline(f, r_s);
        std::getline(f, data);
        if (!new_size_processing(size, x, y)) {
            return {false, 0, 0, {}, {}, {}};
        }
        std::vector<bool> field(x * y, false);
        if (!data_processing(data, x, y, field)) {
            return {false, 0, 0, {}, {}, {}};
        }
        if (!change_rules_file(r_s)) {
            return {false, 0, 0, {}, {}, {}};
        }
        return {true, x, y, born_rules, stay_rules, field};
    }
    bool new_size_processing(const std::string &s, int &x, int &y) {
        std::string x_s, y_s;
        auto p = s.find(';');
        if (p == std::string::npos) {
            return false;
        }
        x_s = s.substr(4, p - 4);
        bool no_err;
        x = QString::fromStdString(x_s).toInt(&no_err);
        if (!no_err) {
            return false;
        }
        y_s = s.substr(p + 6, s.size() - p - 6);
        y = QString::fromStdString(y_s).toInt(&no_err);
        if (!no_err) {
            return false;
        }
        return true;
    }
    bool data_processing(const std::string &s, const int &x, const int &y, std::vector<bool> &field) {
        int pos = 0, count = 0, control_sum = 0;
        std::string num = "";
        bool l = false;
        for (const auto &i : s) {
            if (l) {
                if (i == 'b' or i == '$') {
                    l = false;
                    count = QString::fromStdString(num).toInt();
                    num = "";
                    control_sum += count;
                    if (i == '$') {
                        if (control_sum != x) {

                            return false;
                        } else
                            control_sum = 0;
                    }
                    for (int i = pos; i < pos + count; ++i) {
                        field[i] = true;
                    }
                    pos += count;
                } else if (i - '0' >= 0 and i - '0' <= 9) {
                    num += i;
                } else {
                    return false;
                }
            } else {
                if (i == 'o' or i == '$') {
                    count = QString::fromStdString(num).toInt();
                    num = "";
                    pos += count;
                    control_sum += count;
                    if (i == '$') {
                        if (control_sum != x) {
                            return false;
                        } else
                            control_sum = 0;
                    }
                    if (i == 'o') {
                        l = true;
                    }
                } else if (i - '0' >= 0 and i - '0' <= 9) {
                    num += i;
                } else if (i != 'b') {
                    return false;
                }
            }
        }
        if (pos != x * y) {
            return false;
        }
        return true;
    }
};
