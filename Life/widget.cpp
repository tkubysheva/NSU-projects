#include "widget.h"
#include "ui_widget.h"
#include <vector>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), Field_(new Field(this)) {
    ui->setupUi(this);
    connect(ui->start, SIGNAL(clicked()), Field_, SLOT(on_start_clicked()));
    connect(ui->stop, SIGNAL(clicked()), Field_, SLOT(on_stop_clicked()));
    connect(ui->save, SIGNAL(clicked()), Field_, SLOT(on_save_clicked()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(load_clicked()));
    connect(ui->clear, SIGNAL(clicked()), Field_, SLOT(on_clear_clicked()));
    connect(ui->FieldSize_x, SIGNAL(valueChanged(int)), Field_, SLOT(on_change_size_x_clicked(int)));
    connect(ui->FieldSize_y, SIGNAL(valueChanged(int)), Field_, SLOT(on_change_size_y_clicked(int)));
    connect(ui->one_step, SIGNAL(clicked()), Field_, SLOT(on_one_step_clicked()));
    connect(ui->change, SIGNAL(clicked()), this, SLOT(change_rules()));
    ui->horizontalLayout->addWidget(Field_);
}

void Widget::rules_update(const std::vector<int> &b, const std::vector<int> &s) {
    ui->b1->setCheckState(Qt::Unchecked);
    ui->b2->setCheckState(Qt::Unchecked);
    ui->b3->setCheckState(Qt::Unchecked);
    ui->b4->setCheckState(Qt::Unchecked);
    ui->b5->setCheckState(Qt::Unchecked);
    ui->b6->setCheckState(Qt::Unchecked);
    ui->b7->setCheckState(Qt::Unchecked);
    ui->b8->setCheckState(Qt::Unchecked);
    ui->s1->setCheckState(Qt::Unchecked);
    ui->s2->setCheckState(Qt::Unchecked);
    ui->s3->setCheckState(Qt::Unchecked);
    ui->s4->setCheckState(Qt::Unchecked);
    ui->s5->setCheckState(Qt::Unchecked);
    ui->s6->setCheckState(Qt::Unchecked);
    ui->s7->setCheckState(Qt::Unchecked);
    ui->s8->setCheckState(Qt::Unchecked);

    for (const auto i : b) {
        if (i == 1) {
            ui->b1->setCheckState(Qt::Checked);
        }
        if (i == 2) {
            ui->b2->setCheckState(Qt::Checked);
        }
        if (i == 3) {
            ui->b3->setCheckState(Qt::Checked);
        }
        if (i == 4) {
            ui->b4->setCheckState(Qt::Checked);
        }
        if (i == 5) {
            ui->b5->setCheckState(Qt::Checked);
        }
        if (i == 6) {
            ui->b6->setCheckState(Qt::Checked);
        }
        if (i == 7) {
            ui->b7->setCheckState(Qt::Checked);
        }
        if (i == 8) {
            ui->b8->setCheckState(Qt::Checked);
        }
    }
    for (const auto i : s) {
        if (i == 1) {
            ui->s1->setCheckState(Qt::Checked);
        }
        if (i == 2) {
            ui->s2->setCheckState(Qt::Checked);
        }
        if (i == 3) {
            ui->s3->setCheckState(Qt::Checked);
        }
        if (i == 4) {
            ui->s4->setCheckState(Qt::Checked);
        }
        if (i == 5) {
            ui->s5->setCheckState(Qt::Checked);
        }
        if (i == 6) {
            ui->s6->setCheckState(Qt::Checked);
        }
        if (i == 7) {
            ui->s7->setCheckState(Qt::Checked);
        }
        if (i == 8) {
            ui->s8->setCheckState(Qt::Checked);
        }
    }
}

void Widget::change_rules() {
    std::vector<int> born, stay;
    if (ui->b1->isChecked()) {
        born.push_back(1);
    }
    if (ui->b2->isChecked()) {
        born.push_back(2);
    }
    if (ui->b3->isChecked()) {
        born.push_back(3);
    }
    if (ui->b4->isChecked()) {
        born.push_back(4);
    }
    if (ui->b5->isChecked()) {
        born.push_back(5);
    }
    if (ui->b6->isChecked()) {
        born.push_back(6);
    }
    if (ui->b7->isChecked()) {
        born.push_back(7);
    }
    if (ui->b8->isChecked()) {
        born.push_back(8);
    }
    if (ui->s1->isChecked()) {
        stay.push_back(1);
    }
    if (ui->s2->isChecked()) {
        stay.push_back(2);
    }
    if (ui->s3->isChecked()) {
        stay.push_back(3);
    }
    if (ui->s4->isChecked()) {
        stay.push_back(4);
    }
    if (ui->s5->isChecked()) {
        stay.push_back(5);
    }
    if (ui->s6->isChecked()) {
        stay.push_back(6);
    }
    if (ui->s7->isChecked()) {
        stay.push_back(7);
    }
    if (ui->s8->isChecked()) {
        stay.push_back(8);
    }
    Field_->change_rules(born, stay);
}
void Widget::load_clicked() {
    load_data ld = Field_->load_clicked();
    if (ld.success) {
        ui->FieldSize_x->setValue(ld.x);
        ui->FieldSize_y->setValue(ld.y);
        rules_update(ld.b, ld.s);
        update();
    }
}

Widget::~Widget() {
    delete ui;
    delete Field_;
}
