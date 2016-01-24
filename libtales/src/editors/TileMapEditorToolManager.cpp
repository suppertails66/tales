#include "editors/TileMapEditorToolManager.h"
#include <cstdlib>

namespace Tales {


TileMapEditorToolManager::TileMapEditorToolManager()
  : currentTool_(TileMapEditorTools::pencil),
    pencilDrawIndex_(0),
    pencilHFlip_(false),
    pencilVFlip_(false),
    areaCloneState_(TileMapEditorTools::areaCloneWaitingForSelect),
    areaCloneBaseX_(0),
    areaCloneBaseY_(0),
    areaCloneW_(0),
    areaCloneH_(0),
    areaCloneBuffer_(NULL) { };
  
TileMapEditorToolManager::~TileMapEditorToolManager() {
  clearAreaCloneBuffer();
}
  
TileMapEditorTools::TileMapEditorTool TileMapEditorToolManager
    ::currentTool() const {
  return currentTool_;
}

void TileMapEditorToolManager
    ::changeTool(TileMapEditorTools::TileMapEditorTool tool) {
  resetTools();
  
  currentTool_ = tool;
}
  
void TileMapEditorToolManager
    ::resetTools() {
//  pencilDrawIndex_ = 0;
  pencilHFlip_ = false;
  pencilVFlip_ = false;
  clearAreaCloneBuffer();
  areaCloneState_ = TileMapEditorTools::areaCloneWaitingForSelect;
}
  
int TileMapEditorToolManager
    ::pencilDrawIndex() const {
  return pencilDrawIndex_;
}
  
bool TileMapEditorToolManager
    ::pencilHFlip() const {
  return pencilHFlip_;
}
  
bool TileMapEditorToolManager
    ::pencilVFlip() const {
  return pencilVFlip_;
}

void TileMapEditorToolManager
    ::setPencilDrawIndex(int pencilDrawIndex__) {
  pencilDrawIndex_ = pencilDrawIndex__;
}

void TileMapEditorToolManager
    ::setPencilHFlip(bool pencilHFlip__) {
  pencilHFlip_ = pencilHFlip__;
}

void TileMapEditorToolManager
    ::setPencilVFlip(bool pencilVFlip__) {
  pencilVFlip_ = pencilVFlip__;
}

void TileMapEditorToolManager
    ::flipPencilH() {
  if (pencilHFlip_) {
    pencilHFlip_ = false;
  }
  else {
    pencilHFlip_ = true;
  }
}
    
void TileMapEditorToolManager
    ::flipPencilV() {
  if (pencilVFlip_) {
    pencilVFlip_ = false;
  }
  else {
    pencilVFlip_ = true;
  }
}
  
void TileMapEditorToolManager
    ::finalizeCloneArea(TileMap& tileMap) {
  clearAreaCloneBuffer();
  
  // Make rectangle positive
      
  if (areaCloneW_ < 0) {
    areaCloneBaseX_ += areaCloneW_;
    areaCloneW_ = (-areaCloneW_ + 1);
  }
  
  if (areaCloneH_ < 0) {
    areaCloneBaseY_ += areaCloneH_;
    areaCloneH_ = (-areaCloneH_ + 1);
  }
  
  // Crop upper-left
  
  if (areaCloneBaseX_ < 0) {
    areaCloneW_ += areaCloneBaseX_;
    areaCloneBaseX_ = 0;
  }
  
  if (areaCloneBaseY_ < 0) {
    areaCloneH_ += areaCloneBaseY_;
    areaCloneBaseY_ = 0;
  }
  
  // Crop lower-right
  
  if (areaCloneBaseX_ + areaCloneW_ >= tileMap.w()) {
    areaCloneW_ = tileMap.w() - areaCloneBaseX_;
  }
  
  if (areaCloneBaseY_ + areaCloneH_ >= tileMap.h()) {
    areaCloneH_ = tileMap.h() - areaCloneBaseY_;
  }
  
  // Make sure there's something to copy
  
  if ((areaCloneW_ <= 0) || (areaCloneH_ <= 0)) {
    areaCloneState_ = TileMapEditorTools::areaCloneWaitingForSelect;
    return;
  }
  
  reinitializeAreaCloneBuffer(areaCloneW_, areaCloneH_);
  
  for (int j = 0; j < areaCloneH_; j++) {
    for (int i = 0; i < areaCloneW_; i++) {
      areaCloneBuffer_[i][j]
        = tileMap.tileData(areaCloneBaseX_ + i,
                           areaCloneBaseY_ + j);
    }
  }
  
  areaCloneState_ = TileMapEditorTools::areaCloneCloning;
}
  
TileReference TileMapEditorToolManager
    ::areaCloneBuffer(int x, int y) {
  return areaCloneBuffer_[x][y];
}
  
TileMapEditorTools::AreaCloneState TileMapEditorToolManager
    ::areaCloneState() const {
  return areaCloneState_;
}

int TileMapEditorToolManager
    ::areaCloneBaseX() const {
  return areaCloneBaseX_;
}

int TileMapEditorToolManager
    ::areaCloneBaseY() const {
  return areaCloneBaseY_;
}

int TileMapEditorToolManager
    ::areaCloneW() const {
  return areaCloneW_;
}

int TileMapEditorToolManager
    ::areaCloneH() const {
  return areaCloneH_;
}
  
void TileMapEditorToolManager
    ::setAreaCloneState(
    TileMapEditorTools::AreaCloneState areaCloneState__) {
  areaCloneState_ = areaCloneState__;
}

void TileMapEditorToolManager
    ::setAreaCloneBaseX(
    int areaCloneBaseX__) {
  clearAreaCloneBuffer();
  areaCloneBaseX_ = areaCloneBaseX__;
}

void TileMapEditorToolManager
    ::setAreaCloneBaseY(
    int areaCloneBaseY__) {
  clearAreaCloneBuffer();
  areaCloneBaseY_ = areaCloneBaseY__;
}

void TileMapEditorToolManager
    ::setAreaCloneW(
    int areaCloneW__) {
  clearAreaCloneBuffer();
  areaCloneW_ = areaCloneW__;
}

void TileMapEditorToolManager
    ::setAreaCloneH(
    int areaCloneH__) {
  clearAreaCloneBuffer();
  areaCloneH_ = areaCloneH__;
}

void TileMapEditorToolManager
    ::clearAreaCloneBuffer() {
  if (areaCloneBuffer_ == NULL) {
    return;
  }
  
  for (int i = 0; i < areaCloneW_; i++) {
    delete[] areaCloneBuffer_[i];
  }
  
  delete[] areaCloneBuffer_;
  
  areaCloneBuffer_ = NULL;
}

void TileMapEditorToolManager
    ::reinitializeAreaCloneBuffer(int w, int h) {
  if ((w == 0) || (h == 0)) {
    areaCloneBuffer_ = NULL;
    return;
  }
  
  clearAreaCloneBuffer();
  
  areaCloneBuffer_ = new TileReference*[w];
  for (int i = 0; i < w; i++) {
    areaCloneBuffer_[i] = new TileReference[h];
  }
}


};
