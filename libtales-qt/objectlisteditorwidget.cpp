#include "objectlisteditorwidget.h"
#include "gamedata/ObjectTypeID.h"
#include "gamedata/ObjectStates.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

ObjectListEditorWidget::ObjectListEditorWidget(QWidget *parent) :
    QListWidget(parent),
    group_(0)
{
}

void ObjectListEditorWidget::assignGroup(LevelObjectEntryGroup* group__,
        Tales::LevelEditorToolManager& toolManager__) {
    group_ = group__;
    toolManager_ = &toolManager__;
    repopulate();
}

void ObjectListEditorWidget::repopulate() {
    clear();

    if (group_ == 0) {
        return;
    }

    int num = 0;
    for (LevelObjectEntryCollection::iterator it = group_->begin();
         it != group_->end();
         ++it) {
        LevelObjectEntry entry = *it;
        std::string name;
        name += StringConversion::toString(
                    num);
        name += ": ";
        name += ObjectTypeIDs::nameOfObject(
                    entry.objectTypeID());
        ObjectStateInfo info = ObjectStates::findObjectStateInfo(
                    entry.objectTypeID(),
                    entry.spawnParameter());
        if (info.stateNum != -1) {
            name += " (";
            name += std::string(info.stateName);
            name += ")";
        }
        addItem(QString(name.c_str()));

        ++num;
    }
}

void ObjectListEditorWidget::updateObjectSelection() {
    int num = 0;
    for (LevelObjectEntryCollection::iterator it = group_->begin();
         it != group_->end();
         ++it) {
        if (it == toolManager_->objectEditorSingleGroupIt()) {
            setCurrentRow(num);
            return;
        }

        ++num;
    }
}

bool ObjectListEditorWidget::hasGroup() const {
    return (group_ != 0);
}

Tales::LevelObjectEntryCollection::iterator
    ObjectListEditorWidget::findCurrentItemIt() {
    if (group_ == 0) {
//        return;
    }

    LevelObjectEntryCollection::iterator it = group_->begin();
    for (int i = 0; i < currentRow(); i++) {
        ++it;
    }
    return it;
}
