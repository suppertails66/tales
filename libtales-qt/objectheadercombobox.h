#ifndef OBJECTHEADERCOMBOBOX_H
#define OBJECTHEADERCOMBOBOX_H

#include <QComboBox>
#include "gamedata/EditableLevelGraphicsData.h"

class ObjectHeaderComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ObjectHeaderComboBox(QWidget *parent = 0);

    void repopulate(Tales::EditableLevelGraphicsData& src);
    
signals:
    
public slots:
    
};

#endif // OBJECTHEADERCOMBOBOX_H
