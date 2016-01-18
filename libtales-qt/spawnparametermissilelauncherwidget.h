#ifndef SPAWNPARAMETERMISSILELAUNCHERWIDGET_H
#define SPAWNPARAMETERMISSILELAUNCHERWIDGET_H

#include <QWidget>
#include "structs/Tbyte.h"
#include "gamedata/LevelObjectEntry.h"

namespace Ui {
class SpawnParameterMissileLauncherWidget;
}

class SpawnParameterMissileLauncherWidget : public QWidget
{
    Q_OBJECT
    
public:
    friend class ObjectEditDialog;

    explicit SpawnParameterMissileLauncherWidget(QWidget *parent = 0);
    ~SpawnParameterMissileLauncherWidget();

    void setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__);

    void loadValue(Tales::Tbyte value);

protected:
    Tales::LevelObjectEntry* levelObjectEntry_;
    
private slots:
    void on_orientationComboBox_activated(int index);

    void on_metatileCoverageSpinBox_valueChanged(int arg1);

    void on_facingLeftButton_clicked(bool checked);

    void on_facingRightButton_clicked(bool checked);

private:
    Ui::SpawnParameterMissileLauncherWidget *ui;
};

#endif // SPAWNPARAMETERMISSILELAUNCHERWIDGET_H
