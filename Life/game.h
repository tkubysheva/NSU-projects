#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
class Game {
public:
    Game();
    size_t x() const;
    size_t y() const;
    void set_x(size_t);
    void set_y(size_t);
    std::string alive_for_print();
    std::string dead_for_print();
    bool is_alive(size_t x, size_t y);
    void change_state(size_t x, size_t y);
    void clear_field();
    void next_field_generation();
    void converse_field(std::vector<bool> f);
    void converse_field();
    bool field_equal();
    bool change_rules(std::string r);
    void change_size(size_t size, bool x = false);

private:
    const size_t begin_size_x;
    const size_t begin_size_y;
    size_t FieldSize_x_;
    size_t FieldSize_y_;
    std::vector<int> alive_rules;
    std::vector<int> dead_rules;
    bool right_neighbor(int n, bool is_alive);
    double cell_size_height();
    double cell_size_width();
    bool will_be_alive(size_t x, size_t y);
    std::vector<bool> ThisField;
    std::vector<bool> NextField;
};

#endif// GAME_H
