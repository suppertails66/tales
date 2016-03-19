#include "talesqtenhancementseditor.h"
#include "ui_talesqtenhancementseditor.h"
#include "talesqtstatevar.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "util/StringConversion.h"
#include <iostream>

using namespace Tales;

TalesQtEnhancementsEditor::TalesQtEnhancementsEditor(QWidget *parent) :
    QWidget(parent),
    enhancementsEditor_(appState_.editor().enhancementsEditor()),
    ui(new Ui::TalesQtEnhancementsEditor)
{
    ui->setupUi(this);

    for (int i = HackSettings::startOnLevelHackAreaBase;
         i < HackSettings::startOnLevelHackAreaLimit;
         i++) {
        ui->startAreaBox->addItem(StringConversion::toString(i).c_str(), i);
    }

    reloadStartLevelDisplayValues();
}

TalesQtEnhancementsEditor::~TalesQtEnhancementsEditor()
{
    delete ui;
}

void TalesQtEnhancementsEditor::refreshDisplay() {
    switch (enhancementsEditor_.hackSettings().doubleJumpFixOption()) {
    case HackSettings::doubleJumpFixOff:
        ui->doubleJumpFixBox->setChecked(false);
        break;
    case HackSettings::doubleJumpFixOn:
        ui->doubleJumpFixBox->setChecked(true);
        break;
    default:
        break;
    }

    switch (enhancementsEditor_.hackSettings().maxHeightFixOption()) {
    case HackSettings::maxHeightFixOff:
        ui->maxHeightFixBox->setChecked(false);
        break;
    case HackSettings::maxHeightFixOn:
        ui->maxHeightFixBox->setChecked(true);
        break;
    default:
        break;
    }

    switch (enhancementsEditor_.hackSettings().bombJumpFixOption()) {
    case HackSettings::bombJumpFixOff:
        ui->bombJumpFixBox->setChecked(false);
        break;
    case HackSettings::bombJumpFixOn:
        ui->bombJumpFixBox->setChecked(true);
        break;
    default:
        break;
    }

    switch (enhancementsEditor_.hackSettings().inventoryHackOption()) {
    case HackSettings::inventoryHackOff:
        ui->inventoryHackOffBox->setChecked(true);
        break;
    case HackSettings::inventoryHackOnBasic:
        ui->inventoryHackBasicBox->setChecked(true);
        break;
    case HackSettings::inventoryHackOnFull:
        ui->inventoryHackFullBox->setChecked(true);
        break;
    case HackSettings::inventoryHackOnHotswapOnly:
        ui->inventoryHackHotswapOnlyBox->setChecked(true);
        break;
    default:
        break;
    }

    switch (enhancementsEditor_.hackSettings().flightHackOption()) {
    case HackSettings::flightHackOff:
        ui->flightHackOffBox->setChecked(true);
        break;
    case HackSettings::flightHackOnLimited:
        ui->flightLimitedBox->setChecked(true);
        break;
    case HackSettings::flightHackOnDisabled:
        ui->flightDisabledBox->setChecked(true);
        break;
    default:
        break;
    }

    switch (enhancementsEditor_.hackSettings().noGameOverHackOption()) {
    case HackSettings::noGameOverHackOff:
        ui->gameOverStandardBox->setChecked(true);
        break;
    case HackSettings::noGameOverHackOn:
        ui->gameOverNoneBox->setChecked(true);
        break;
    default:
        break;
    }

    switch (enhancementsEditor_.hackSettings().saveHackOption()) {
    case HackSettings::saveHackOff:
        ui->saveHackOffBox->setChecked(true);
        break;
    case HackSettings::autoSaveHackOn:
        ui->autoSaveHackOnBox->setChecked(true);
        break;
    case HackSettings::manualSaveHackOn:
        ui->manualSaveHackOnBox->setChecked(true);
        break;
    default:
        break;
    }

    reloadStartLevelDisplayValues();
}

void TalesQtEnhancementsEditor::refreshStartLevelDisplay() {
    switch (enhancementsEditor_.hackSettings().startOnLevelHackOption()) {
    case HackSettings::startOnLevelHackOff:
        ui->startLevelEnabledBox->setChecked(false);
        ui->startAreaBox->setEnabled(false);
        ui->startMapBox->setEnabled(false);
        ui->startSpawnBox->setEnabled(false);
        break;
    case HackSettings::startOnLevelHackOn:
        ui->startLevelEnabledBox->setChecked(true);
        ui->startAreaBox->setEnabled(true);
        ui->startMapBox->setEnabled(true);
        ui->startSpawnBox->setEnabled(true);
        break;
    default:
        break;
    }

    ui->startAreaBox->setCurrentIndex(
                enhancementsEditor_.hackSettings().startOnLevelHackArea()
                    - HackSettings::startOnLevelHackAreaBase);

    ui->startMapBox->setCurrentIndex(
                enhancementsEditor_.hackSettings().startOnLevelHackMap()
                    - 1);

    ui->startSpawnBox->setCurrentIndex(
                enhancementsEditor_.hackSettings().startOnLevelHackSpawn());
}

