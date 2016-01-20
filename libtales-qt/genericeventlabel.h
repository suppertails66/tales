#ifndef GENERICEVENTLABEL_H
#define GENERICEVENTLABEL_H

#include <QLabel>
#include "structs/InputEventData.h"

class GenericEventLabel : public QLabel
{
    Q_OBJECT
public:
    explicit GenericEventLabel(QWidget *parent = 0);
    
protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

signals:
    
    void pickerEnter(QEvent* event);
    void pickerLeave(QEvent* event);
    void pickerMouseMove(QMouseEvent* event);
    void pickerMousePress(QMouseEvent* event);
    void pickerMouseRelease(QMouseEvent* event);
    void pickerMouseDoubleClick(QMouseEvent* event);

    void pickerEnter();
    void pickerLeave();
    void pickerMouseMove(Tales::InputEventData data);
    void pickerMousePress(Tales::InputEventData data);
    void pickerMouseRelease(Tales::InputEventData data);
    void pickerMouseDoubleClick(Tales::InputEventData data);

public slots:
    
};

#endif // GENERICEVENTLABEL_H
