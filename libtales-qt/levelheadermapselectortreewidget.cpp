#include "levelheadermapselectortreewidget.h"
#include "gamedata/AreaMapReference.h"

using namespace Tales;

LevelHeaderMapSelectorTreeWidget::LevelHeaderMapSelectorTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}

void LevelHeaderMapSelectorTreeWidget::repopulate(
                Tales::LevelHeaders& levelHeaders,
                int numAreas,
                const int subMapCounts[],
                Tales::AreaMetadataMap& areaMetadata) {
    // Remove existing items
    clear();

    // Add top-level items


/*    for (int i = 0; i < levelHeaders.size(); i++) {
        AreaMapReference mapnums = levelHeaders.areaMapNumOfIndex(i);


    } */

    for (int i = 0; i < numAreas; i++) {
        if (subMapCounts[i] <= 0) {
            continue;
        }

        QTreeWidgetItem* parentItem = new QTreeWidgetItem(this);
        parentItem->setText(0,
                            (std::string("Area ") + StringConversion::toString(i)
                             + " (" + areaMetadata[i].name() + ")").c_str());
        parentItem->setData(0, Qt::UserRole, QVariant(i + TwoKeyedData<int>::primaryKeyBase));
        // Expand by default
        parentItem->setExpanded(true);

        for (int j = 0; j < subMapCounts[i]; j++) {
            QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
            int itemIndex = levelHeaders.levelHeaderIndex(
                        i + TwoKeyedData<int>::primaryKeyBase,
                        j + TwoKeyedData<int>::subKeyBase);
            item->setText(0,
                          (std::string("Map ")
                            + StringConversion::toString(j
                                        + TwoKeyedData<int>::subKeyBase)/*
                           + " (" + StringConversion::toString(itemIndex)
                           + ")"*/).c_str());
            item->setData(0, Qt::UserRole, QVariant(
                              itemIndex));

            parentItem->addChild(item);
        }
    }

    // Add special-case maps
    AreaMapReference worldMapDupeNums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::worldMapDupeHeaderIndex);
    AreaMapReference introDupeNums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::introDupeHeaderIndex);
    AreaMapReference lakeRocky1Nums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::lakeRocky1HeaderIndex);
    AreaMapReference lakeRockyBossNums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::lakeRockyBossHeaderIndex);
    AreaMapReference lakeRocky2Nums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::lakeRocky2HeaderIndex);
    AreaMapReference pollyMt1BossNums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::pollyMt1BossHeaderIndex);
    AreaMapReference cavernIslandBossNums
            = levelHeaders.areaMapNumOfIndex(LevelHeaders::cavernIslandBossHeaderIndex);

    addSpecialMap(worldMapDupeNums,
                  LevelHeaders::worldMapDupeHeaderIndex);
    addSpecialMap(introDupeNums,
                  LevelHeaders::introDupeHeaderIndex);
    addSpecialMap(lakeRocky1Nums,
                  LevelHeaders::lakeRocky1HeaderIndex);
    addSpecialMap(lakeRockyBossNums,
                  LevelHeaders::lakeRockyBossHeaderIndex);
    addSpecialMap(lakeRocky2Nums,
                  LevelHeaders::lakeRocky2HeaderIndex);
    addSpecialMap(pollyMt1BossNums,
                  LevelHeaders::pollyMt1BossHeaderIndex);
    addSpecialMap(cavernIslandBossNums,
                  LevelHeaders::cavernIslandBossHeaderIndex);
}

void LevelHeaderMapSelectorTreeWidget::addSpecialMap(
                   Tales::AreaMapReference ref,
                   int indexNum) {
    for (int i = 0; i < topLevelItemCount(); i++) {
        QTreeWidgetItem* item = topLevelItem(i);

        if (item->data(0, Qt::UserRole) == ref.areaNum()) {
            QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
/*            newItem->setText(0, QString((std::string("Special (")
                                + StringConversion::toString(indexNum) + ")")
                                        .c_str())); */
            newItem->setText(0, QString((std::string("Special (")
                                         + StringConversion::toString(ref.areaNum())
                                         + "-"
                                         + StringConversion::toString(ref.mapNum())
                                         + " alt)")
                                        .c_str()));
            newItem->setData(0, Qt::UserRole, QVariant(indexNum));
            item->addChild(newItem);
        }
    }
}
