#include "vramgraphiclist.h"
#include "util/StringConversion.h"
#include "editors/GraphicToInfo.h"
#include "talesqtstatevar.h"
#include <QListWidgetItem>
#include <iostream>

using namespace Tales;
using namespace Luncheon;

VRAMGraphicList::VRAMGraphicList(QWidget *parent) :
    QListWidget(parent)
{
}

void VRAMGraphicList::repopulate(Tales::ObjectGraphicsHeader& header) {
    // Clear existing content
    clear();

    for (int i = 0; i < header.size(); i++) {
        ObjectGraphicSubheader& subheader = header.subheader(i);

        int index = subheader.objectGraphicIndex();

        ObjectGraphicSubheader::SubstitutionOption flipFlag
                = subheader.substitutionOption();

        bool flipEnabled = false;

        if (flipFlag == ObjectGraphicSubheader::substitutionEnabled) {
            flipEnabled = true;
        }

        QListWidgetItem* item = new QListWidgetItem(
                    QString(nameOfItem(i,
                               index,
                               flipEnabled).c_str()), this);
        addItem(item);
    }
}

std::string VRAMGraphicList::nameOfItem(int itemNum,
                       int graphicID,
                       bool flipEnabled) {
    std::string name;
    name += StringConversion::toString(itemNum);
    name += ": ";
    name += GraphicToInfo::nameOfCompressedGraphic(graphicID);
    if (flipEnabled) {
        name += " (flipped)";
    }

    return name;
}
