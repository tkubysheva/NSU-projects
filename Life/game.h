#ifndef GAME_H
#define GAME_H
#include <vector>
#include <QPainter>
class game
{
private:
    double cell_size_height();
    double cell_size_width();
    bool will_be_alive(int x, int y);
public:
    int FieldSize_x_ = 20;
    int FieldSize_y_ = 20;
    game();
    std::vector<int> alive_count;
    std::vector<int> dead_count;
    bool is_alive(int x, int y);
    void change_state(int x, int y);
    void clear_field();
    void update_after_press();
    void next_field_generation();
    void converse_field();
    bool field_equal();
    bool right_neighbor(int n, bool is_alive);
    std::vector<bool> ThisField;
    std::vector<bool> NextField;

};

#endif // GAME_H
