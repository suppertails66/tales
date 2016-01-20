#include "editors/MetatilePickerSceneBase.h"
#include "gamedata/MetatileStructure.h"

namespace Tales {


MetatilePickerSceneBase::MetatilePickerSceneBase()
  : highlightedMetatileBoxEnabled_(false),
    highlightedMetatileIndex_(0),
    pickedMetatileBoxEnabled_(true),
    pickedMetatileIndex_(0),
    gridLayerEnabled_(true),
//    highlightedMetatileBoxEnabled_(false),
//    highlightedMetatileIndex_(0),
    gridLayer_(16,
               1,
               Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity),
               false) {
  gridLayer_.setXLimit(metatilesPerRow_
                          * MetatileStructure::metatileWidth);
  gridLayer_.setYLimit(metatilesPerColumn_
                          * MetatileStructure::metatileHeight);
}
  
MetatilePickerSceneBase::~MetatilePickerSceneBase() { };

void MetatilePickerSceneBase::enterMouse() {
//  highlightedMetatileBoxEnabled_ = true;
}

void MetatilePickerSceneBase::exitMouse() {
//  highlightedMetatileBoxEnabled_ = false;
}

void MetatilePickerSceneBase
    ::moveMouse(int x, int y, InputEventData eventData) {
  
}

void MetatilePickerSceneBase
    ::pressMouse(int x, int y, InputEventData eventData) {
  
}

void MetatilePickerSceneBase
    ::releaseMouse(int x, int y, InputEventData eventData) {
  
}

void MetatilePickerSceneBase
    ::doubleClickMouse(int x, int y, InputEventData eventData) {
  
}

int MetatilePickerSceneBase
    ::metatileIndexToX(int index) const {
  return (index % metatilesPerRow_)
    * MetatileStructure::metatileWidth;
}

int MetatilePickerSceneBase
    ::metatileIndexToY(int index) const {
  return (index / metatilesPerRow_)
    * MetatileStructure::metatileHeight;
}

int MetatilePickerSceneBase
    ::coordinateToMetatileIndex(int x, int y) const {
  return ((y / MetatileStructure::metatileHeight) * metatilesPerRow_)
            + (x / MetatileStructure::metatileWidth);
}
  
void MetatilePickerSceneBase
    ::setGridLayerEnabled(bool gridLayerEnabled__) {
  gridLayerEnabled_ = gridLayerEnabled__;
}


};
