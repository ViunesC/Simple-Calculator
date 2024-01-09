#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->mainLineEdit->setMinimumSize(181,41);
    ui->mainLineEdit->setMaximumSize(181,41);

    // set-up signal and slots
    connect(ui->numpad0, &QPushButton::pressed, [this](){
        expression += "0";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad1, &QPushButton::pressed, [this](){
        expression += "1";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad2, &QPushButton::pressed, [this](){
        expression += "2";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad3, &QPushButton::pressed, [this](){
        expression += "3";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad4, &QPushButton::pressed, [this](){
        expression += "4";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad5, &QPushButton::pressed, [this](){
        expression += "5";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad6, &QPushButton::pressed, [this](){
        expression += "6";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad7, &QPushButton::pressed, [this](){
        expression += "7";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad8, &QPushButton::pressed, [this](){
        expression += "8";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->numpad9, &QPushButton::pressed, [this](){
        expression += "9";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->btnPlus, &QPushButton::pressed, [this](){
        expression += "+";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->btnMinus, &QPushButton::pressed, [this](){
        expression += "-";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->btnMultiply, &QPushButton::pressed, [this](){
        expression += "*";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->btnDivide, &QPushButton::pressed, [this](){
        expression += "/";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->btnLbracket, &QPushButton::pressed, [this](){
        expression += "(";
        ui->mainLineEdit->setText(expression);
    });

    connect(ui->btnRbracket, &QPushButton::pressed, [this](){
        expression += ")";
        ui->mainLineEdit->setText(expression);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnClear_clicked()
{
    expression = "";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_btnDelete_clicked()
{
    expression = expression.chopped(1);
    ui->mainLineEdit->setText(expression);
}


void Widget::on_btnEqual_clicked()
{
    calculator cal_inst;
    expression = cal_inst.calculate(expression);
    ui->mainLineEdit->setText(expression);
}

