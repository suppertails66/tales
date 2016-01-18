#include "lengthmapvalueeditdialog.h"
#include "ui_lengthmapvalueeditdialog.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

LengthMapValueEditDialog::LengthMapValueEditDialog(
                               int valueIndex__,
                               Tales::LengthMapValue& value__,
                               QWidget *parent) :
    QDialog(parent),
    valueIndex_(valueIndex__),
    value_(value__),
    ui(new Ui::LengthMapValueEditDialog)
{
    ui->setupUi(this);

    ui->indexLabel->setText(
                StringConversion::toString(valueIndex__).c_str());
    ui->magnitudeSpinBox->setValue(value_.magnitude());
    if (value_.direction() == LengthMapValue::backward) {
        ui->reversedCheckBox->setChecked(true);
    }
}

LengthMapValueEditDialog::~LengthMapValueEditDialog()
{
    delete ui;
}

void LengthMapValueEditDialog::on_magnitudeSpinBox_valueChanged(int arg1)
{
    value_.setMagnitude(arg1);
}

void LengthMapValueEditDialog::on_reversedCheckBox_clicked(bool checked)
{
    if (checked) {
        value_.setDirection(LengthMapValue::backward);
    }
    else {
        value_.setDirection(LengthMapValue::forward);
    }
}
