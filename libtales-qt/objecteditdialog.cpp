#include "objecteditdialog.h"
#include "ui_objecteditdialog.h"
#include "spawnparametermanualwidget.h"
#include "spawnparameterwarpwidget.h"
#include "spawnparameterstandardwidget.h"
#include "spawnparametermissilelauncherwidget.h"
#include "spawnparameterenemyminewidget.h"
#include "ui_spawnparametermanualwidget.h"
#include "ui_spawnparameterwarpwidget.h"
#include "ui_spawnparameterstandardwidget.h"
#include "ui_spawnparametermissilelauncherwidget.h"
#include "ui_spawnparameterenemyminewidget.h"
#include "gamedata/ObjectStates.h"
#include "gamedata/ObjectTypeID.h"
#include "util/StringConversion.h"
#include "editors/ObjectDisplayCache.h"
#include "talesqtformatconversion.h"
#include "editors/ObjectToGraphics.h"
#include <QLabel>
#include <iostream>

using namespace Tales;
using namespace Luncheon;

ObjectEditDialog::ObjectEditDialog(Tales::LevelObjectGraphicSceneLayer&
                                    levelObjectGraphicSceneLayer__,
//            const Tales::ObjectGraphicsHeader& objectGraphicsHeader__,
            LevelObjectEntry& levelObjectEntry__,
            QWidget *parent) :
    QDialog(parent),
    levelObjectGraphicSceneLayer_(levelObjectGraphicSceneLayer__),
