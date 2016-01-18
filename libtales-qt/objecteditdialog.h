#ifndef OBJECTEDITDIALOG_H
#define OBJECTEDITDIALOG_H

#include <QDialog>
#include "gamedata/ObjectGraphicsHeader.h"
#include "gamedata/LevelObjectEntry.h"
#include "editors/LevelObjectGraphicSceneLayer.h"
#include "gamedata/ObjectTypeID.h"

namespace Ui {
class ObjectEditDialog;
}

class ObjectEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    ObjectEditDialog(Tales::LevelObjectGraphicSceneLayer&
                        levelObjectGraphicSceneLayer__,
//                     const Tales::ObjectGraphicsHeader& objectGraphicsHeader__,
                     Tales::LevelObjectEntry& levelObjectEntry__,
                     QWidget *parent = 0);
    ~ObjectEditDialog();

    void reloadDisplay();

    void refreshDisplay();

    Tales::LevelObjectEntry levelObjectEntry();

protected:

    Tales::LevelObjectGraphicSceneLayer& levelObjectGraphicSceneLayer_;
//    const Tales::ObjectGraphicsHeader& objectGraphicsHeader_;
    Tales::LevelObjectEntry& levelObjectEntry_;

    int findIndexOfObjectID(Tales::ObjectTypeIDs::ObjectTypeID id);
    
private slots:
    void onSpawnChange();

    void on_vramAutofillButton_clicked();

    void on_objectTypeComboBox_activated(int index);

    void on_leftFacingButton_clicked(bool checked);

    void on_rightFacingButton_clicked(bool checked);

    void on_xPosSpinBox_valueChanged(int arg1);

    void on_yPosSpinBox_valueChanged(int arg1);

    void on_blinkingBox_clicked(bool checked);

    void on_invisibilityBox_clicked(bool checked);

    void on_leftTileVRAMIndexBox_valueChanged(int arg1);

    void on_rightTileVRAMIndexBox_valueChanged(int arg1);

private:
    Ui::ObjectEditDialog *ui;
};

#endif // OBJECTEDITDIALOG_H
