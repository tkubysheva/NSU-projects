#include "game.h"
#include "field.h"
#include <algorithm>
game::game():
    ThisField(FieldSize_x_*FieldSize_y_, false),
    NextField(FieldSize_x_*FieldSize_y_, false)
{
    alive_count = {2, 3};
    dead_count = {3};
}

bool game::right_neighbor(int n, bool is_alive){
    if(is_alive){
        return  std::find(alive_count.begin(), alive_count.end(), n) != alive_count.end();
    }
    return  std::find(dead_count.begin(), dead_count.end(), n) != dead_count.end();
}

void game::next_field_generation(){
    for(int i = 0; i < FieldSize_y_; ++i){
        for(int j = 0; j < FieldSize_x_; ++j){
            NextField[i*FieldSize_x_ + j] = will_be_alive(j, i);
        }
    }
}

bool game::is_alive(int x, int y){
    return ThisField[y*FieldSize_x_ +x];
}

void game::change_state(int x, int y){
    ThisField[y*FieldSize_x_ + x]= !ThisField[y*FieldSize_x_ + x];
}
void game::converse_field(){
    for (int i = 0; i <FieldSize_x_*FieldSize_y_; ++i){
        ThisField[i] = NextField[i];
    }
}
bool game::field_equal(){
    for (int i = 0; i <FieldSize_x_*FieldSize_y_; ++i){
        if(ThisField[i] != NextField[i])
            return false;
    }
    return true;
}

bool game::will_be_alive(int x, int y){
    int alive_nearby = 0;
    if(x > 0 and x < FieldSize_x_ - 1 and y > 0 and y < FieldSize_y_ - 1){
        alive_nearby += ThisField[x + (y+1)*FieldSize_x_] + ThisField[x + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + (y+1)*FieldSize_x_] + ThisField[(x + 1) + (y+1)*FieldSize_x_] +
                ThisField[(x - 1) + (y-1)*FieldSize_x_] + ThisField[(x + 1) + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + y*FieldSize_x_] + ThisField[(x + 1) + y*FieldSize_x_];
    }
    else if(x > 0 and x < FieldSize_x_ - 1 and y == 0){
        alive_nearby += ThisField[x + (y+1)*FieldSize_x_] +
                ThisField[(x - 1) + (y+1)*FieldSize_x_] + ThisField[(x + 1) + (y+1)*FieldSize_x_] +
                ThisField[(x - 1) + y*FieldSize_x_] + ThisField[(x + 1) + y*FieldSize_x_];
    }
    if(x > 0 and x < FieldSize_x_ - 1 and y == FieldSize_y_ - 1){
        alive_nearby += ThisField[x + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + (y-1)*FieldSize_x_] + ThisField[(x + 1) + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + y*FieldSize_x_] + ThisField[(x + 1) + y*FieldSize_x_];
    }
    else if(x == 0 and y > 0 and y < FieldSize_y_ - 1){
        alive_nearby += ThisField[x + (y+1)*FieldSize_x_] + ThisField[x + (y-1)*FieldSize_x_] +
                ThisField[(x + 1) + (y+1)*FieldSize_x_] +
                ThisField[(x + 1) + (y-1)*FieldSize_x_] + ThisField[(x + 1) + y*FieldSize_x_];
    }
    else if(x == 0 and y == 0){
        alive_nearby += ThisField[x + (y+1)*FieldSize_x_] +
                ThisField[(x + 1) + (y+1)*FieldSize_x_] + ThisField[(x + 1) + y*FieldSize_x_];
    }
    else if(x == 0 and y == FieldSize_y_ - 1){
        alive_nearby += ThisField[x + (y-1)*FieldSize_x_] +
                ThisField[(x + 1) + (y-1)*FieldSize_x_] + ThisField[(x + 1) + y*FieldSize_x_];
    }
    else if(x == FieldSize_x_ - 1 and y > 0 and y < FieldSize_y_ - 1){
        alive_nearby += ThisField[x + (y+1)*FieldSize_x_] + ThisField[x + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + (y+1)*FieldSize_x_] + ThisField[(x - 1) + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + y*FieldSize_x_];
    }
    else if(x == FieldSize_x_ - 1 and y == 0){
        alive_nearby += ThisField[x + (y+1)*FieldSize_x_] + ThisField[(x - 1) + (y+1)*FieldSize_x_] +
                ThisField[(x - 1) + y*FieldSize_x_];
    }
    else if(x == FieldSize_x_ - 1 and y == FieldSize_y_ - 1){
        alive_nearby += ThisField[x + (y-1)*FieldSize_x_] + ThisField[(x - 1) + (y-1)*FieldSize_x_] +
                ThisField[(x - 1) + y*FieldSize_x_];
    }
    return right_neighbor(alive_nearby, is_alive(x, y));
}
