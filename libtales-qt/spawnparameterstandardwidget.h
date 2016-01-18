#ifndef SPAWNPARAMETERSTANDARDWIDGET_H
#define SPAWNPARAMETERSTANDARDWIDGET_H

#include <QWidget>
#include "structs/Tbyte.h"
#include "gamedata/LevelObjectEntry.h"

namespace Ui {
class SpawnParameterStandardWidget;
}

class SpawnParameterStandardWidget : public QWidget
{
    Q_OBJECT
    
public:
    friend class ObjectEditDialog;

    explicit SpawnParameterStandardWidget(QWidget *parent = 0);
    ~SpawnParameterStandardWidget();

    void setLevelObjectEntry(Tales::LevelObjectEntry& levelObjectEntry__);

    void loadValue(Tales::Tbyte value);

protected:
    Tales::LevelObjectEntry* levelObjectEntry_;
    
private slots:
    void on_initialStateBox_activated(int index);

private:
    Ui::SpawnParameterStandardWidget *ui;
};

#endif // SPAWNPARAMETERSTANDARDWIDGET_H
