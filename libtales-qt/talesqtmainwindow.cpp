#include "ui_talesqtmainwindow.h"
#include "talesqtmainwindow.h"
#include "talesqtstatevar.h"
#include "genericerrordialog.h"
#include "aboutdialog.h"
#include "graphicsexportdialog.h"
#include "exception/NotEnoughSpaceException.h"
#include "util/StringConversion.h"
#include <QFileDialog>

using namespace Tales;
using namespace Luncheon;

TalesQtMainWindow::TalesQtMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TalesQtMainWindow)
{
    ui->setupUi(this);

    // Give statevar pointer to main window for future manipulations
    appState_.setMainWindow(this);

    changeMode(TalesQtEditorModes::levelEditor);
}

MainEditorWidgets& TalesQtMainWindow::mainEditorWidgets() {
    return *(ui->editorWidgets);
}

TalesQtMainWindow::~TalesQtMainWindow()
{
    delete ui;
}

void TalesQtMainWindow
    ::changeMode(TalesQtEditorModes::TalesQtEditorMode mode) {

    ui->selectorBar->changeMode(mode);

    ui->actionLevel_Editor->setChecked(false);
    ui->actionVRAM_Editor->setChecked(false);
    ui->actionMetatile_Behavior->setChecked(false);
    ui->actionLength_map_editor->setChecked(false);
    ui->actionPalette_editor->setChecked(false);
    ui->actionMetatile_structure_editor->setChecked(false);
    ui->actionGraphics_mappings_editor->setChecked(false);
    ui->actionPower_up_editor->setChecked(false);
    ui->actionMusic_editor->setChecked(false);
    ui->actionPalette_cycle_editor->setChecked(false);
    ui->actionHacks_and_enhancements->setChecked(false);
    ui->actionTilemap_editor->setChecked(false);

    switch (mode) {
    case TalesQtEditorModes::levelEditor:
        ui->actionLevel_Editor->setChecked(true);
        break;
    case TalesQtEditorModes::vramEditor:
        ui->actionVRAM_Editor->setChecked(true);
        break;
    case TalesQtEditorModes::metatileBehaviorEditor:
        ui->actionMetatile_Behavior->setChecked(true);
        break;
    case TalesQtEditorModes::lengthMapsEditor:
        ui->actionLength_map_editor->setChecked(true);
        break;
    case TalesQtEditorModes::paletteEditor:
        ui->actionPalette_editor->setChecked(true);
        break;
    case TalesQtEditorModes::metatileStructureEditor:
        ui->actionMetatile_structure_editor->setChecked(true);
        break;
    case TalesQtEditorModes::graphicsEditor:
        ui->actionGraphics_mappings_editor->setChecked(true);
        break;
    case TalesQtEditorModes::powerUpEditor:
        ui->actionPower_up_editor->setChecked(true);
        break;
    case TalesQtEditorModes::musicEditor:
        ui->actionMusic_editor->setChecked(true);
        break;
    case TalesQtEditorModes::paletteCycleEditor:
        ui->actionPalette_cycle_editor->setChecked(true);
        break;
    case TalesQtEditorModes::enhancementsEditor:
        ui->actionHacks_and_enhancements->setChecked(true);
        break;
    case TalesQtEditorModes::tileMapEditor:
        ui->actionTilemap_editor->setChecked(true);
        break;
    default:
        break;
    }
}

void TalesQtMainWindow::on_actionExport_ROM_triggered()
{
//    QString selectedFilter("ROM files (*.gg)");
    QString filename;
    while (true) {
        filename = QFileDialog::getSaveFileName(
                    this, tr("Export to ROM"),
                    "",
                    tr("ROM files (*.gg)"));

        if (filename.size() == 0) {
            return;
        }

        if (appState_.configFile().valueOfKey(
                    "Global", "SourceRomPath").compare(
                        filename.toStdString().c_str())
                == 0) {
            GenericErrorDialog dialog(
                        "Error: The selected file is the source ROM for the program "
                        "and cannot be overwritten. Use a different name instead.");
            dialog.exec();
        }
        else {
            break;
        }
    }

    try {
    appState_.editor().exportToFile(filename.toStdString());
    appState_.editor().metadata().setExportFileLocation(
                filename.toStdString());
    }
    catch (Tales::NotEnoughSpaceException& e) {
        GenericErrorDialog dialog(
                    std::string("Error: The exported data is too large to fit in the ROM. "
                    "Please free up space by deleting objects, simplifying "
                    "graphics and level layouts, and otherwise reducing space "
                    "usage.\n\n"
                    "If you think this is a bug, please report it!\n\n"
                    "Source: ")
                    + e.nameOfSourceFile()
                    + ",\n"
                    + e.source()
                    + ", line "
                    + StringConversion::toString(e.lineNum()));
        dialog.exec();
    }
}

void TalesQtMainWindow::on_actionSave_project_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
                this, tr("Save project data"),
                "",
                tr("Project files (*.tls)"));

    if (filename.size() == 0) {
        return;
    }

    appState_.editor().saveToFile(filename.toStdString());
    appState_.setLastLoadedFileName(filename.toStdString());
}

void TalesQtMainWindow::on_actionLoad_project_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Load project data"),
                "",
                tr("Project files (*.tls)"));

    if (filename.size() == 0) {
        return;
    }

    appState_.editor().loadFromFile(filename.toStdString());
    appState_.setLastLoadedFileName(filename.toStdString());
    appState_.reload();
}

void TalesQtMainWindow::on_actionSave_project_triggered()
{
    if (appState_.lastLoadedFileName().empty()) {
        on_actionSave_project_as_triggered();
        return;
    }
    else {
        appState_.editor().saveToFile(appState_.lastLoadedFileName());
    }
}

void TalesQtMainWindow::on_actionExport_ROM_2_triggered()
{
    if (appState_.editor().metadata().exportFileLocation().empty()) {
        on_actionExport_ROM_triggered();
        return;
    }
    else {
        appState_.editor().exportToFile(
                    appState_.editor().metadata().exportFileLocation());
    }
}

void TalesQtMainWindow::on_actionLevel_Editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::levelEditor);
}

void TalesQtMainWindow::on_actionVRAM_Editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::vramEditor);
}

void TalesQtMainWindow::on_actionMetatile_Behavior_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::metatileBehaviorEditor);
}

void TalesQtMainWindow::on_actionLength_map_editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::lengthMapsEditor);
}

void TalesQtMainWindow::on_actionPalette_editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::paletteEditor);
}

void TalesQtMainWindow::on_actionMetatile_structure_editor_triggered(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::metatileStructureEditor);
}

void TalesQtMainWindow::on_actionGraphics_mappings_editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::graphicsEditor);
}

void TalesQtMainWindow::on_actionPower_up_editor_triggered(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::powerUpEditor);
}

void TalesQtMainWindow::on_actionMusic_editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::musicEditor);
}

void TalesQtMainWindow::on_actionPalette_cycle_editor_triggered()
{
    appState_.changeEditor(TalesQtEditorModes::paletteCycleEditor);
}

void TalesQtMainWindow::on_actionHacks_and_enhancements_triggered(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::enhancementsEditor);
}

void TalesQtMainWindow::on_actionAbout_triggered(bool checked)
{
    AboutDialog(appState_.editor().versionNum(),
                this).exec();
}

void TalesQtMainWindow::on_actionTilemap_editor_triggered(bool checked)
{
    appState_.changeEditor(TalesQtEditorModes::tileMapEditor);
}

void TalesQtMainWindow::on_actionExport_other_triggered(bool checked)
{
    GraphicsExportDialog(this).exec();
}
