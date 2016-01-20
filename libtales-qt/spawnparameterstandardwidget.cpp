#include "spawnparameterstandardwidget.h"
#include "ui_spawnparameterstandardwidget.h"
#include "gamedata/ObjectStates.h"
#include "util/StringConversion.h"
#include <string>
#include <iostream>

using namespace Tales;
using namespace Luncheon;

SpawnParameterStandardWidget::SpawnParameterStandardWidget(QWidget *parent) :
    QWidget(parent),
    levelObjectEntry_(0),
    ui(new Ui::SpawnParameterStandardWidget)
{
    ui->setupUi(this);
}

SpawnParameterStandardWidget::~SpawnParameterStandardWidget()
{
    delete ui;
}

void SpawnParameterStandardWidget
    ::setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__) {
    levelObjectEntry_ = &levelObjectEntry__;
}

void SpawnParameterStandardWidget::loadValue(Tbyte value) {
    // lazy check for initialization
//    if ((ui->initialStateBox->count() > 0)
//        && (value == levelObjectEntry_->spawnParameter())) {
//        return;
//    }

    ui->initialStateBox->clear();

    int numStates = ObjectStates::numStatesPerObject(
                levelObjectEntry_->objectTypeID());

    for (int i = 0; i < numStates; i++) {
        ObjectStateInfo stateInfo
                = ObjectStates::objectStateInfo(
                    levelObjectEntry_->objectTypeID(),
                    i + 1);

        ui->initialStateBox->addItem(
                    QString(
                        (
                            StringConversion::toString(stateInfo.stateNum)
                            + ": "
                            + std::string(stateInfo.stateName)
                        ).c_str()
                    ),
                    QVariant(stateInfo.stateNum)
                );
    }

    if (value != 0) {
        // value - 1 would work here except that we handle a few
        // exceptional parameter values manually
        for (int i = 0; i < ui->initialStateBox->count(); i++) {
            if (ui->initialStateBox->itemData(i).toInt()
                    == value) {
                ui->initialStateBox->setCurrentIndex(i);
            }
        }
    }
    else {
        ui->initialStateBox->setCurrentIndex(value + 1);
    }
}

void SpawnParameterStandardWidget::on_initialStateBox_activated(int index)
{
    levelObjectEntry_->setSpawnParameter(
                ui->initialStateBox->itemData(index).toInt());
}
