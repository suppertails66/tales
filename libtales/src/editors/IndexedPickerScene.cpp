#include "editors/IndexedPickerScene.h"
#include "util/MiscMath.h"

using namespace Luncheon;

namespace Tales {


IndexedPickerScene::IndexedPickerScene(int totalSelectables__,
                                       int selectablesPerRow__,
                                       int selectableWidth__,
                                       int selectableHeight__)
  : totalSelectables_(totalSelectables__),
    selectablesPerRow_(selectablesPerRow__),
    selectableWidth_(selectableWidth__),
    selectableHeight_(selectableHeight__),
    sceneScale_(1.00),
    highlightedSelectableBoxEnabled_(false),
    highlightedSelectableIndex_(0),
    pickedSelectableBoxEnabled_(true),
    pickedSelectableIndex_(0),
    gridLayerEnabled_(true),
    gridLayer_(selectableWidth_,
               1,
               Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity),
               false) { };
  
IndexedPickerScene::~IndexedPickerScene() { };
  
void IndexedPickerScene::render(Graphic& dst,
                          Box srcbox,
                          double scale) {
  if ((nativeBuffer_.w() != srcbox.w())
      || (nativeBuffer_.h() != srcbox.h())) {
    nativeBuffer_ = Graphic(srcbox.w(), srcbox.h());
  }
                          
  renderNative(nativeBuffer_,
               srcbox);
  
  int scaledW = srcbox.w() * sceneScale_;
  int scaledH = srcbox.h() * sceneScale_;
  
  nativeBuffer_.scale(dst,
                       Box(0, 0,
                           scaledW,
                           scaledH));
      
  if (gridLayerEnabled_) {
    gridLayer_.render(dst,
                      Box(srcbox.x(),
                          srcbox.y(),
                          scaledW,
                          scaledH),
                      sceneScale_);
  }
  
  if ((highlightedSelectableBoxEnabled_)) {
    dst.drawRectBorder(selectableIndexToDrawX(highlightedSelectableIndex_),
                       selectableIndexToDrawY(highlightedSelectableIndex_),
                       selectableWidth_ * sceneScale_,
                       selectableHeight_ * sceneScale_,
                       Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                       2);
  }
  
  if ((pickedSelectableBoxEnabled_)) {
    dst.drawRectBorder(selectableIndexToDrawX(pickedSelectableIndex_),
                       selectableIndexToDrawY(pickedSelectableIndex_),
                       selectableWidth_ * sceneScale_,
                       selectableHeight_ * sceneScale_,
                       Color(0xFF, 0xFF, 0x00, Color::fullAlphaOpacity),
                       2);
  }
}
  
void IndexedPickerScene::enterMouse() {
  highlightedSelectableBoxEnabled_ = true;
}

void IndexedPickerScene::exitMouse() {
  highlightedSelectableBoxEnabled_ = false;
}

void IndexedPickerScene::moveMouse(InputEventData eventData) {
  highlightedSelectableBoxEnabled_ = true;
  highlightedSelectableIndex_ = drawPosToSelectableIndex(
                                  eventData.x(), eventData.y());
}

void IndexedPickerScene::pressMouse(InputEventData eventData) {
  if (!eventData.mouseLeftButton()) {
    return;
  }
  
  pickedSelectableBoxEnabled_ = true;
  pickedSelectableIndex_ = drawPosToSelectableIndex(
                                  eventData.x(), eventData.y());
}

void IndexedPickerScene::releaseMouse(InputEventData eventData) {
  
}

void IndexedPickerScene::doubleClickMouse(InputEventData eventData) {
  
}
  
int IndexedPickerScene::highlightedIndex() {
  return highlightedSelectableIndex_;
}

int IndexedPickerScene::pickedIndex() {
  return pickedSelectableIndex_;
}
  
void IndexedPickerScene::clearHighlightedBox() {
  highlightedSelectableBoxEnabled_ = false;
}

void IndexedPickerScene::clearPickedBox() {
  pickedSelectableBoxEnabled_ = false;
}
  
void IndexedPickerScene::pickIndex(int index) {
  pickedSelectableBoxEnabled_ = true;
  pickedSelectableIndex_ = index;
}

void IndexedPickerScene::highlightIndex(int index) {
  highlightedSelectableBoxEnabled_ = true;
  highlightedSelectableIndex_ = index;
}
  
bool IndexedPickerScene::gridLayerEnabled() const {
  return gridLayerEnabled_;
}
 
void IndexedPickerScene::setGridLayerEnabled(bool gridLayerEnabled__) {
  gridLayerEnabled_ = gridLayerEnabled__;
}

int IndexedPickerScene::selectablesPerColumn() const {
  return (totalSelectables_ / selectablesPerRow_);
}
  
double IndexedPickerScene::sceneScale() {
  return sceneScale_;
}

void IndexedPickerScene::setSceneScale(double sceneScale__) {
  sceneScale_ = sceneScale__;
}
  
int IndexedPickerScene::realPosToSelectableIndex(int realX, int realY) {
  return ((realY / selectableHeight_) * selectablesPerRow_)
            + (realX / selectableWidth_);
}

int IndexedPickerScene::drawPosToSelectableIndex(int drawX, int drawY) {
  return realPosToSelectableIndex(drawX / sceneScale_,
                                  drawY / sceneScale_);
}

int IndexedPickerScene::selectableIndexToDrawX(int index) {
  return selectableIndexToNativeDrawX(index) * sceneScale_;
}

int IndexedPickerScene::selectableIndexToDrawY(int index) {
  return selectableIndexToNativeDrawY(index) * sceneScale_;
}

int IndexedPickerScene::selectableIndexToNativeDrawX(int index) {
  return (index % selectablesPerRow_) * selectableWidth_;
}

int IndexedPickerScene::selectableIndexToNativeDrawY(int index) {
  return (index / selectablesPerRow_) * selectableHeight_;
}



};
