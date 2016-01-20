#include "genericeventlabel.h"
#include "createinputeventdata.h"

using namespace Tales;

GenericEventLabel::GenericEventLabel(QWidget *parent) :
    QLabel(parent)
{
}

void GenericEventLabel::enterEvent(QEvent* event) {
    emit pickerEnter(event);

    emit pickerEnter();
}

void GenericEventLabel::leaveEvent(QEvent* event) {
    emit pickerLeave(event);

    emit pickerLeave();
}

void GenericEventLabel::mouseMoveEvent(QMouseEvent* event) {
    emit pickerMouseMove(event);

    InputEventData data
            = CreateInputEventData::create(event);
    emit pickerMouseMove(data);
}

void GenericEventLabel::mousePressEvent(QMouseEvent* event) {
    emit pickerMousePress(event);

    InputEventData data
            = CreateInputEventData::create(event);
    emit pickerMousePress(data);
}

void GenericEventLabel::mouseReleaseEvent(QMouseEvent* event) {
    emit pickerMouseRelease(event);

    InputEventData data
            = CreateInputEventData::create(event);
    emit pickerMouseRelease(data);
}

void GenericEventLabel::mouseDoubleClickEvent(QMouseEvent* event) {
    emit pickerMouseDoubleClick(event);

    InputEventData data
            = CreateInputEventData::create(event);
    emit pickerMouseDoubleClick(data);
}

