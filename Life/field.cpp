#include "field.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QString>
#include <fstream>

field::field(QWidget *parent) : QWidget(parent), timer(new QTimer(this)) {
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(generation_next_field()));
}
void field::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    PaintField(paint);
    PaintCells(paint);
}

double field::cell_size_height() {
    return (double) height() / Game.y();
}

double field::cell_size_width() {
    return (double) width() / Game.x();
}

void field::PaintField(QPainter &p) {
    p.setPen(GridColor);
    for (double i = 0; i <= width(); i += cell_size_width()) {
        p.drawLine(i, 0, i, height());
    }
    for (double i = 0; i <= height(); i += cell_size_height()) {
        p.drawLine(0, i, width(), i);
    }
}

void field::PaintCells(QPainter &p) {
    for (size_t i = 0; i < Game.y(); ++i) {
        for (size_t j = 0; j < Game.x(); ++j) {
            if (Game.is_alive(j, i)) {
                QRectF rect(cell_size_width() * j, cell_size_height() * i, cell_size_width(), cell_size_height());
                p.fillRect(rect, CellColor);
            }
        }
    }
}

void field::mousePressEvent(QMouseEvent *clik) {
    int i = clik->x() / cell_size_width();
    int j = clik->y() / cell_size_height();
    Game.change_state(i, j);
    update();
}

void field::change_rules(QString r) {
    std::string rules = r.toStdString();
    if (!Game.change_rules(rules)) {
        wrong_rules();
    }
}

void field::wrong_file() {
    QMessageBox::information(this, tr("Error"), tr("Wrong file's format."), QMessageBox::Ok);
}
void field::wrong_rules() {
    QMessageBox::information(this, tr("Wrong rules"), tr("Right format: b3s23."), QMessageBox::Ok);
}
void field::mouseMoveEvent(QMouseEvent *clik) {
    int i = clik->x() / cell_size_width();
    int j = clik->y() / cell_size_height();
    if (!Game.is_alive(i, j)) {
        Game.change_state(i, j);
        update();
    }
}

void field::on_clear_clicked() {
    timer->stop();
    Game.clear_field();
    update();
}

void field::on_one_step_clicked() {
    timer->stop();
    Game.next_field_generation();
    Game.converse_field();
    update();
}

void field::generation_next_field() {
    Game.next_field_generation();
    if (Game.field_equal()) {
        timer->stop();
    }
    Game.converse_field();
    update();
}

void field::on_start_clicked() {
    timer->start();
}

void field::on_stop_clicked() {
    timer->stop();
}

void field::on_change_size_x_clicked(int x) {
    timer->stop();
    Game.change_size(x, true);
    update();
}
void field::on_change_size_y_clicked(int y) {
    timer->stop();
    Game.change_size(y);
    update();
}

void field::on_save_clicked() {
    timer->stop();
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");
    std::string filename = str.toStdString();
    std::fstream f(filename);
    clear_file(filename);
    f << "x = " << Game.x() << "; y = " << Game.y() << std::endl;
    f << "b" << Game.dead_for_print() << "s" << Game.alive_for_print() << std::endl;
    int count = 0;
    for (size_t i = 0; i < Game.y(); ++i) {
        for (size_t j = 0; j < Game.x(); ++j) {
            if (j == 0) {
                if (i != 0) {
                    f << count << "$" << (Game.is_alive(j, i) ? "o" : "b");
                } else {
                    f << (Game.is_alive(j, i) ? "o" : "b");
                }
                count = 1;
            } else {
                if (Game.is_alive(j, i) == Game.is_alive(j - 1, i)) {
                    count++;
                } else {
                    f << count << (Game.is_alive(j, i) ? "o" : "b");
                    count = 1;
                }
            }
        }
        if (i == Game.y() - 1) {
            f << count << "$" << std::endl;
        }
    }
    f.close();
}

void field::clear_file(std::string filename) {
    std::ofstream ofs;
    ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

bool field::new_size_processing(const std::string &s, int &x, int &y) {
    std::string x_s, y_s;
    auto p = s.find(';');
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
bool field::data_processing(const std::string &s, const int &x, const int &y, std::vector<bool> &field) {
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
        ;
    }
    return true;
}
load_data field::load_clicked() {
    timer->stop();
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");
    std::string filename = str.toStdString();
    std::fstream f(filename);
    std::string size, data, x_s, y_s, r_s;
    int x, y;
    std::getline(f, size);
    std::getline(f, r_s);
    std::getline(f, data);
    f.close();
    if (!new_size_processing(size, x, y)) {
        wrong_file();
        return {false, 0, 0, ""};
    }
    std::vector<bool> field(x * y);
    std::fill(field.begin(), field.end(), false);
    if (!data_processing(data, x, y, field)) {
        wrong_file();
        return {false, 0, 0, ""};
    }
    if (!Game.change_rules(r_s)) {
        wrong_file();
        return {false, 0, 0, ""};
    }
    Game.change_size(x, true);
    Game.change_size(y);
    Game.converse_field(field);
    update();
    return {true, x, y, r_s};
}
