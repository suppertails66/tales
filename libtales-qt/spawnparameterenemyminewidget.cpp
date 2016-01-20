#include "spawnparameterenemyminewidget.h"
#include "ui_spawnparameterenemyminewidget.h"
#include <iostream>

using namespace Tales;

SpawnParameterEnemyMineWidget::SpawnParameterEnemyMineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpawnParameterEnemyMineWidget)
{
    ui->setupUi(this);
}

SpawnParameterEnemyMineWidget::~SpawnParameterEnemyMineWidget()
{
    delete ui;
}

void SpawnParameterEnemyMineWidget
    ::setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__) {
    levelObjectEntry_ = &levelObjectEntry__;
}

void SpawnParameterEnemyMineWidget::loadValue(Tbyte value) {
    if ((value & 0x80) == 0) {
        if (!ui->passiveMineButton->isChecked()) {
            ui->passiveMineButton->setChecked(true);
        }
        ui->mineDropperSettingsWidget->setEnabled(false);
    }
    else if (value == 0xFF) {
        if (!ui->droppedMineButton->isChecked()) {
            ui->droppedMineButton->setChecked(true);
        }
        ui->mineDropperSettingsWidget->setEnabled(false);
    }
    else {
        if (!ui->mineDropperButton->isChecked()) {
            ui->mineDropperButton->setChecked(true);
        }
        ui->mineDropperSettingsWidget->setEnabled(true);
        ui->orientationComboBox->setCurrentIndex(
                    (value & 0x70) >> 4);
        ui->metatileCoverageSpinBox->setValue(
                    (value & 0x0F));
    }
}

void SpawnParameterEnemyMineWidget::on_passiveMineButton_clicked(bool checked)
{
    levelObjectEntry_->setSpawnParameter(
                levelObjectEntry_->spawnParameter() & 0x7F);
    loadValue(levelObjectEntry_->spawnParameter());
}

void SpawnParameterEnemyMineWidget::on_droppedMineButton_clicked(bool checked)
{
    levelObjectEntry_->setSpawnParameter(0xFF);
    loadValue(levelObjectEntry_->spawnParameter());
}

void SpawnParameterEnemyMineWidget::on_mineDropperButton_clicked(bool checked)
{
//    levelObjectEntry_->setSpawnParameter(
//                (levelObjectEntry_->spawnParameter() & 0xBF) | 0x80);
    levelObjectEntry_->setSpawnParameter(0x81);
    loadValue(levelObjectEntry_->spawnParameter());
}

void SpawnParameterEnemyMineWidget::on_orientationComboBox_activated(int index)
{
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0x8F)
                | ((index & 0x07) << 4));
}

void SpawnParameterEnemyMineWidget::on_metatileCoverageSpinBox_valueChanged(int arg1)
{
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0xF0)
                | (arg1 & 0x0F));
}
