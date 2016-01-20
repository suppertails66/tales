#include "editors/ColorPickerGraphicSceneLayer.h"
#include "util/MiscMath.h"
#include <cstdlib>
#include <iostream>

using namespace Luncheon;

namespace Tales {


ColorPickerGraphicSceneLayer::ColorPickerGraphicSceneLayer()
  : previewBuffer_(previewWidth_, previewHeight_),
    scale_(1.00),
    pickedIndexBoxEnabled_(false),
    pickedIndex_(0),
    highlightedIndexBoxEnabled_(false),
    highlightedIndex_(0),
    colorPickedCallback_(NULL),
    colorPickedCallbackParam_(NULL) {
  enableAllColors();
}
  
void ColorPickerGraphicSceneLayer::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  previewBuffer_.clear(Color(255, 255, 255, Color::fullAlphaOpacity));
  
  for (int i = 0; i < numColors_; i++) {
    int targetX = colorIndexToLocalX(i);
    int targetY = colorIndexToLocalY(i);
  
    if (!(enabledColors_[i])) {
      previewBuffer_.drawLine(targetX, targetY,
                             targetX + widthOfColor_,
                             targetY + heightOfColor_,
                             Color(255, 0, 0, Color::fullAlphaOpacity),
                             1);
      previewBuffer_.drawLine(targetX + widthOfColor_, targetY,
                             targetX,
                             targetY + heightOfColor_,
                             Color(255, 0, 0, Color::fullAlphaOpacity),
                             1);
      continue;
    }
    
    previewBuffer_.fillRect(targetX, targetY,
                            widthOfColor_, heightOfColor_,
                            Color(palette[i].realR(),
                                  palette[i].realG(),
                                  palette[i].realB(),
                                  Color::fullAlphaOpacity));
  }
  
  previewBuffer_.scale(dst);
  
  if (highlightedIndexBoxEnabled_) {
    int targetX = colorIndexToLocalX(highlightedIndex_) * scale_;
    int targetY = colorIndexToLocalY(highlightedIndex_) * scale_;
    
    dst.drawRectBorder(targetX, targetY,
                                  widthOfColor_ * scale_,
                                  heightOfColor_ * scale_,
                                  Color(255, 255, 0, Color::fullAlphaOpacity),
                                  3);
  }
  
  if (pickedIndexBoxEnabled_) {
    int targetX = colorIndexToLocalX(pickedIndex_) * scale_;
    int targetY = colorIndexToLocalY(pickedIndex_) * scale_;
    
    dst.drawRectBorder(targetX, targetY,
                                  widthOfColor_ * scale_,
                                  heightOfColor_ * scale_,
                                  Color(255, 0, 0, Color::fullAlphaOpacity),
                                  3);
  }
}

void ColorPickerGraphicSceneLayer::setColorPickedCallback(
    void (*colorPickedCallback__)(int,void*),
    void* colorPickedCallbackParam__) {
  colorPickedCallback_ = colorPickedCallback__;
  colorPickedCallbackParam_ = colorPickedCallbackParam__;
}
  
int ColorPickerGraphicSceneLayer::previewWidth() {
  return previewWidth_ * scale_;
}

int ColorPickerGraphicSceneLayer::previewHeight() {
  return previewHeight_ * scale_;
}
  
void ColorPickerGraphicSceneLayer::setPalette(GGPalette palette__) {
  palette = palette__;
}

void ColorPickerGraphicSceneLayer::setColorInPalette(GGColor color,
                       int index) {
  palette[index] = color;
}
  
void ColorPickerGraphicSceneLayer::enterMouse() {
  highlightedIndexBoxEnabled_ = true;
}

void ColorPickerGraphicSceneLayer::exitMouse() {
  highlightedIndexBoxEnabled_ = false;
}

void ColorPickerGraphicSceneLayer::moveMouse(InputEventData eventData) {
  highlightedIndexBoxEnabled_ = true;
  highlightedIndex_ = realCoordinateToColorIndex(eventData.x(), eventData.y());
}

void ColorPickerGraphicSceneLayer::pressMouse(InputEventData eventData) {
  if (!eventData.mouseLeftButton()) {
    return;
  }
  
  int targetIndex = realCoordinateToColorIndex(eventData.x(), eventData.y());
  
  if (!colorEnabled(targetIndex)) {
    return;
  }
  
  pickedIndexBoxEnabled_ = true;
  pickedIndex_ = targetIndex;
  
  if (colorPickedCallback_ != NULL) {
    colorPickedCallback_(pickedIndex_, colorPickedCallbackParam_);
  }
}

void ColorPickerGraphicSceneLayer::releaseMouse(InputEventData eventData) {
  
}

void ColorPickerGraphicSceneLayer::doubleClickMouse(InputEventData eventData) {
  
}

int ColorPickerGraphicSceneLayer::pickedIndex() {
  return pickedIndex_;
}

void ColorPickerGraphicSceneLayer::setPickedIndex(int index) {
  pickedIndex_ = index;
}
  
void ColorPickerGraphicSceneLayer
    ::setPickedIndexBoxEnabled(bool pickedIndexBoxEnabled__) {
  pickedIndexBoxEnabled_ = pickedIndexBoxEnabled__;
}
  
void ColorPickerGraphicSceneLayer::disableAllColors() {
  for (int i = 0; i < numColors_; i++) {
    enabledColors_[i] = false;
  }
}

void ColorPickerGraphicSceneLayer::enableAllColors() {
  for (int i = 0; i < numColors_; i++) {
    enabledColors_[i] = true;
  }
}
  
bool ColorPickerGraphicSceneLayer
    ::colorEnabled(int index) {
  return enabledColors_[index];
}

void ColorPickerGraphicSceneLayer
    ::setColorEnabled(int index, bool enabled) {
  enabledColors_[index] = enabled;
}

int ColorPickerGraphicSceneLayer
    ::colorIndexToLocalX(int index) const {
  return (index % colorsPerRow_)
    * widthOfColor_;
}

int ColorPickerGraphicSceneLayer
    ::colorIndexToLocalY(int index) const {
  return (index / colorsPerRow_)
    * heightOfColor_;
}

int ColorPickerGraphicSceneLayer
    ::realCoordinateToColorIndex(int x, int y) const {
//  int result = ((y / scale_ / heightOfColor_) * colorsPerRow_)
//            + (x / scale_ / widthOfColor_);
  int result = (x / scale_ / widthOfColor_);
  MiscMath::clamp(result, 0, numColors_ - 1);
  return result;
}
  
double ColorPickerGraphicSceneLayer
    ::scale() {
  return scale_;
}

void ColorPickerGraphicSceneLayer
    ::setScale(double scale__) {
  scale_ = scale__;
}


};
