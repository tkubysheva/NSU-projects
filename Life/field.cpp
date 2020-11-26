#include "field.h"
#include <QMouseEvent>
#include <iostream>
#include <QMessageBox>
#include<vector>
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
    QColor GridColor = "#808080";
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
                p.fillRect(rect, "#800080");
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
    auto pos1 = rules.find("b");
    auto pos2 = rules.find("s");
    Game.alive_count.clear();
    Game.dead_count.clear();
    if (pos1 != std::string::npos and pos2 !=std::string::npos) {
        std::string arg1 = rules.substr(pos1+1, -pos1 - 1 +pos2);
        std::string arg2 = rules.substr(pos2+1, rules.size()- 1 - pos2);
        std::cout<<arg1 <<" "<<arg2<<std::endl;
        for(auto i: arg1){
            if (i - '0' > 0 and i - '0' < 10){
                Game.dead_count.push_back(i-'0');
            }else {
                wrong_rules();
                return;
            }
        }
        for(auto i: arg2){
            if (i - '0' > 0 and i - '0' < 10){
                Game.alive_count.push_back(i-'0');
            }else {
                wrong_rules();
                return;
            }
        }
    }
}

void field::wrong_rules(){
    QMessageBox::information(this,
                                    tr("Wrong rules"),
                                    tr("Right format: b3s23."),
                                    QMessageBox::Ok);
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
    std::fill(Game.ThisField.begin(),Game.ThisField.end(), false);
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
    Game.FieldSize_x_ = x;
    std::vector<bool> f(x*Game.FieldSize_y_, false);
    Game.ThisField = f;
    Game.NextField = f;
    update();
}
void field::on_change_size_y_clicked(int y)
{
    timer->stop();
    Game.FieldSize_y_ = y;
    std::vector<bool> f(y*Game.FieldSize_x_, false);
    Game.ThisField = f;
    Game.NextField = f;
    update();
}
