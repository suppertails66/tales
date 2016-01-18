#ifndef SPAWNPARAMETERENEMYMINEWIDGET_H
#define SPAWNPARAMETERENEMYMINEWIDGET_H

#include <QWidget>
#include "structs/Tbyte.h"
#include "gamedata/LevelObjectEntry.h"

namespace Ui {
class SpawnParameterEnemyMineWidget;
}

class SpawnParameterEnemyMineWidget : public QWidget
{
    Q_OBJECT
    
public:
    friend class ObjectEditDialog;

    explicit SpawnParameterEnemyMineWidget(QWidget *parent = 0);
    ~SpawnParameterEnemyMineWidget();

    void setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__);

    void loadValue(Tales::Tbyte value);

protected:
    Tales::LevelObjectEntry* levelObjectEntry_;
    
private slots:
    void on_passiveMineButton_clicked(bool checked);

    void on_droppedMineButton_clicked(bool checked);

    void on_mineDropperButton_clicked(bool checked);

    void on_orientationComboBox_activated(int index);

    void on_metatileCoverageSpinBox_valueChanged(int arg1);

private:
    Ui::SpawnParameterEnemyMineWidget *ui;
};

#endif // SPAWNPARAMETERENEMYMINEWIDGET_H