//    objectGraphicsHeader_(objectGraphicsHeader__),
    levelObjectEntry_(levelObjectEntry__),
    ui(new Ui::ObjectEditDialog)
{
    ui->setupUi(this);

    // extremely lazy hacky very bad connections so we can update
    // when the promoted spawn parameter editor widgets update
    QObject::connect(
                dynamic_cast<SpawnParameterStandardWidget*>(
                    ui->spawnParameterWidget->widget(0))
                    ->ui->initialStateBox,
                SIGNAL(activated(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterWarpWidget*>(
                    ui->spawnParameterWidget->widget(1))
                    ->ui->warpDestinationComboBox,
                SIGNAL(activated(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterWarpWidget*>(
                    ui->spawnParameterWidget->widget(1))
                    ->ui->warpSizeComboBox,
                SIGNAL(activated(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterWarpWidget*>(
                    ui->spawnParameterWidget->widget(1))
                    ->ui->horizontalOrientationBox,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterWarpWidget*>(
                    ui->spawnParameterWidget->widget(1))
                    ->ui->verticalOrientationBox,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterManualWidget*>(
                    ui->spawnParameterWidget->widget(2))
                    ->ui->parameterBox,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterMissileLauncherWidget*>(
                    ui->spawnParameterWidget->widget(3))
                    ->ui->orientationComboBox,
                SIGNAL(activated(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterMissileLauncherWidget*>(
                    ui->spawnParameterWidget->widget(3))
                    ->ui->metatileCoverageSpinBox,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterMissileLauncherWidget*>(
                    ui->spawnParameterWidget->widget(3))
                    ->ui->facingLeftButton,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterMissileLauncherWidget*>(
                    ui->spawnParameterWidget->widget(3))
                    ->ui->facingRightButton,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterEnemyMineWidget*>(
                    ui->spawnParameterWidget->widget(4))
                    ->ui->passiveMineButton,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterEnemyMineWidget*>(
                    ui->spawnParameterWidget->widget(4))
                    ->ui->droppedMineButton,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterEnemyMineWidget*>(
                    ui->spawnParameterWidget->widget(4))
                    ->ui->mineDropperButton,
                SIGNAL(clicked(bool)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterEnemyMineWidget*>(
                    ui->spawnParameterWidget->widget(4))
                    ->ui->orientationComboBox,
                SIGNAL(activated(int)),
                this,
                SLOT(onSpawnChange()));
    QObject::connect(
                dynamic_cast<SpawnParameterEnemyMineWidget*>(
                    ui->spawnParameterWidget->widget(4))
                    ->ui->metatileCoverageSpinBox,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(onSpawnChange()));

    // Set up object ID box
    for (int i = 0; i < ObjectTypeIDs::objectTypeIDLimit; i++) {
        if (ObjectTypeIDs::isObjectUsable(
                    static_cast<ObjectTypeIDs::ObjectTypeID>(i))) {
            ui->objectTypeComboBox->addItem(
                        QString((
                            StringConversion::toString(
                                    i
                                )
                                    + ": "
                                    + ObjectTypeIDs::nameOfObject(
                                        static_cast<ObjectTypeIDs::ObjectTypeID>(i))
                            ).c_str()), QVariant(i));
        }
    }

    reloadDisplay();
}

ObjectEditDialog::~ObjectEditDialog()
{
    delete ui;
}

void ObjectEditDialog::onSpawnChange() {
    refreshDisplay();
}

void ObjectEditDialog::reloadDisplay() {
    int newSpawnParameterIndex
           = findIndexOfObjectID(levelObjectEntry_.objectTypeID());
    if (newSpawnParameterIndex == -1) {
        ui->objectTypeComboBox->setCurrentIndex(0);
    }
    else {
        ui->objectTypeComboBox->setCurrentIndex(newSpawnParameterIndex);
    }

    ObjectGraphicInfo graphicInfo = ObjectToGraphics::objectToGraphics(
                levelObjectEntry_.objectTypeID());

    // Graphics must be compressed or special-cased
    if ((levelObjectEntry_.objectTypeID() == ObjectTypeIDs::itemPickup)
        || (graphicInfo.graphicCompressionType != GraphicCompressionTypes
                                                ::uncompressed)) {
        levelObjectGraphicSceneLayer_.refreshGraphicVRAMOffsets(
                    levelObjectEntry_,
                    graphicInfo);
    }

    // Check what kind of widget we need to display spawn parameter
    switch (ObjectStates::objectSpawnParameterType(
                levelObjectEntry_.objectTypeID())) {
    case ObjectStates::spawnParameterStandard:
        {
        ui->spawnParameterWidget->setCurrentIndex(0);
        SpawnParameterStandardWidget* widget
                = dynamic_cast<SpawnParameterStandardWidget*>(
                    ui->spawnParameterWidget->currentWidget());
        widget->setLevelObjectEntry(levelObjectEntry_);
        widget->loadValue(levelObjectEntry_.spawnParameter());
        }
        break;
    case ObjectStates::spawnParameterWarp:
        {
        ui->spawnParameterWidget->setCurrentIndex(1);
        SpawnParameterWarpWidget* widget
                = dynamic_cast<SpawnParameterWarpWidget*>(
                    ui->spawnParameterWidget->currentWidget());
        widget->setLevelObjectEntry(levelObjectEntry_);
        widget->setLevelObjectGraphicSceneLayer(
                    levelObjectGraphicSceneLayer_);
        widget->loadValue(levelObjectEntry_.spawnParameter());
        }
        break;
    case ObjectStates::spawnParameterManual:
        {
        ui->spawnParameterWidget->setCurrentIndex(2);
        SpawnParameterManualWidget* widget
                = dynamic_cast<SpawnParameterManualWidget*>(
                    ui->spawnParameterWidget->currentWidget());
        widget->setLevelObjectEntry(levelObjectEntry_);
        widget->loadValue(levelObjectEntry_.spawnParameter());
        }
        break;
    case ObjectStates::spawnParameterMissileLauncher:
        {
        ui->spawnParameterWidget->setCurrentIndex(3);
        SpawnParameterMissileLauncherWidget* widget
                = dynamic_cast<SpawnParameterMissileLauncherWidget*>(
                    ui->spawnParameterWidget->currentWidget());
        widget->setLevelObjectEntry(levelObjectEntry_);
        widget->loadValue(levelObjectEntry_.spawnParameter());
        }
        break;
    case ObjectStates::spawnParameterEnemyMine:
        {
        ui->spawnParameterWidget->setCurrentIndex(4);
        SpawnParameterEnemyMineWidget* widget
                = dynamic_cast<SpawnParameterEnemyMineWidget*>(
                    ui->spawnParameterWidget->currentWidget());
        widget->setLevelObjectEntry(levelObjectEntry_);
        widget->loadValue(levelObjectEntry_.spawnParameter());
        }
        break;
    default:
        break;
    }

    ui->xPosSpinBox->setValue(
                levelObjectEntry_.xPos());
    ui->yPosSpinBox->setValue(
                levelObjectEntry_.yPos());

    if (levelObjectEntry_.xDirectionFlag() == LevelObjectEntry::left) {
        ui->leftFacingButton->setChecked(true);
    }
    else {
        ui->rightFacingButton->setChecked(true);
    }

    if (levelObjectEntry_.blinkingFlag() == LevelObjectEntry::blinking) {
        ui->blinkingBox->setChecked(true);
    }
    else {
        ui->blinkingBox->setChecked(false);
    }

    if (levelObjectEntry_.invisibilityFlag() == LevelObjectEntry::invisible) {
        ui->invisibilityBox->setChecked(true);
    }
    else {
        ui->invisibilityBox->setChecked(false);
    }

    ui->leftTileVRAMIndexBox->setValue(
                levelObjectEntry_.leftTileVRAMIndex());
    ui->rightTileVRAMIndexBox->setValue(
                levelObjectEntry_.rightTileVRAMIndex());

    refreshDisplay();
}

void ObjectEditDialog::refreshDisplay() {
    // Update preview display
    ObjectDisplayCache display;

    levelObjectGraphicSceneLayer_
            .generateObjectPreview(display,
                                   levelObjectEntry_);
    if (levelObjectEntry_.objectTypeID() == ObjectTypeIDs::warp) {
        // Some objects get too large to display comfortably
        // at double scale: special-case them
        ui->graphicPreviewLabel->setPixmap(
                    TalesQtFormatConversion::graphicToPixmap(
                        display.graphic()).scaled(
                            display.graphic().w(),
                            display.graphic().h()));
    }
    else {
        ui->graphicPreviewLabel->setPixmap(
                    TalesQtFormatConversion::graphicToPixmap(
                        display.graphic()).scaled(
                            display.graphic().w() * 2,
                            display.graphic().h() * 2));
    }
}

Tales::LevelObjectEntry ObjectEditDialog::levelObjectEntry() {
    return levelObjectEntry_;
}

void ObjectEditDialog::on_vramAutofillButton_clicked()
{
    reloadDisplay();
}

int ObjectEditDialog::findIndexOfObjectID(ObjectTypeIDs::ObjectTypeID id) {
    for (int i = 0; i < ui->objectTypeComboBox->count(); i++) {
        if (static_cast<ObjectTypeIDs::ObjectTypeID>(
                    ui->objectTypeComboBox->itemData(i).toInt())
                == id) {
            return i;
        }
    }

    return -1;
}

void ObjectEditDialog::on_objectTypeComboBox_activated(int index)
{
    levelObjectEntry_.setObjectTypeID(
          static_cast<ObjectTypeIDs::ObjectTypeID>(
                ui->objectTypeComboBox->itemData(index).toInt()));
    // Reset spawn parameter to 1, which is always valid
    // and much easier to deal with than trying to get each
    // class to enforce validity
    levelObjectEntry_.setSpawnParameter(1);

    reloadDisplay();
}

void ObjectEditDialog::on_leftFacingButton_clicked(bool checked)
{
    levelObjectEntry_.setXDirectionFlag(LevelObjectEntry::left);
}

void ObjectEditDialog::on_rightFacingButton_clicked(bool checked)
{
    levelObjectEntry_.setXDirectionFlag(LevelObjectEntry::right);
}

void ObjectEditDialog::on_xPosSpinBox_valueChanged(int arg1)
{
    levelObjectEntry_.setXPos(arg1);
}

void ObjectEditDialog::on_yPosSpinBox_valueChanged(int arg1)
{
    levelObjectEntry_.setYPos(arg1);
}

void ObjectEditDialog::on_blinkingBox_clicked(bool checked)
{
    if (checked) {
        levelObjectEntry_.setBlinkingFlag(
                    LevelObjectEntry::blinking);
    }
    else {
        levelObjectEntry_.setBlinkingFlag(
                    LevelObjectEntry::notBlinking);
    }
}

void ObjectEditDialog::on_invisibilityBox_clicked(bool checked)
{
    if (checked) {
        levelObjectEntry_.setInvisibilityFlag(
                    LevelObjectEntry::invisible);
    }
    else {
        levelObjectEntry_.setInvisibilityFlag(
                    LevelObjectEntry::visible);
    }
}

void ObjectEditDialog::on_leftTileVRAMIndexBox_valueChanged(int arg1)
{
    levelObjectEntry_.setLeftTileVRAMIndex(arg1);
    refreshDisplay();
}

void ObjectEditDialog::on_rightTileVRAMIndexBox_valueChanged(int arg1)
{
    levelObjectEntry_.setRightTileVRAMIndex(arg1);
    refreshDisplay();
}
