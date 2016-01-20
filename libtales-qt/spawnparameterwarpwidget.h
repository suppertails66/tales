#ifndef SPAWNPARAMETERWARPWIDGET_H
#define SPAWNPARAMETERWARPWIDGET_H

#include <QWidget>
#include "structs/Tbyte.h"
#include "gamedata/LevelObjectEntry.h"
#include "editors/LevelObjectGraphicSceneLayer.h"

namespace Ui {
class SpawnParameterWarpWidget;
}

class SpawnParameterWarpWidget : public QWidget
{
    Q_OBJECT
    
public:
    friend class ObjectEditDialog;

    explicit SpawnParameterWarpWidget(QWidget *parent = 0);
    ~SpawnParameterWarpWidget();

    void setLevelObjectGraphicSceneLayer(
            Tales::LevelObjectGraphicSceneLayer& levelObjectGraphicSceneLayer__);

    void setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__);

    void loadValue(Tales::Tbyte value);

protected:
    Tales::LevelObjectGraphicSceneLayer* levelObjectGraphicSceneLayer_;

private slots:
    void on_warpSizeComboBox_activated(int index);

    void on_warpDestinationComboBox_activated(int index);

    void on_horizontalOrientationBox_clicked(bool checked);

    void on_verticalOrientationBox_clicked(bool checked);

protected:
    Tales::LevelObjectEntry* levelObjectEntry_;
    
private:
    Ui::SpawnParameterWarpWidget *ui;
};

#endif // SPAWNPARAMETERWARPWIDGET_H
