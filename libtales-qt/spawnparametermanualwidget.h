#ifndef SPAWNPARAMETERMANUALWIDGET_H
#define SPAWNPARAMETERMANUALWIDGET_H

#include <QWidget>
#include "structs/Tbyte.h"
#include "gamedata/LevelObjectEntry.h"

namespace Ui {
class SpawnParameterManualWidget;
}

class SpawnParameterManualWidget : public QWidget
{
    Q_OBJECT
    
public:
    friend class ObjectEditDialog;

    explicit SpawnParameterManualWidget(QWidget *parent = 0);
    ~SpawnParameterManualWidget();

    void setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__);

    void loadValue(Tales::Tbyte value);
    
protected:
    Tales::LevelObjectEntry* levelObjectEntry_;

private slots:
    void on_parameterBox_valueChanged(int arg1);

private:
    Ui::SpawnParameterManualWidget *ui;
};

#endif // SPAWNPARAMETERMANUALWIDGET_H
