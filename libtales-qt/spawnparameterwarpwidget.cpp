#include "spawnparameterwarpwidget.h"
#include "ui_spawnparameterwarpwidget.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

SpawnParameterWarpWidget::SpawnParameterWarpWidget(QWidget *parent) :
    QWidget(parent),
    levelObjectEntry_(0),
    ui(new Ui::SpawnParameterWarpWidget)
{
    ui->setupUi(this);

    for (int i = 0x1E; i < 0xFF; i += 0x20) {
        ui->warpSizeComboBox->addItem(
                    QString((StringConversion::toString(i)
                             + " px").c_str()));
    }
}

SpawnParameterWarpWidget::~SpawnParameterWarpWidget()
{
    delete ui;
}

void SpawnParameterWarpWidget::setLevelObjectGraphicSceneLayer(
        LevelObjectGraphicSceneLayer& levelObjectGraphicSceneLayer__) {
    levelObjectGraphicSceneLayer_ = &levelObjectGraphicSceneLayer__;
}

void SpawnParameterWarpWidget
    ::setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__) {
    levelObjectEntry_ = &levelObjectEntry__;
}

void SpawnParameterWarpWidget::loadValue(Tbyte value) {
    if (levelObjectGraphicSceneLayer_ != 0) {
        ui->warpDestinationComboBox->clear();

        if (levelObjectGraphicSceneLayer_->warpDestinationCollection() != 0) {

            const WarpDestinationCollection& destinations
                    = *(levelObjectGraphicSceneLayer_->warpDestinationCollection());

            for (int i = 0; i < destinations.size(); i++) {
                WarpDestination destination
                        = destinations[i];
                std::string destString;
    //            destString += StringConversion::toString(i);
    //            destString += ": ";
                if (destination.primaryMapDestination()
                        == PrimaryMaps::worldMap) {
                    if (destination.destinationSpawnIndex() == 0xFF) {
                        destString += "World map: Coco Island escape cutscene";
                    }
                    else {
                        destString += "World map, on area ";
                        destString += StringConversion::toString(
                                    destination.destinationSpawnIndex());
                    }
                }
                else {
                    destString += StringConversion::toString(
                                destination.primaryMapDestination());
                    destString += "-";
                    destString += StringConversion::toString(
                                destination.subMapDestination());
                    destString += ", spawn point ";
                    destString += StringConversion::toString(
                                destination.destinationSpawnIndex());
                }

                ui->warpDestinationComboBox->addItem(
                            QString(destString.c_str()));
            }
        }
    }

    ui->verticalOrientationBox->setChecked(
                (value & 0x80));
    ui->horizontalOrientationBox->setChecked(
                !(value & 0x80));
    ui->warpDestinationComboBox->setCurrentIndex(
                value & 0x0F);
    ui->warpSizeComboBox->setCurrentIndex(
                (value & 0x70) >> 4);
}

void SpawnParameterWarpWidget
    ::on_warpSizeComboBox_activated(int index) {
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0x8F)
                | (index << 4));
}

void SpawnParameterWarpWidget
    ::on_warpDestinationComboBox_activated(int index) {
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0xF0)
                | (index & 0x0F));
}

void SpawnParameterWarpWidget
    ::on_horizontalOrientationBox_clicked(bool checked) {
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0x7F));
}

void SpawnParameterWarpWidget
    ::on_verticalOrientationBox_clicked(bool checked) {
    levelObjectEntry_->setSpawnParameter(
                (levelObjectEntry_->spawnParameter() & 0x7F)
                    | 0x80);
}
