#include "metatilepickerlabel.h"
#include "talesqtstatevar.h"
#include "createinputeventdata.h"
#include "structs/InputEventData.h"

using namespace Tales;

MetatilePickerLabel::MetatilePickerLabel(QWidget *parent) :
    QLabel(parent),
    realParent_((TalesQtLevelEditorWidget*)(parent))
{
}

void MetatilePickerLabel::enterEvent(QEvent* event) {
    appState_.editor().levelEditor().metatilePickerEnterMouse();
    realParent_->refreshMetatilePickerDisplay();
}

void MetatilePickerLabel::leaveEvent(QEvent* event) {
    appState_.editor().levelEditor().metatilePickerExitMouse();
    realParent_->refreshMetatilePickerDisplay();
}

void MetatilePickerLabel::mouseMoveEvent(QMouseEvent* event) {
    InputEventData data
            = CreateInputEventData::create(event);

    appState_.editor().levelEditor().metatilePickerMoveMouse(
                event->x(), event->y(), data);

    realParent_->refreshMetatilePickerDisplay();
}

void MetatilePickerLabel::mousePressEvent(QMouseEvent* event) {
    InputEventData data
            = CreateInputEventData::create(event);

    appState_.editor().levelEditor().metatilePickerPressMouse(
                event->x(), event->y(), data);

    realParent_->refreshDisplay();
}