void TalesQtEnhancementsEditor::reloadStartLevelDisplayValues() {

    int numMaps = SubMaps::subMapCounts[
            enhancementsEditor_.hackSettings().startOnLevelHackArea()];
    ui->startMapBox->clear();
    for (int i = 0; i < numMaps; i++) {
        ui->startMapBox->addItem(StringConversion::toString(i + 1).c_str(), i + 1);
    }

    int numSpawns =
            appState_.editor().levelEditor().spawnPoints()
                .spawnsByMapnum(
                    enhancementsEditor_.hackSettings().startOnLevelHackArea(),
                    enhancementsEditor_.hackSettings().startOnLevelHackMap()).size();
    ui->startSpawnBox->clear();
    for (int i = 0; i < numSpawns; i++) {
        ui->startSpawnBox->addItem(StringConversion::toString(i).c_str(), i);
    }

    refreshStartLevelDisplay();
}

void TalesQtEnhancementsEditor::on_doubleJumpFixBox_clicked(bool checked)
{
    if (checked) {
        enhancementsEditor_.hackSettings().setDoubleJumpFixOption(
                    HackSettings::doubleJumpFixOn);
    }
    else {
        enhancementsEditor_.hackSettings().setDoubleJumpFixOption(
                    HackSettings::doubleJumpFixOff);
    }
}

void TalesQtEnhancementsEditor::on_maxHeightFixBox_clicked(bool checked)
{
    if (checked) {
        enhancementsEditor_.hackSettings().setMaxHeightFixOption(
                    HackSettings::maxHeightFixOn);
    }
    else {
        enhancementsEditor_.hackSettings().setMaxHeightFixOption(
                    HackSettings::maxHeightFixOff);
    }
}

void TalesQtEnhancementsEditor::on_bombJumpFixBox_clicked(bool checked)
{
    if (checked) {
        enhancementsEditor_.hackSettings().setBombJumpFixOption(
                    HackSettings::bombJumpFixOn);
    }
    else {
        enhancementsEditor_.hackSettings().setBombJumpFixOption(
                    HackSettings::bombJumpFixOff);
    }
}

void TalesQtEnhancementsEditor::on_inventoryHackOffBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setInventoryHackOption(
                HackSettings::inventoryHackOff);
}

void TalesQtEnhancementsEditor::on_inventoryHackHotswapOnlyBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setInventoryHackOption(
                HackSettings::inventoryHackOnHotswapOnly);
}

void TalesQtEnhancementsEditor::on_inventoryHackBasicBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setInventoryHackOption(
                HackSettings::inventoryHackOnBasic);
}

void TalesQtEnhancementsEditor::on_inventoryHackFullBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setInventoryHackOption(
                HackSettings::inventoryHackOnFull);
}

void TalesQtEnhancementsEditor::on_flightHackOffBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setFlightHackOption(
                HackSettings::flightHackOff);
}

void TalesQtEnhancementsEditor::on_flightLimitedBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setFlightHackOption(
                HackSettings::flightHackOnLimited);
}

void TalesQtEnhancementsEditor::on_flightDisabledBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setFlightHackOption(
                HackSettings::flightHackOnDisabled);
}

void TalesQtEnhancementsEditor::on_gameOverStandardBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setNoGameOverHackOption(
                HackSettings::noGameOverHackOff);
}

void TalesQtEnhancementsEditor::on_gameOverNoneBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setNoGameOverHackOption(
                HackSettings::noGameOverHackOn);
}

void TalesQtEnhancementsEditor::on_saveHackOffBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setSaveHackOption(
                HackSettings::saveHackOff);
}

void TalesQtEnhancementsEditor::on_autoSaveHackOnBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setSaveHackOption(
                HackSettings::autoSaveHackOn);
}

void TalesQtEnhancementsEditor::on_manualSaveHackOnBox_clicked(bool checked)
{
    enhancementsEditor_.hackSettings().setSaveHackOption(
                HackSettings::manualSaveHackOn);
}

void TalesQtEnhancementsEditor::on_startLevelEnabledBox_clicked(bool checked)
{
    if (checked) {
        enhancementsEditor_.hackSettings().setStartOnLevelHackOption(
                    HackSettings::startOnLevelHackOn);
    }
    else {
        enhancementsEditor_.hackSettings().setStartOnLevelHackOption(
                    HackSettings::startOnLevelHackOff);
    }

    refreshStartLevelDisplay();
}

void TalesQtEnhancementsEditor::on_startAreaBox_activated(int index)
{
    enhancementsEditor_.hackSettings().setStartOnLevelHackArea(
                ui->startAreaBox->itemData(index).toInt());
    enhancementsEditor_.hackSettings().setStartOnLevelHackMap(
                1);
    enhancementsEditor_.hackSettings().setStartOnLevelHackSpawn(
                0);

    reloadStartLevelDisplayValues();
}

void TalesQtEnhancementsEditor::on_startMapBox_activated(int index)
{
    enhancementsEditor_.hackSettings().setStartOnLevelHackMap(
                ui->startMapBox->itemData(index).toInt());
}

void TalesQtEnhancementsEditor::on_startSpawnBox_activated(int index)
{
    enhancementsEditor_.hackSettings().setStartOnLevelHackSpawn(
                ui->startSpawnBox->itemData(index).toInt());
}
