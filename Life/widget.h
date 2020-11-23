#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *paint) override;
    void PaintField(QPainter&p);
    void PaintCells(QPainter &p);
    void mousePressEvent(QMouseEvent *clik);
private slots:
    void on_clear_clicked();

    void on_onestep_clicked();

    void on_start_clicked();

    void on_stop_clicked();



    void on_change_size_clicked();

private:
    Ui::Widget *ui;
    bool GameOver = true;
    int FieldSize_x_ = 20;
    int FieldSize_y_ = 20;
    bool* ThisField;
    bool* NextField;
    double cell_size_height();
    double cell_size_width();
    void update_after_press();
    void next_field_generation();
    bool will_be_alive(int x, int y);
    void converse_field();
    bool field_equal();
};
#endif // WIDGET_H
