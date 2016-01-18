#ifndef MAPSELECTORTREEWIDGET_H
#define MAPSELECTORTREEWIDGET_H

#include <QTreeWidget>
#include "editors/EditorMetadata.h"

class MapSelectorTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit MapSelectorTreeWidget(QWidget *parent = 0);

    void repopulate(int numAreas,
                    const int subMapCounts[],
                    Tales::AreaMetadataMap& areaMetadata_);
    
signals:
    
public slots:
    
};

#endif // MAPSELECTORTREEWIDGET_H
