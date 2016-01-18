#include "slopespeedselectorwidget.h"
#include "ui_slopespeedselectorwidget.h"

SlopeSpeedSelectorWidget::SlopeSpeedSelectorWidget(QWidget *parent) :
    QWidget(parent),
    number_(0),
    ui(new Ui::SlopeSpeedSelectorWidget)
{
    ui->setupUi(this);
}

SlopeSpeedSelectorWidget::~SlopeSpeedSelectorWidget()
{
    delete ui;
}

void SlopeSpeedSelectorWidget::setLabel(const std::string& label__) {
    ui->label->setText(
                label__.c_str());
}

void SlopeSpeedSelectorWidget::setValue(int value) {
    ui->spinBox->setValue(value);
}

void SlopeSpeedSelectorWidget::setNumber(int number__) {
    number_ = number__;
}

int SlopeSpeedSelectorWidget::value() {
    return ui->spinBox->value();
}


void SlopeSpeedSelectorWidget::on_spinBox_valueChanged(int arg1)
{
    emit valueChanged(number_, arg1);
}
