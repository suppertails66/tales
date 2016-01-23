#ifndef TALESQTMAINWINDOW_H
#define TALESQTMAINWINDOW_H

#include <QMainWindow>
#include "maineditorwidgets.h"
#include "talesqteditormodes.h"

namespace Ui {
class TalesQtMainWindow;
}

class TalesQtMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TalesQtMainWindow(QWidget *parent = 0);
    ~TalesQtMainWindow();

    MainEditorWidgets& mainEditorWidgets();

    void changeMode(TalesQtEditorModes::TalesQtEditorMode mode);
    
private slots:
    void on_actionExport_ROM_triggered();

    void on_actionSave_project_as_triggered();

    void on_actionLoad_project_triggered();

    void on_actionSave_project_triggered();

    void on_actionExport_ROM_2_triggered();

    void on_actionLevel_Editor_triggered();

    void on_actionVRAM_Editor_triggered();

    void on_actionMetatile_Behavior_triggered();

    void on_actionLength_map_editor_triggered();

    void on_actionPalette_editor_triggered();

    void on_actionMetatile_structure_editor_triggered(bool checked);

    void on_actionGraphics_mappings_editor_triggered();

    void on_actionPower_up_editor_triggered(bool checked);

    void on_actionMusic_editor_triggered();

    void on_actionPalette_cycle_editor_triggered();

    void on_actionHacks_and_enhancements_triggered(bool checked);

    void on_actionAbout_triggered(bool checked);

    void on_actionTilemap_editor_triggered(bool checked);

private:
    Ui::TalesQtMainWindow *ui;
};

#endif // TALESQTMAINWINDOW_H
