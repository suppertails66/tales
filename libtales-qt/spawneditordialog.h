#ifndef SPAWNEDITORDIALOG_H
#define SPAWNEDITORDIALOG_H

#include <QDialog>
#include "gamedata/SpawnPoint.h"
#include "editors/LevelSpawnGraphicSceneLayer.h"

namespace Ui {
class SpawnEditorDialog;
}

class SpawnEditorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SpawnEditorDialog(Tales::LevelSpawnGraphicSceneLayer&
                                 levelSpawnGraphicSceneLayer__,
                               Tales::SpawnPoint& spawnPoint__,
                               QWidget *parent = 0);
    ~SpawnEditorDialog();

protected:
    void refreshDisplay();

    Tales::LevelSpawnGraphicSceneLayer& levelSpawnGraphicSceneLayer_;
    Tales::SpawnPoint& spawnPoint_;
    
private slots:
    void on_tailsXBox_valueChanged(int arg1);

    void on_tailsYBox_valueChanged(int arg1);

    void on_camXBox_valueChanged(int arg1);

    void on_camYBox_valueChanged(int arg1);

private:
    Ui::SpawnEditorDialog *ui;
};

#endif // SPAWNEDITORDIALOG_H
