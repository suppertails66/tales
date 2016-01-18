#ifndef METATILEPICKERLABEL_H
#define METATILEPICKERLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "talesqtleveleditorwidget.h"

class MetatilePickerLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MetatilePickerLabel(QWidget *parent = 0);

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    TalesQtLevelEditorWidget* realParent_;
    
signals:
    
public slots:
    
};

#endif // METATILEPICKERLABEL_H
