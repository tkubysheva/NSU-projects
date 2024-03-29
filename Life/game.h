#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
class Game {
public:
    Game();
    size_t x() const {
        return FieldSize_x_;
    }
    size_t y() const {
        return FieldSize_y_;
    }
    void set_x(size_t x) {
        FieldSize_x_ = x;
    }

    void set_y(size_t y) {
        FieldSize_y_ = y;
    }
    std::string alive_for_print();
    std::string dead_for_print();
    std::vector<int> alive_rules_screen() {
        return stay_rules;
    }
    std::vector<int> dead_rules_screen() {
        return born_rules;
    }
    bool is_alive(size_t x, size_t y);
    void change_state(size_t x, size_t y);
    void clear_field();
    void next_field_generation();
    void converse_field(std::vector<bool> &f);
    void converse_field();
    bool field_equal();
    void change_rules(std::vector<int> &b, std::vector<int> &s);
    void change_size(size_t size, bool x = false);

private:
    const size_t begin_size_x;
    const size_t begin_size_y;
    size_t FieldSize_x_;
    size_t FieldSize_y_;
    std::vector<int> stay_rules;
    std::vector<int> born_rules;
    bool right_neighbor(int n, bool is_alive);
    double cell_size_height();
    double cell_size_width();
    bool will_be_alive(size_t x, size_t y);
    std::vector<bool> ThisField;
    std::vector<bool> NextField;
};

#endif// GAME_H
