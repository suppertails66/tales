#include "spawnparametermissilelauncherwidget.h"
#include "ui_spawnparametermissilelauncherwidget.h"

using namespace Tales;

SpawnParameterMissileLauncherWidget::SpawnParameterMissileLauncherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpawnParameterMissileLauncherWidget)
{
    ui->setupUi(this);
}

SpawnParameterMissileLauncherWidget::~SpawnParameterMissileLauncherWidget()
{
    delete ui;
}

void SpawnParameterMissileLauncherWidget
    ::setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__) {
    levelObjectEntry_ = &levelObjectEntry__;
}

void SpawnParameterMissileLauncherWidget::loadValue(Tbyte value) {
    ui->orientationComboBox->setCurrentIndex(
                (value & 0x70) >> 4);

    ui->metatileCoverageSpinBox->setValue(
                (value & 0x0F));

    if ((value & 0x80) != 0) {
        ui->facingRightButton->setChecked(true);
    }
    else {
        ui->facingLeftButton->setChecked(true);
    }
}

void SpawnParameterMissileLauncherWidget::on_orientationComboBox_activated(int index)
{
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0x8F)
                | ((index & 0x07) << 4));
}

void SpawnParameterMissileLauncherWidget::on_metatileCoverageSpinBox_valueChanged(int arg1)
{
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0xF0)
                | (arg1 & 0x0F));
}

void SpawnParameterMissileLauncherWidget::on_facingLeftButton_clicked(bool checked)
{
    if (checked) {
        levelObjectEntry_->setSpawnParameter(
                    (levelObjectEntry_->spawnParameter() & 0x7F));
    }
}

void SpawnParameterMissileLauncherWidget::on_facingRightButton_clicked(bool checked)
{
    if (checked) {
        levelObjectEntry_->setSpawnParameter(
                    (levelObjectEntry_->spawnParameter() | 0x80));
    }
}
