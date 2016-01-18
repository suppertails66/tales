#include "editors/LengthMapLayeredGraphicScene.h"
#include "editors/LengthMapDrawer.h"
#include "gamedata/MetatileStructure.h"
#include "util/MiscMath.h"
#include <cstdlib>
#include <iostream>

using namespace Luncheon;

namespace Tales {


LengthMapLayeredGraphicScene::LengthMapLayeredGraphicScene()
  : scale_(16.0),
    lengthMap_(NULL),
    mapType_(mapTypeWidth),
    gridLayerEnabled_(true),
    gridLayer_(1,
               1,
               Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity),
               false),
    editDialogCallback_(NULL),
    editDialogCallbackParam_(NULL) {
//  gridLayer_.setXLimit(metatilesPerRow_
//                          * MetatileStructure::metatileWidth);
//  gridLayer_.setYLimit(metatilesPerColumn_
//                          * MetatileStructure::metatileHeight);
}
  
LengthMapLayeredGraphicScene::~LengthMapLayeredGraphicScene() { };
  
void LengthMapLayeredGraphicScene::render(Graphic& dst,
                    Box srcbox,
                    double scale) {
  if ((previewBuffer_.w() != srcbox.w())
      || (previewBuffer_.h() != srcbox.h())) {
    previewBuffer_ = Graphic(srcbox.w(), srcbox.h());
  }
  
  previewBuffer_.clear(Color(0xFF, 0xFF, 0xFF, Color::fullAlphaOpacity));
  
  switch (mapType_) {
  case mapTypeWidth:
    LengthMapDrawer::drawWidthMap(previewBuffer_,
                                  *lengthMap_);
    break;
  case mapTypeHeight:
    LengthMapDrawer::drawHeightMap(previewBuffer_,
                                   *lengthMap_);
    break;
  default:
    break;
  }
  
  int scaledWidth = srcbox.w() * scale;
  int scaledHeight = srcbox.h() * scale;
  
  previewBuffer_.scale(dst,
            Box(0, 0, scaledWidth, scaledHeight),
            Graphic::noTransUpdate);
  
  if (gridLayerEnabled_) {
    gridLayer_.render(dst,
                      srcbox,
                      scale);
  }
}

void LengthMapLayeredGraphicScene
    ::enterMouse() {
  
}

void LengthMapLayeredGraphicScene
    ::exitMouse() {
  
}

void LengthMapLayeredGraphicScene
    ::moveMouse(InputEventData eventData) {
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
/*  int x = eventData.x();
  int y = eventData.y();
  
  if (mapType_ == mapTypeWidth) {
    if (((int)(x) % MetatileStructure::metatileWidth)
          > (MetatileStructure::metatileWidth / 2)) {
      x = (int)((x / scale_) + 1) * scale_;
    }
  }
  else if (mapType_ == mapTypeHeight) {
    if (((int)(y) % MetatileStructure::metatileHeight)
          > (MetatileStructure::metatileHeight / 2)) {
      y = (int)((y / scale_) + 1) * scale_;
    }
  } */
  
//  alterMagnitude(x, y, true);
  alterMagnitude(eventData.x(), eventData.y());
}

void LengthMapLayeredGraphicScene
    ::pressMouse(InputEventData eventData) {
  if (eventData.mouseRightButton()) {
    doDialogEdit(eventData.x(), eventData.y());
    return;
  }
  
  alterMagnitude(eventData.x(),
                 eventData.y());
}

void LengthMapLayeredGraphicScene
    ::releaseMouse(InputEventData eventData) {
  
}

void LengthMapLayeredGraphicScene
    ::doubleClickMouse(InputEventData eventData) {
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
  doDialogEdit(eventData.x(), eventData.y());
}
  
void LengthMapLayeredGraphicScene
    ::doDialogEdit(int realX, int realY) {
  int localX = realCoordToLocal(realX);
  int localY = realCoordToLocal(realY);
  
  int index = 0;
  switch (mapType_) {
  case mapTypeWidth:
    index = localY;
    break;
  case mapTypeHeight:
    index = localX;
    break;
  default:
    break;
  }
  
  MiscMath::clamp(index, 0, MetatileLengthMap::numElements - 1);
  
  if (editDialogCallback_ != NULL) {
    LengthMapValue val = lengthMap_->lengthAt(index);
    if (editDialogCallback_(index,
                        &val,
                        editDialogCallbackParam_)) {
       lengthMap_->lengthAt(index) = val;
    }
  }
}

