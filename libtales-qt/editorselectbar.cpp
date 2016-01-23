#include "editorselectbar.h"
#include "ui_editorselectbar.h"
#include "talesqtstatevar.h"

EditorSelectBar::EditorSelectBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorSelectBar)
{
    ui->setupUi(this);

//    ui->levelEditorButton->setIcon(QIcon(QPixmap(":/resources/testimage.png")));

//    ui->levelEditorButton->setCheckable(true);
//    ui->vramButton->setCheckable(true);

    // default tool: level editor
//    ui->levelEditorButton->setChecked(true);
}

EditorSelectBar::~EditorSelectBar()
{
    delete ui;
}

void EditorSelectBar::raiseAllButtons() {
    ui->levelEditorButton->setChecked(false);
    ui->vramButton->setChecked(false);
    ui->metatileBehaviorButton->setChecked(false);
    ui->lengthMapsButton->setChecked(false);
    ui->paletteButton->setChecked(false);
    ui->metatileStructureButton->setChecked(false);
    ui->graphicsButton->setChecked(false);
    ui->powerUpButton->setChecked(false);
    ui->musicButton->setChecked(false);
    ui->paletteCycleButton->setChecked(false);
    ui->enhancementsButton->setChecked(false);
    ui->tileMapButton->setChecked(false);
}

void EditorSelectBar
        ::changeMode(TalesQtEditorModes::TalesQtEditorMode mode) {
    raiseAllButtons();

    switch (mode) {
    case TalesQtEditorModes::levelEditor:
        ui->levelEditorButton->setChecked(true);
        break;
    case TalesQtEditorModes::vramEditor:
        ui->vramButton->setChecked(true);
        break;
    case TalesQtEditorModes::metatileBehaviorEditor:
        ui->metatileBehaviorButton->setChecked(true);
        break;
    case TalesQtEditorModes::lengthMapsEditor:
        ui->lengthMapsButton->setChecked(true);
        break;
    case TalesQtEditorModes::paletteEditor:
        ui->paletteButton->setChecked(true);
        break;
    case TalesQtEditorModes::metatileStructureEditor:
        ui->metatileStructureButton->setChecked(true);
        break;
    case TalesQtEditorModes::graphicsEditor:
        ui->graphicsButton->setChecked(true);
        break;
    case TalesQtEditorModes::powerUpEditor:
        ui->powerUpButton->setChecked(true);
        break;
    case TalesQtEditorModes::musicEditor:
        ui->musicButton->setChecked(true);
        break;
    case TalesQtEditorModes::paletteCycleEditor:
        ui->paletteCycleButton->setChecked(true);
        break;
    case TalesQtEditorModes::enhancementsEditor:
        ui->enhancementsButton->setChecked(true);
        break;
    case TalesQtEditorModes::tileMapEditor:
        ui->tileMapButton->setChecked(true);
        break;
    default:
        break;
    }
}

void EditorSelectBar::on_levelEditorButton_clicked()
{
 //   changeMode(TalesQtEditorModes::levelEditor);
    appState_.changeEditor(TalesQtEditorModes::levelEditor);
}

void EditorSelectBar::on_vramButton_clicked()
{
//    changeMode(TalesQtEditorModes::vramEditor);
    appState_.changeEditor(TalesQtEditorModes::vramEditor);
}

void EditorSelectBar::on_metatileBehaviorButton_clicked(bool checked)
{
//    changeMode(TalesQtEditorModes::metatileBehaviorEditor);
    appState_.changeEditor(TalesQtEditorModes::metatileBehaviorEditor);
}

void EditorSelectBar::on_lengthMapsButton_clicked(bool checked)
{
//    changeMode(TalesQtEditorModes::lengthMapsEditor);
    appState_.changeEditor(TalesQtEditorModes::lengthMapsEditor);
}

void EditorSelectBar::on_paletteButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::paletteEditor);
}

void EditorSelectBar::on_metatileStructureButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::metatileStructureEditor);
}

void EditorSelectBar::on_graphicsButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::graphicsEditor);
}

void EditorSelectBar::on_powerUpButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::powerUpEditor);
}

void EditorSelectBar::on_musicButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::musicEditor);
}

void EditorSelectBar::on_paletteCycleButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::paletteCycleEditor);
}

void EditorSelectBar::on_enhancementsButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::enhancementsEditor);
}

void EditorSelectBar::on_tileMapButton_clicked(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::tileMapEditor);
}
