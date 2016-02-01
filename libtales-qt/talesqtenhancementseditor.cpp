#include "talesqtenhancementseditor.h"
#include "ui_talesqtenhancementseditor.h"
#include "talesqtstatevar.h"

using namespace Tales;

TalesQtEnhancementsEditor::TalesQtEnhancementsEditor(QWidget *parent) :
    QWidget(parent),
    enhancementsEditor_(appState_.editor().enhancementsEditor()),
    ui(new Ui::TalesQtEnhancementsEditor)
{
    ui->setupUi(this);
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
