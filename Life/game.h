#ifndef GAME_H
#define GAME_H
#include <vector>
#include <QPainter>
class game
{
    const int begin_size_x;
    const int begin_size_y;
public:
    game();
    int FieldSize_x_;
    int FieldSize_y_;
    std::vector<int> alive_rules;
    std::vector<int> dead_rules;
    std::string alive_for_print;
    std::string dead_for_print;
    bool is_alive(int x, int y);
    void change_state(int x, int y);
    void clear_field();
    void next_field_generation();
    void converse_field();
    bool field_equal();
    bool change_rules(std::string r);
    void change_size(int size, bool x = false);
    std::vector<bool> ThisField;
private:
    bool right_neighbor(int n, bool is_alive);
    double cell_size_height();
    double cell_size_width();
    bool will_be_alive(int x, int y);
    std::vector<bool> NextField;
};

#endif // GAME_H
