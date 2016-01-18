#include "emeraldeditorwidget.h"
#include "ui_emeraldeditorwidget.h"
#include "util/StringConversion.h"
#include <cstdlib>

using namespace Tales;
using namespace Luncheon;

EmeraldEditorWidget::EmeraldEditorWidget(QWidget *parent) :
    QWidget(parent),
    emeraldNum_(0),
    powerUpData_(NULL),
    emeraldHealthRefills_(NULL),
    ui(new Ui::EmeraldEditorWidget)
{
    ui->setupUi(this);
}

EmeraldEditorWidget::~EmeraldEditorWidget()
{
    delete ui;
}

void EmeraldEditorWidget::refreshDisplay() {
    if (powerUpData_ != NULL) {
        ui->flightTimeBox->setValue(
                    (powerUpData_->flightTimePerPowerup(emeraldNum_) - 4)
                        / 256);
        ui->hpBox->setValue(
                    powerUpData_->maxHealthPerPowerup(emeraldNum_));
    }

    if (emeraldHealthRefills_ != NULL) {
        ui->hpRefillBox->setValue(
                    emeraldHealthRefills_->healthRefillPerEmerald(emeraldNum_));
    }
}

void EmeraldEditorWidget::setEmeraldNum(int emeraldNum__) {
    emeraldNum_ = emeraldNum__;
    ui->numberLabel->setText(
                (StringConversion::toString(emeraldNum_)).c_str());
}

void EmeraldEditorWidget::setPowerUpData(Tales::EditablePowerUpData& powerUpData__) {
    powerUpData_ = &powerUpData__;
}

void EmeraldEditorWidget::setEmeraldHealthRefills(
        Tales::EditableEmeraldHealthRefills& emeraldHealthRefills__) {
    emeraldHealthRefills_ = &emeraldHealthRefills__;
}

void EmeraldEditorWidget::on_flightTimeBox_editingFinished()
{
    if (powerUpData_ != NULL) {
        powerUpData_->flightTimePerPowerup(emeraldNum_)
                = (ui->flightTimeBox->value() * 256) + 4;
    }
}

void EmeraldEditorWidget::on_hpBox_editingFinished()
{
    if (powerUpData_ != NULL) {
        powerUpData_->maxHealthPerPowerup(emeraldNum_)
                = ui->hpBox->value();
    }
}

void EmeraldEditorWidget::on_hpRefillBox_editingFinished()
{
    if (emeraldHealthRefills_ != NULL) {
        emeraldHealthRefills_->healthRefillPerEmerald(
                    emeraldNum_) = ui->hpRefillBox->value();
    }
}
