#include "structs/InputEventData.h"

 namespace Tales {
 
 
InputEventData::InputEventData()
  : x_(0),
    y_(0),
    mouseLeftButton_(false),
    mouseRightButton_(false),
    mouseMiddleButton_(false),
    control_(false),
    alt_(false),
    shift_(false) { };

int InputEventData::x() {
  return x_;
}

void InputEventData::setX(int x__) {
  x_ = x__;
}

int InputEventData::y() {
  return y_;
}

void InputEventData::setY(int y__) {
  y_ = y__;
}

bool InputEventData::mouseLeftButton() {
  return mouseLeftButton_;
}

void InputEventData::setMouseLeftButton(bool mouseLeftButton__) {
  mouseLeftButton_ = mouseLeftButton__;
}

bool InputEventData::mouseRightButton() {
  return mouseRightButton_;
}

void InputEventData::setMouseRightButton(bool mouseRightButton__) {
  mouseRightButton_ = mouseRightButton__;
}

bool InputEventData::mouseMiddleButton() {
  return mouseMiddleButton_;
}

void InputEventData::setMouseMiddleButton(bool mouseMiddleButton__) {
  mouseMiddleButton_ = mouseMiddleButton__;
}
  
bool InputEventData::control() {
  return control_;
}

void InputEventData::setControl(bool control__) {
  control_ = control__;
}

bool InputEventData::alt() {
  return alt_;
}

void InputEventData::setAlt(bool alt__) {
  alt_ = alt__;
}

bool InputEventData::shift() {
  return shift_;
}

void InputEventData::setShift(bool shift__) {
  shift_ = shift__;
}


};
