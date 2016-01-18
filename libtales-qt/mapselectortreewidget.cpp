#include "mapselectortreewidget.h"
#include "util/StringConversion.h"
#include "structs/TwoKeyedData.h"
#include "editors/EditorMetadata.h"

using namespace Luncheon;
using namespace Tales;

MapSelectorTreeWidget::MapSelectorTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setHeaderHidden(true);
}

void MapSelectorTreeWidget::repopulate(int numAreas,
                const int subMapCounts[],
                Tales::AreaMetadataMap& areaMetadata_) {
    // Remove existing items
    clear();

    for (int i = 0; i < numAreas; i++) {
        if (subMapCounts[i] <= 0) {
            continue;
        }

        QTreeWidgetItem* parentItem = new QTreeWidgetItem(this);
        parentItem->setText(0,
                            (std::string("Area ") + StringConversion::toString(i)
                             + " (" + areaMetadata_[i].name() + ")").c_str());
        parentItem->setData(0, Qt::UserRole, QVariant(i + TwoKeyedData<int>::primaryKeyBase));
        // Expand by default
        parentItem->setExpanded(true);

        for (int j = 0; j < subMapCounts[i]; j++) {
            QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
            item->setText(0,
                          (std::string("Map ")
                            + StringConversion::toString(j
                                        + TwoKeyedData<int>::subKeyBase)).c_str());
            item->setData(0, Qt::UserRole, QVariant(j + TwoKeyedData<int>::subKeyBase));

            parentItem->addChild(item);
        }
    }
}
