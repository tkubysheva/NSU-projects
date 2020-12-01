#include "field.h"
#include <QMouseEvent>
#include <QMessageBox>
#include<vector>
#include <stdlib.h>
#include<fstream>
#include<iostream>
field::field(QWidget *parent) : QWidget(parent),
    timer(new QTimer(this))
{
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(generation_next_field()));
}
void field::paintEvent(QPaintEvent *){
    QPainter paint(this);
    PaintField(paint);
    PaintCells(paint);
}

double field::cell_size_height(){
    return (double)height()/Game.FieldSize_y_;
}

double field::cell_size_width(){
    return (double)width()/Game.FieldSize_x_;
}
void field::PaintField(QPainter &p){
    p.setPen(GridColor);
    for(double i = 0; i <= width(); i+= cell_size_width()){
        p.drawLine(i, 0, i, height());
    }
    for(double i = 0; i <= height(); i+= cell_size_height()){
        p.drawLine(0, i, width(), i);
    }
}

void field::PaintCells(QPainter &p){
    for(int i = 0; i < Game.FieldSize_y_; ++i){
        for(int j = 0; j < Game.FieldSize_x_; ++j){
            if(Game.is_alive(j, i)){
                QRectF rect(cell_size_width()*j,cell_size_height()*i,cell_size_width(), cell_size_height());
                p.fillRect(rect, CellColor);
            }
        }
    }
}

void field::mousePressEvent(QMouseEvent *clik){
    int i = clik->x()/cell_size_width();
    int j = clik->y()/cell_size_height();
    Game.change_state(i, j);
    update();
}

void field::change_rules(QString r){
    std::string rules = r.toStdString();
    if(!Game.change_rules(rules)){
        wrong_rules();
    }
}

void field::wrong_file(){
    QMessageBox::information(this, tr("Error"), tr("Wrong file's format."), QMessageBox::Ok);
}
void field::wrong_rules(){
    QMessageBox::information(this, tr("Wrong rules"), tr("Right format: b3s23."), QMessageBox::Ok);
}
void field::mouseMoveEvent(QMouseEvent *clik)
{
    int i = clik->x()/cell_size_width();
    int j = clik->y()/cell_size_height();
    if(!Game.is_alive(i, j)){
        Game.change_state(i, j);
        update();
    }
}

void field::on_clear_clicked()
{
    timer->stop();
    Game.clear_field();
    update();
}

void field::on_one_step_clicked()
{
    timer->stop();
    Game.next_field_generation();
    Game.converse_field();
    update();
}

void field::generation_next_field(){
    Game.next_field_generation();
    if(Game.field_equal()){
        timer->stop();
    }
    Game.converse_field();
    update();
}

void field::start_clicked()
{
    timer->start();
}

void field::stop_clicked()
{
    timer->stop();
}

void field::on_change_size_x_clicked(int x)
{
    timer->stop();
    Game.change_size(x, true);
    update();
}
void field::on_change_size_y_clicked(int y)
{
    timer->stop();
    Game.change_size(y);
    update();
}

void field::save_clicked(){
    timer->stop();
    std::fstream f("game.txt");
    clear_file();
    f << "x = "<< Game.FieldSize_x_<< "; y = "<< Game.FieldSize_y_<<std::endl;
    f << "b"<<Game.dead_for_print<<"s"<<Game.alive_for_print<<std::endl;
    int count = 0;
    for(int i = 0; i < Game.FieldSize_y_; ++i){
        for(int j = 0; j < Game.FieldSize_x_; ++j){
            if(j == 0){
                if(i != 0){
                    f << count<<"$"<<(Game.is_alive(j, i) ? "o":"b");
                }
                else {
                    f << (Game.is_alive(j, i) ? "o":"b");
                }
                count = 1;
            }
            else {
                if(Game.is_alive(j, i) == Game.is_alive(j-1, i)){
                    count++;
                }
                else{
                    f << count<<(Game.is_alive(j, i) ? "o" : "b");
                    count = 1;
                }
            }
        }
        if(i == Game.FieldSize_y_ - 1){
            f << count << "$"<<std::endl;
        }
    }
    f.close();
}

void field::clear_file(){
    std::ofstream ofs;
    ofs.open("game.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

load_data field::load_clicked(){
    timer->stop();
    std::fstream f("game.txt");
    std::string s, x_s, y_s, r_s;
    int x, y;
    std::getline(f, s);
    auto p = s.find(';');
    x_s = s.substr(4, p-4);
    if((x = atoi(x_s.c_str())) == 0){
        wrong_file();
        return {false, 0, 0, ""};
    }
    y_s = s.substr(p+6, s.size() - p - 6);
    if((y = atoi(y_s.c_str()))== 0){
        wrong_file();
        return {false, 0, 0, ""};
    }
    std::getline(f, r_s);
    std::getline(f, s);
    f.close();
    std::vector<bool> field(x*y);
    std::fill(field.begin(), field.end(), false);
    int pos = 0, count = 0, control_sum = 0;
    std::string num = "";
    bool l = false;
    for(const auto& i : s){
        if(l){
            if(i == 'b' or i == '$'){
                l = false;
                count = atoi(num.c_str());
                num = "";
                control_sum += count;
                if(i == '$'){
                    if(control_sum != x){
                        wrong_file();
                        return {false, 0, 0, ""};
                    }
                    else control_sum = 0;
                }
                for (int i = pos; i< pos+count; ++i){
                    field[i] = true;
                }
                pos += count;
            }else if(i-'0' >=0 and i-'0'<= 9){
                num += i;
            }
            else {
                wrong_file();
                return {false, 0, 0, ""};
            }
        }else{
            if(i == 'o' or i == '$'){
                count = atoi(num.c_str());
                num = "";
                pos += count;
                control_sum += count;
                if(i == '$'){
                    if(control_sum != x){
                        wrong_file();
                        return {false, 0, 0, ""};
                    }
                    else control_sum = 0;
                }
                if(i == 'o'){
                    l = true;  
                }

            }else if(i-'0' >=0 and i-'0'<= 9){
                num += i;
            }
            else if(i != 'b'){
                wrong_file();
                return {false, 0, 0, ""};
            }
        }
    }
    if(pos != x*y){
        wrong_file();
        return {false, 0, 0, ""};
    }
    if(!Game.change_rules(r_s)){
        wrong_file();
        return {false, 0, 0, ""};
    }
    Game.change_size(x, true);
    Game.change_size(y);
    for(int i = 0; i < x*y; ++i)
        Game.ThisField[i] = field[i];
    update();
    return {true, x, y, r_s};
}
