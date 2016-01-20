#ifndef LEVELHEADERMAPSELECTORTREEWIDGET_H
#define LEVELHEADERMAPSELECTORTREEWIDGET_H

#include <QTreeWidget>
#include "gamedata/LevelHeaders.h"
#include "editors/EditorMetadata.h"

class LevelHeaderMapSelectorTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit LevelHeaderMapSelectorTreeWidget(QWidget *parent = 0);

    void repopulate(Tales::LevelHeaders& levelHeaders,
                    int numAreas,
                    const int subMapCounts[],
                    Tales::AreaMetadataMap& areaMetadata);

    void addSpecialMap(Tales::AreaMapReference ref,
                       int indexNum);
    
signals:
    
public slots:
    
};

#endif // LEVELHEADERMAPSELECTORTREEWIDGET_H
