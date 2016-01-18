#include "leveleditorpreviewlabel.h"
#include "talesqtstatevar.h"
#include "talesqtleveleditorwidget.h"
#include <iostream>

using namespace Tales;

LevelEditorPreviewLabel::LevelEditorPreviewLabel(QWidget *parent) :
    QLabel(parent),
    parentEditor_(*(dynamic_cast<TalesQtLevelEditorWidget*>(parent)))
{
}

void LevelEditorPreviewLabel::resizeEvent(QResizeEvent* event) {
    parentEditor_.refreshDisplay();
//    std::cout << event->oldSize().width() << " " << event->oldSize().height() << std::endl;
}

void LevelEditorPreviewLabel::enterEvent(QEvent* event) {
    appState_.editor().levelEditor().levelEditorEnterMouse();
    parentEditor_.refreshLevelEditorDisplay();
}

void LevelEditorPreviewLabel::leaveEvent(QEvent* event) {
    appState_.editor().levelEditor().levelEditorExitMouse();
    parentEditor_.refreshLevelEditorDisplay();
}

void LevelEditorPreviewLabel::mouseMoveEvent(QMouseEvent* event) {
    InputEventData data;
    data.setMouseLeftButton(event->buttons() & Qt::LeftButton);
    data.setMouseMiddleButton(event->buttons() & Qt::MiddleButton);
    data.setMouseRightButton(event->buttons() & Qt::RightButton);
    data.setControl(event->modifiers() & Qt::ControlModifier);
    data.setAlt(event->modifiers() & Qt::AltModifier);
    data.setShift(event->modifiers() & Qt::ShiftModifier);

    appState_.editor().levelEditor().levelEditorMoveMouse(
                event->x(), event->y(), data);

    parentEditor_.refreshDisplay();
}

void LevelEditorPreviewLabel::mouseDoubleClickEvent(QMouseEvent* event) {
    InputEventData data;
    data.setMouseLeftButton(event->buttons() & Qt::LeftButton);
    data.setMouseMiddleButton(event->buttons() & Qt::MiddleButton);
    data.setMouseRightButton(event->buttons() & Qt::RightButton);
    data.setControl(event->modifiers() & Qt::ControlModifier);
    data.setAlt(event->modifiers() & Qt::AltModifier);
    data.setShift(event->modifiers() & Qt::ShiftModifier);

    appState_.editor().levelEditor().levelEditorDoubleClickMouse(
                event->x(), event->y(), data);

    parentEditor_.refreshDisplay();
}

void LevelEditorPreviewLabel::mousePressEvent(QMouseEvent* event) {
    InputEventData data;
    data.setMouseLeftButton(event->buttons() & Qt::LeftButton);
    data.setMouseMiddleButton(event->buttons() & Qt::MiddleButton);
    data.setMouseRightButton(event->buttons() & Qt::RightButton);
    data.setControl(event->modifiers() & Qt::ControlModifier);
    data.setAlt(event->modifiers() & Qt::AltModifier);
    data.setShift(event->modifiers() & Qt::ShiftModifier);

    appState_.editor().levelEditor().levelEditorPressMouse(
                event->x(), event->y(), data);

    parentEditor_.refreshDisplay();
}

void LevelEditorPreviewLabel::mouseReleaseEvent(QMouseEvent* event) {
    InputEventData data;
    data.setMouseLeftButton(event->buttons() & Qt::LeftButton);
    data.setMouseMiddleButton(event->buttons() & Qt::MiddleButton);
    data.setMouseRightButton(event->buttons() & Qt::RightButton);
    data.setControl(event->modifiers() & Qt::ControlModifier);
    data.setAlt(event->modifiers() & Qt::AltModifier);
    data.setShift(event->modifiers() & Qt::ShiftModifier);

    appState_.editor().levelEditor().levelEditorReleaseMouse(
                event->x(), event->y(), data);

    parentEditor_.refreshDisplay();
}

void LevelEditorPreviewLabel::wheelEvent(QWheelEvent* event) {
    bool horizontal = (event->modifiers() & Qt::ShiftModifier);

    Qt::KeyboardModifiers realModifiers = event->modifiers();

    // Pretend shift isn't pressed (default implementation uses
    // this for page scrolling)
    if (event->modifiers() & Qt::ShiftModifier) {
        realModifiers ^= Qt::ShiftModifier;
//        event->setModifiers(event->modifiers() ^ Qt::ShiftModifier);
    }

    // use Alt to check for page scrolling instead
    if (event->modifiers() & Qt::ControlModifier) {
        realModifiers ^= Qt::ControlModifier;
        realModifiers |= Qt::ShiftModifier;
//        event->setModifiers(event->modifiers() | Qt::ShiftModifier);
    }

    QWheelEvent realEvent(event->pos(),
                            event->globalPos(),
                            event->delta(),
                            event->buttons(),
                            realModifiers,
                            event->orientation());

    // Horizontal scroll if shift pressed
    if (horizontal) {
        parentEditor_.levelHorizontalScrollBar().wheelEvent(&realEvent);
    }
    // Vertical scroll if not
    else {
        parentEditor_.levelVerticalScrollBar().wheelEvent(&realEvent);
    }

    parentEditor_.refreshLevelEditorDisplay();
}
