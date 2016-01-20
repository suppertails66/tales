#include "spawnparametermanualwidget.h"
#include "ui_spawnparametermanualwidget.h"

using namespace Tales;

SpawnParameterManualWidget::SpawnParameterManualWidget(QWidget *parent) :
    QWidget(parent),
    levelObjectEntry_(0),
    ui(new Ui::SpawnParameterManualWidget)
{
    ui->setupUi(this);
}

SpawnParameterManualWidget::~SpawnParameterManualWidget()
{
    delete ui;
}

void SpawnParameterManualWidget
    ::setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__) {
    levelObjectEntry_ = &levelObjectEntry__;
}

void SpawnParameterManualWidget::loadValue(Tbyte value) {
    ui->parameterBox->setValue((int)(value));
}

void SpawnParameterManualWidget::on_parameterBox_valueChanged(int arg1)
{
    levelObjectEntry_->setSpawnParameter((Tbyte)(arg1));
}
