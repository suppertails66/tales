#include "levelpropertiesdialog.h"
#include "ui_levelpropertiesdialog.h"
#include "gamedata/SpecialEffect.h"
#include "editors/PaletteEditor.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

LevelPropertiesDialog::LevelPropertiesDialog(Tales::LevelEditor& levelEditor__,
                                             QWidget *parent) :
    QDialog(parent),
    levelEditor_(levelEditor__),
    ui(new Ui::LevelPropertiesDialog)
{
    ui->setupUi(this);

    ui->levelWidthBox->addItem("16 x 256", 16);
    ui->levelWidthBox->addItem("32 x 128", 32);
    ui->levelWidthBox->addItem("48 x 86", 48);
    ui->levelWidthBox->addItem("64 x 64", 64);
    ui->levelWidthBox->addItem("80 x 51", 80);
    ui->levelWidthBox->addItem("96 x 42", 96);
    ui->levelWidthBox->addItem("128 x 32", 128);
    ui->levelWidthBox->addItem("256 x 16", 256);

    for (int i = 0; i < SpecialEffects::specialEffectLimit; i++) {
        SpecialEffects::SpecialEffect effect
                = static_cast<SpecialEffects::SpecialEffect>(i);
        ui->levelEffect1Box->addItem(
                    SpecialEffects::nameOfEffect(effect).c_str(),
                    i);
        ui->levelEffect2Box->addItem(
                    SpecialEffects::nameOfEffect(effect).c_str(),
                    i);
        ui->levelEffect3Box->addItem(
                    SpecialEffects::nameOfEffect(effect).c_str(),
                    i);
        ui->levelEffect4Box->addItem(
                    SpecialEffects::nameOfEffect(effect).c_str(),
                    i);
    }

    for (int i = 0; i < levelEditor_.numMetatileStructureSets(); i++) {
        std::string nameString = StringConversion::toString(i);
        ui->metatileStructureSetComboBox->addItem(
                    nameString.c_str(), i);
    }

    for (int i = 0; i < levelEditor_.numPalettes(); i++) {
        std::string nameString = StringConversion::toString(i)
                + ": "
                + PaletteEditor::nameOfPalette(i);
        ui->palette0ComboBox->addItem(nameString.c_str(), i);
        ui->palette1ComboBox->addItem(nameString.c_str(), i);
    }

    reload();
}

LevelPropertiesDialog::~LevelPropertiesDialog()
{
    delete ui;
}

void LevelPropertiesDialog::reload() {
    int width = levelEditor_.currentLevelWidth();
    for (int i = 0; i < ui->levelWidthBox->count(); i++) {
        if (ui->levelWidthBox->itemData(i).toInt()
                == width) {
            ui->levelWidthBox->setCurrentIndex(i);
        }
    }

    LevelEffectsHeader& effects = levelEditor_.currentLevelEffectsHeader();

    ui->levelEffect1Box->setCurrentIndex(
                effects.effect(0));
    ui->levelEffect2Box->setCurrentIndex(
                effects.effect(1));
    ui->levelEffect3Box->setCurrentIndex(
                effects.effect(2));
    ui->levelEffect4Box->setCurrentIndex(
                effects.effect(3));

    ui->metatileStructureSetComboBox->setCurrentIndex(
                levelEditor_.currentLevelMetatileStructureIndex());

    ui->palette0ComboBox->setCurrentIndex(
                levelEditor_.currentLevelPaletteHeader()
                    .palette0Index());
    ui->palette1ComboBox->setCurrentIndex(
                levelEditor_.currentLevelPaletteHeader()
                    .palette1Index());
}

void LevelPropertiesDialog::on_levelWidthBox_activated(int index)
{
    levelEditor_.setCurrentLevelWidth(
                ui->levelWidthBox->itemData(index).toInt());
}

void LevelPropertiesDialog::on_levelEffect1Box_activated(int index)
{
    levelEditor_.currentLevelEffectsHeader().effect(0)
            = static_cast<SpecialEffects::SpecialEffect>(index);
}

void LevelPropertiesDialog::on_levelEffect2Box_activated(int index)
{
    levelEditor_.currentLevelEffectsHeader().effect(1)
            = static_cast<SpecialEffects::SpecialEffect>(index);
}

void LevelPropertiesDialog::on_levelEffect3Box_activated(int index)
{
    levelEditor_.currentLevelEffectsHeader().effect(2)
            = static_cast<SpecialEffects::SpecialEffect>(index);
}

void LevelPropertiesDialog::on_levelEffect4Box_activated(int index)
{
    levelEditor_.currentLevelEffectsHeader().effect(3)
            = static_cast<SpecialEffects::SpecialEffect>(index);
}

void LevelPropertiesDialog::on_palette0ComboBox_activated(int index)
{
    levelEditor_.currentLevelPaletteHeader()
                    .setPalette0Index(index);
}

void LevelPropertiesDialog::on_palette1ComboBox_activated(int index)
{
    levelEditor_.currentLevelPaletteHeader()
                    .setPalette1Index(index);
}

void LevelPropertiesDialog::on_metatileStructureSetComboBox_activated(int index)
{
    levelEditor_.setCurrentLevelMetatileStructureIndex(index);
}
