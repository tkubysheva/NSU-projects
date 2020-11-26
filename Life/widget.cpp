#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , Field_(new field(this))
{
    ui->setupUi(this);
    connect(ui->start, SIGNAL(clicked()), Field_,SLOT(start_clicked()));
    connect(ui->stop, SIGNAL(clicked()), Field_,SLOT(stop_clicked()));
    connect(ui->clear, SIGNAL(clicked()), Field_,SLOT(on_clear_clicked()));
    connect(ui->FieldSize_x, SIGNAL(valueChanged(int)), Field_, SLOT(on_change_size_x_clicked(int)));
    connect(ui->FieldSize_y, SIGNAL(valueChanged(int)), Field_, SLOT(on_change_size_y_clicked(int)));
    connect(ui->one_step, SIGNAL(clicked()), Field_, SLOT(on_one_step_clicked()));
    connect(ui->rules, SIGNAL(textChanged(QString)), Field_, SLOT(change_rules(QString)));

    ui->horizontalLayout->addWidget(Field_);
}



Widget::~Widget()
{
    delete ui;
    delete Field_;
}