void LengthMapLayeredGraphicScene::setGridLayerEnabled(bool gridLayerEnabled__) {
  gridLayerEnabled_ = gridLayerEnabled__;
}
  
void LengthMapLayeredGraphicScene
    ::setLengthMap(MetatileLengthMap& lengthMap__,
                  MapType mapType__) {
  lengthMap_ = &lengthMap__;
  mapType_ = mapType__;
}
  
void LengthMapLayeredGraphicScene
    ::setEditDialogCallback(
    bool (*editDialogCallback__)(int, LengthMapValue*, void*),
    void* editDialogCallbackParam__) {
  editDialogCallback_ = editDialogCallback__;
  editDialogCallbackParam_ = editDialogCallbackParam__;
}
  
int LengthMapLayeredGraphicScene
    ::realCoordToLocal(int coord) {
  int localCoord = 0;
  if (coord < 0) {
    localCoord = (coord / scale_) - 1;
  }
  else {
    localCoord = (coord / scale_);
  }
  
  return localCoord;
}

void LengthMapLayeredGraphicScene
    ::alterMagnitude(int realX, int realY, bool preAltered) {
  int localX = realCoordToLocal(realX);
  int localY = realCoordToLocal(realY);
  
  // If coordinate is close enough to max, make it max;
  // otherwise, use the literal value
  
/*  if (realX > ((double)(MetatileStructure::metatileWidth * scale_)
               - (0.5 * scale_))) {
    localX = MetatileStructure::metatileWidth;
  }
  
  if (realY > ((double)(MetatileStructure::metatileHeight * scale_)
               - (0.5 * scale_))) {
    localY = MetatileStructure::metatileHeight;
  } */
  
//  std::cout << realX << " " << realY << std::endl;
//  std::cout << localX << " " << localY << std::endl;
    
  int index = 0;
  int mag = 0;
  switch (mapType_) {
  case mapTypeWidth:
    index = localY;
    mag = localX;
    break;
  case mapTypeHeight:
    index = localX;
    mag = localY;
    break;
  default:
    break;
  }
  
  MiscMath::clamp(index, 0, MetatileLengthMap::numElements - 1);
  
  switch (mapType_) {
  case mapTypeWidth:
    if (lengthMap_->lengthAt(index).direction()
          == LengthMapValue::forward) {
      mag = LengthMapValue::maxRegularMagnitude - mag;
      
      if (realX >= (MetatileStructure::metatileWidth * scale_)
                     - (scale_ * 0.4)) {
//        --mag;
        mag = 0;
      }
//      if ((realX % (int)(scale_)) >= ((int)(scale_) / 4)) {
//        --mag;
//      }
    }
    else {
      if (!preAltered) {
        ++mag;
      }
      
      if (realX < scale_ * 0.4) {
//        --mag;
        mag = 0;
      }

//      if ((realX % (int)(scale_)) < ((int)(scale_) / 4)) {
//        --mag;
//      }
    }
    break;
  case mapTypeHeight:
    if (lengthMap_->lengthAt(index).direction()
          == LengthMapValue::backward) {
      mag = LengthMapValue::maxRegularMagnitude - mag;
      
      if (realY >= (MetatileStructure::metatileHeight * scale_)
                     - (scale_ * 0.4)) {
//        --mag;
        mag = 0;
      }
      
//      if ((realY % (int)(scale_)) >= ((int)(scale_) / 4)) {
//        --mag;
//      }
    }
    else {
      if (!preAltered) {
        ++mag;
      }
      
      if (realY < scale_ * 0.4) {
//        --mag;
        mag = 0;
      }

//      if ((realY % (int)(scale_)) < ((int)(scale_) / 4)) {
//        --mag;
//      }
    }
    break;
  default:
    break;
  }
  
  MiscMath::clamp(mag, 0, LengthMapValue::maxRegularMagnitude);
  
//  std::cout << index << " " << mag << std::endl;
  
  lengthMap_->lengthAt(index).setMagnitude(mag);
  
//  std::cout << lengthMap_->lengthAt(index).magnitude() << std::endl;
}
    
void LengthMapLayeredGraphicScene
    ::setCurrentMetatileToForward() {
  for (int i = 0; i < MetatileLengthMap::numElements; i++) {
    lengthMap_->lengthAt(i).setDirection(LengthMapValue::forward);
  }
}

void LengthMapLayeredGraphicScene
    ::setCurrentMetatileToBackward() {
  for (int i = 0; i < MetatileLengthMap::numElements; i++) {
    lengthMap_->lengthAt(i).setDirection(LengthMapValue::backward);
  }
}


};
