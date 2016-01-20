#ifndef OBJECTLISTEDITORWIDGET_H
#define OBJECTLISTEDITORWIDGET_H

#include <QListWidget>
#include "gamedata/LevelObjectEntryGroup.h"
#include "editors/LevelEditorToolManager.h"

class ObjectListEditorWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ObjectListEditorWidget(QWidget *parent = 0);
    
    void assignGroup(Tales::LevelObjectEntryGroup* group__,
                     Tales::LevelEditorToolManager& toolManager__);

    void repopulate();

    void updateObjectSelection();

    bool hasGroup() const;

    Tales::LevelObjectEntryCollection::iterator
        findCurrentItemIt();

protected:
    Tales::LevelObjectEntryGroup* group_;
    Tales::LevelEditorToolManager* toolManager_;

signals:
    
public slots:
    
};

#endif // OBJECTLISTEDITORWIDGET_H
