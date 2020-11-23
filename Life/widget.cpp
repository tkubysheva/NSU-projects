#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , ThisField(new bool [FieldSize_x_*FieldSize_y_])
    , NextField(new bool [FieldSize_x_*FieldSize_y_])
{
    ui->setupUi(this);
    memset(ThisField, false, sizeof(bool) * FieldSize_x_ * FieldSize_y_);
    memset(NextField, false, sizeof(bool) * FieldSize_x_ * FieldSize_y_);
}

Widget::~Widget()
{
    delete [] ThisField;
    delete [] NextField;
    delete ui;
}
double Widget::cell_size_height(){
    return (double)height()/FieldSize_y_;
}

double Widget::cell_size_width(){
    return (double)width()/FieldSize_x_;
}
void Widget::PaintField(QPainter &p){
    QColor GridColor = "#808080";
    p.setPen(GridColor);
    for(double i = 0; i <= width(); i+= cell_size_width()){
        p.drawLine(i, 0, i, height());
    }
    for(double i = 0; i <= height(); i+= cell_size_height()){
        p.drawLine(0, i, width(), i);
    }
}

void Widget::PaintCells(QPainter &p){
    for(int i = 0; i < FieldSize_y_; ++i){
        for(int j = 0; j < FieldSize_x_; ++j){
            if(ThisField[i*FieldSize_x_ +j]){
                QRectF rect(cell_size_width()*j,cell_size_height()*i,cell_size_width(), cell_size_height());
                p.fillRect(rect, "#800080");
            }
        }
    }
}

void Widget::paintEvent(QPaintEvent *){
    QPainter paint(this);
    PaintField(paint);
    PaintCells(paint);
}

bool Widget::will_be_alive(int x, int y){
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
    return ((alive_nearby == 2 and ThisField[x + y*FieldSize_x_]) or alive_nearby == 3) ? true : false;
}

void Widget::next_field_generation(){
    for(int i = 0; i < FieldSize_y_; ++i){
        for(int j = 0; j < FieldSize_x_; ++j){
            NextField[i*FieldSize_x_ + j] = will_be_alive(j, i);
        }
    }
    GameOver = field_equal();
}

void Widget::converse_field(){
    for(int i = 0; i < FieldSize_y_; ++i){
        for(int j = 0; j < FieldSize_x_; ++j){
            ThisField[i*FieldSize_x_ + j] = NextField[i*FieldSize_x_ + j];
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *clik){
    int i = clik->x()/cell_size_width();
    int j = clik->y()/cell_size_height();
    ThisField[j*FieldSize_x_ + i]= !ThisField[j*FieldSize_x_ + i];
    update();
}

void Widget::on_clear_clicked()
{
    GameOver = true;
    memset(ThisField, false, sizeof(bool) * FieldSize_x_ * FieldSize_y_);
    update();
}

void Widget::on_onestep_clicked()
{
    next_field_generation();
    converse_field();
    update();
}

bool Widget::field_equal(){
    for(int i = 0; i < FieldSize_y_; ++i){
        for(int j = 0; j < FieldSize_x_; ++j){
            if(ThisField[i*FieldSize_x_ + j] != NextField[i*FieldSize_x_ + j])
                return false;
        }
    }
    return true;
}

void Widget::on_start_clicked()
{

    GameOver = false;
    while (!GameOver){
        qApp->processEvents();
        next_field_generation();
        converse_field();
        update();
    }
    GameOver = true;
}

void Widget::on_stop_clicked()
{
    GameOver = true;
}

void Widget::on_change_size_clicked()
{
    GameOver = true;
    FieldSize_x_ = ui->FieldSize_x->value();
    FieldSize_y_ = ui->FieldSize_y->value();
    delete [] ThisField;
    delete [] NextField;
    ThisField = new bool [FieldSize_x_*FieldSize_y_];
    NextField = new bool [FieldSize_x_*FieldSize_y_];
    for(int i = 0; i < FieldSize_y_; ++i){
        for(int j = 0; j < FieldSize_x_; ++j){
            NextField[i*FieldSize_x_ + j] = false;
            ThisField[i*FieldSize_x_ + j] = false;
        }
    }
    update();
}
