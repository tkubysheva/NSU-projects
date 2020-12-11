#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), Field_(new field(this)) {
    ui->setupUi(this);
    connect(ui->start, SIGNAL(clicked()), Field_, SLOT(on_start_clicked()));
    connect(ui->stop, SIGNAL(clicked()), Field_, SLOT(on_stop_clicked()));
    connect(ui->save, SIGNAL(clicked()), Field_, SLOT(on_save_clicked()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(load_clicked()));
    connect(ui->clear, SIGNAL(clicked()), Field_, SLOT(on_clear_clicked()));
    connect(ui->FieldSize_x, SIGNAL(valueChanged(int)), Field_, SLOT(on_change_size_x_clicked(int)));
    connect(ui->FieldSize_y, SIGNAL(valueChanged(int)), Field_, SLOT(on_change_size_y_clicked(int)));
    connect(ui->one_step, SIGNAL(clicked()), Field_, SLOT(on_one_step_clicked()));
    connect(ui->rules, SIGNAL(textChanged(QString)), Field_, SLOT(change_rules(QString)));

    ui->horizontalLayout->addWidget(Field_);
}

void Widget::load_clicked() {
    load_data ld = Field_->load_clicked();
    if (ld.success) {
        ui->FieldSize_x->setValue(ld.x);
        ui->FieldSize_y->setValue(ld.y);
        ui->rules->setText(QString::fromStdString(ld.r));
    }
}

Widget::~Widget() {
    delete ui;
    delete Field_;
}
