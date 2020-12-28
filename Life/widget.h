#ifndef WIDGET_H
#define WIDGET_H

#include "field.h"
#include "game.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void load_clicked();
    void change_rules();

private:
    Ui::Widget *ui;
    Field *Field_;
    void rules_update(const std::vector<int> &b, const std::vector<int> &s);
};
#endif// WIDGET_H
