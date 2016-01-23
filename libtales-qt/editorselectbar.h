#ifndef EDITORSELECTBAR_H
#define EDITORSELECTBAR_H

#include <QWidget>
#include "talesqteditormodes.h"

namespace Ui {
class EditorSelectBar;
}

class EditorSelectBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditorSelectBar(QWidget *parent = 0);
    ~EditorSelectBar();

    void changeMode(TalesQtEditorModes::TalesQtEditorMode mode);

protected:

    void raiseAllButtons();
    
private slots:
    void on_levelEditorButton_clicked();

    void on_vramButton_clicked();

    void on_metatileBehaviorButton_clicked(bool checked);

    void on_lengthMapsButton_clicked(bool checked);

    void on_paletteButton_clicked(bool checked);

    void on_metatileStructureButton_clicked(bool checked);

    void on_graphicsButton_clicked(bool checked);

    void on_powerUpButton_clicked(bool checked);

    void on_musicButton_clicked(bool checked);

    void on_paletteCycleButton_clicked(bool checked);

    void on_enhancementsButton_clicked(bool checked);

    void on_tileMapButton_clicked(bool checked);

private:
    Ui::EditorSelectBar *ui;
};

#endif // EDITORSELECTBAR_H
