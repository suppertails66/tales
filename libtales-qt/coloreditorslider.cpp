#include "coloreditorslider.h"
#include "ui_coloreditorslider.h"

ColorEditorSlider::ColorEditorSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorEditorSlider)
{
    ui->setupUi(this);
}

ColorEditorSlider::~ColorEditorSlider()
{
    delete ui;
}

void ColorEditorSlider::setLabel(const std::string& label__) {
    ui->colorLabel->setText(label__.c_str());
}

void ColorEditorSlider::setValue(int value__) {
    ui->colorSlider->setValue(value__);
    ui->colorSpinBox->setValue(value__);
}

int ColorEditorSlider::value() {
    return ui->colorSpinBox->value();
}


/*void ColorEditorSlider::on_colorSlider_sliderMoved(int position)
{
    setValue(position);
    emit valueChanged(position);
}

void ColorEditorSlider::on_colorSpinBox_editingFinished()
{
    setValue(ui->colorSpinBox->value());
    emit valueChanged(ui->colorSpinBox->value());
} */

void ColorEditorSlider::on_colorSpinBox_valueChanged(int arg1)
{
    setValue(arg1);
    emit valueChanged(ui->colorSpinBox->value());
}

void ColorEditorSlider::on_colorSlider_actionTriggered(int action)
{
    setValue(ui->colorSlider->sliderPosition());
}
