#ifndef FIELD_H
#define FIELD_H

#include "game.h"
#include "saveload.h"
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class field;
}
QT_END_NAMESPACE


class Field : public QWidget {
    Q_OBJECT
public slots:
    void on_clear_clicked();
    void on_one_step_clicked();
    void on_start_clicked();
    void on_stop_clicked();
    void on_save_clicked();
    void on_change_size_x_clicked(int x);
    void on_change_size_y_clicked(int x);

    void generation_next_field();

public:
    Field(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *paint) override;
    void mousePressEvent(QMouseEvent *clik) override;
    void mouseMoveEvent(QMouseEvent *clik) override;
    load_data load_clicked();
    void change_rules(std::vector<int> &b, std::vector<int> &s);

private:
    SaveLoad file_helper;
    Game game_;
    void PaintField(QPainter &p);
    void PaintCells(QPainter &p);
    QTimer *timer;
    QColor GridColor = "#808080";
    QColor CellColor = "#800080";
    double cell_size_height();
    double cell_size_width();
    bool change_rules_file(const std::string &rules);
    void wrong_rules();
    void wrong_file();
    void clear_file(std::string filename);
    bool data_processing(const std::string &s2, const int &x, const int &y, std::vector<bool> &field);
    bool new_size_processing(const std::string &s, int &x, int &y);
};
#endif// FIELD_H
