#ifndef VRAMGRAPHICLIST_H
#define VRAMGRAPHICLIST_H

#include <QListWidget>
#include "gamedata/ObjectGraphicsHeader.h"

class VRAMGraphicList : public QListWidget
{
    Q_OBJECT
public:
    explicit VRAMGraphicList(QWidget *parent = 0);
    
    void repopulate(Tales::ObjectGraphicsHeader& header);

protected:

    std::string nameOfItem(int itemNum,
                           int graphicID,
                           bool flipEnabled);

signals:
    
public slots:
    
};

#endif // VRAMGRAPHICLIST_H
