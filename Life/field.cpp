#include "field.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QString>
#include <cmath>
#include <fstream>
#include <string>

Field::Field(QWidget *parent) : QWidget(parent), timer(new QTimer(this)) {
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(generation_next_field()));
}
void Field::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    PaintField(paint);
    PaintCells(paint);
}

double Field::cell_size_height() {
    return (double) height() / game_.y();
}

double Field::cell_size_width() {
    return (double) width() / game_.x();
}

void Field::PaintField(QPainter &p) {
    p.setPen(GridColor);
    QRectF rect(0, 0, width() - 1, height() - 1);
    p.drawRect(rect);
    for (double i = 0; i <= width(); i += cell_size_width()) {
        p.drawLine(i, 0, i, height());
    }
    for (double i = 0; i <= height(); i += cell_size_height()) {
        p.drawLine(0, i, width(), i);
    }
}

void Field::PaintCells(QPainter &p) {
    for (size_t i = 0; i < game_.y(); ++i) {
        for (size_t j = 0; j < game_.x(); ++j) {
            if (game_.is_alive(j, i)) {
                QRectF rect(cell_size_width() * j, cell_size_height() * i, cell_size_width(), cell_size_height());
                p.fillRect(rect, CellColor);
            }
        }
    }
}

void Field::mousePressEvent(QMouseEvent *clik) {
    if (clik->x() > width() or clik->y() > height() or clik->x() < 0 or clik->y() < 0) { return; }
    int i = clik->x() / cell_size_width();
    int j = clik->y() / cell_size_height();
    game_.change_state(i, j);
    update();
}

void Field::wrong_file() {
    QMessageBox::information(this, tr("Error"), tr("Wrong file's format."), QMessageBox::Ok);
}

void Field::mouseMoveEvent(QMouseEvent *clik) {
    if (clik->x() > width() or clik->y() > height() or clik->x() < 0 or clik->y() < 0) { return; }
    int i = clik->x() / cell_size_width();
    int j = clik->y() / cell_size_height();
    if (!game_.is_alive(i, j)) {
        game_.change_state(i, j);
        update();
    }
}

void Field::on_clear_clicked() {
    timer->stop();
    game_.clear_field();
    update();
}

void Field::on_one_step_clicked() {
    timer->stop();
    game_.next_field_generation();
    game_.converse_field();
    update();
}

void Field::generation_next_field() {
    game_.next_field_generation();
    if (game_.field_equal()) {
        timer->stop();
    }
    game_.converse_field();
    update();
}

void Field::on_start_clicked() {
    timer->start();
}

void Field::on_stop_clicked() {
    timer->stop();
}

void Field::on_change_size_x_clicked(int x) {
    timer->stop();
    game_.change_size(x, true);
    update();
}
void Field::on_change_size_y_clicked(int y) {
    timer->stop();
    game_.change_size(y);
    update();
}

void Field::on_save_clicked() {
    timer->stop();
    std::vector<bool> field;
    for (size_t i = 0; i < game_.y(); ++i) {
        for (size_t j = 0; j < game_.x(); ++j) {
            field.push_back(game_.is_alive(j, i));
        }
    }
    file_helper.Save(game_.x(), game_.y(), field, game_.dead_for_print(), game_.alive_for_print());
}
void Field::change_rules(std::vector<int> &b, std::vector<int> &s) {
    timer->stop();
    game_.change_rules(b, s);
}

load_data Field::load_clicked() {
    timer->stop();
    load_data ld = file_helper.Load();
    if (!ld.success) {
        wrong_file();
    } else {
        game_.change_rules(ld.b, ld.s);
        game_.change_size(ld.x, true);
        game_.change_size(ld.y);
        game_.converse_field(ld.field);
        update();
    }
    return ld;
}
