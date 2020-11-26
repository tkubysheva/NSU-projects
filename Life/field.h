#ifndef FIELD_H
#define FIELD_H

#include <QTimer>
#include <QWidget>
#include "game.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class field; }
QT_END_NAMESPACE

class field : public QWidget{
    Q_OBJECT
public slots:
    void on_clear_clicked();
    void on_one_step_clicked();
    void start_clicked();
    void stop_clicked();
    void on_change_size_x_clicked(int x);
    void on_change_size_y_clicked(int x);
    void generation_next_field();
    void change_rules(QString);
public:
    field(QWidget *parent = nullptr);
    double cell_size_height();
    double cell_size_width();
    void wrong_rules();
    void paintEvent(QPaintEvent *paint) override;
    void PaintField(QPainter&p);
    void PaintCells(QPainter &p);
    void mousePressEvent(QMouseEvent *clik) override;
    void mouseMoveEvent(QMouseEvent *clik) override;
private:
    game Game;
    QTimer *timer;
};
#endif // FIELD_H
