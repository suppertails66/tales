#include "editors/LevelEditorToolManager.h"
#include <cstdlib>
#include <iostream>

namespace Tales {


LevelEditorToolManager::LevelEditorToolManager()
  : currentTool_(LevelEditorTools::metatilePaint),
    pickedMetatileIndex_(0),
    metatileAreaCloneState_(LevelEditorTools::waitingForSelectionClick),
    metatileAreaCloneBaseX_(0),
    metatileAreaCloneBaseY_(0),
    metatileAreaCloneWidth_(0),
    metatileAreaCloneHeight_(0),
    metatileAreaCloneMetatileArray_(NULL),
    objectEditorState_(LevelEditorTools::objectEditorNothingSelected),
    objectEditorLastRealX_(0),
    objectEditorLastRealY_(0),
    spawnEditorState_(LevelEditorTools::spawnEditorNothingSelected),
    spawnEditorLastRealX_(0),
    spawnEditorLastRealY_(0) { };
  
LevelEditorToolManager::~LevelEditorToolManager() {
  delete metatileAreaCloneMetatileArray_;
}

LevelEditorTools::LevelEditorTool LevelEditorToolManager
    ::currentTool() const {
  return currentTool_;
}

void LevelEditorToolManager::setCurrentTool(LevelEditorTools::LevelEditorTool
    currentTool__) {
  currentTool_ = currentTool__;
  
  // Reset selected tool to default state
  switch (currentTool__) {
  case LevelEditorTools::metatileAreaClone:
    metatileAreaCloneState_ = LevelEditorTools::waitingForSelectionClick;
    break;
  case LevelEditorTools::objectEditor:
    objectEditorState_ = LevelEditorTools::objectEditorNothingSelected;
    break;
  default:
    break;
  }
  
  objectEditorState_ = LevelEditorTools::objectEditorNothingSelected;
}

void LevelEditorToolManager::setCurrentToolNoReset(
    LevelEditorTools::LevelEditorTool currentTool__) {
  currentTool_ = currentTool__;
}
  
int LevelEditorToolManager::pickedMetatileIndex() const {
  return pickedMetatileIndex_;
}

void LevelEditorToolManager
    ::setPickedMetatileIndex(int pickedMetatileIndex__) {
  pickedMetatileIndex_ = pickedMetatileIndex__;
}
  
LevelEditorTools::MetatileAreaCloneState LevelEditorToolManager
    ::metatileAreaCloneState() const {
  return metatileAreaCloneState_;
}

void LevelEditorToolManager::setMetatileAreaCloneState(
    LevelEditorTools::MetatileAreaCloneState metatileAreaCloneState__) {
  metatileAreaCloneState_ = metatileAreaCloneState__;
}
  
int LevelEditorToolManager::metatileAreaCloneBaseX() const {
  return metatileAreaCloneBaseX_;
}

void LevelEditorToolManager
    ::setMetatileAreaCloneBaseX(int metatileAreaCloneBaseX__) {
  metatileAreaCloneBaseX_ = metatileAreaCloneBaseX__;
}

int LevelEditorToolManager
    ::metatileAreaCloneBaseY() const {
  return metatileAreaCloneBaseY_;
}

void LevelEditorToolManager
    ::setMetatileAreaCloneBaseY(int metatileAreaCloneBaseY__) {
  metatileAreaCloneBaseY_ = metatileAreaCloneBaseY__;
}

int LevelEditorToolManager
    ::metatileAreaCloneWidth() const {
  return metatileAreaCloneWidth_;
}

void LevelEditorToolManager
    ::setMetatileAreaCloneWidth(int metatileAreaCloneWidth__) {
  metatileAreaCloneWidth_ = metatileAreaCloneWidth__;
}

int LevelEditorToolManager
    ::metatileAreaCloneHeight() const {
  return metatileAreaCloneHeight_;
}

void LevelEditorToolManager
    ::setMetatileAreaCloneHeight(int metatileAreaCloneHeight__) {
  metatileAreaCloneHeight_ = metatileAreaCloneHeight__;
}

void LevelEditorToolManager
    ::finalizeMetatileAreaClone(const MapLayout& mapLayout,
                                int mapWidth) {
  // Make any negative dimensions positive
  
  if (metatileAreaCloneWidth_ < 0) {
    metatileAreaCloneBaseX_ += metatileAreaCloneWidth_;
    metatileAreaCloneWidth_ = -metatileAreaCloneWidth_;
                     
    // hacky fix to make negative positions work intuitively
    ++metatileAreaCloneWidth_;
  }
  
  if (metatileAreaCloneHeight_ < 0) {
    metatileAreaCloneBaseY_ += metatileAreaCloneHeight_;
    metatileAreaCloneHeight_ = -metatileAreaCloneHeight_;
                     
    // hacky fix to make negative positions work intuitively
    ++metatileAreaCloneHeight_;
  }
    
  int arraySize = metatileAreaCloneWidth_ * metatileAreaCloneHeight_;
  if (arraySize <= 0) {
    return;
  }
  
  delete metatileAreaCloneMetatileArray_;
  metatileAreaCloneMetatileArray_
    = new Tbyte[metatileAreaCloneWidth_ * metatileAreaCloneHeight_];
    
  for (int j = 0; j < metatileAreaCloneHeight_; j++) {
    for (int i = 0; i < metatileAreaCloneWidth_; i++) {
      metatileAreaCloneMetatileArray_[(j * metatileAreaCloneWidth_)
                                        + i]
        = mapLayout.getMetatile(
            ((metatileAreaCloneBaseY_ + j) * mapWidth)
              + (metatileAreaCloneBaseX_ + i));
    }
  }
}

int LevelEditorToolManager
    ::metatileAreaCloneMetatile(int x, int y) {
  return (int)(metatileAreaCloneMetatileArray_[(y * metatileAreaCloneWidth_)
                                          + x]);
}
  
LevelEditorTools::ObjectEditorState LevelEditorToolManager
    ::objectEditorState() const {
  return objectEditorState_;
}

ObjectDisplayCacheCollection::iterator LevelEditorToolManager
    ::objectEditorSingleCacheIt() const {
  return objectEditorSingleCacheIt_;
}

LevelObjectEntryCollection::iterator LevelEditorToolManager
    ::objectEditorSingleGroupIt() const {
  return objectEditorSingleGroupIt_;
}

ObjectDisplayCacheCollectionIteratorCollection&
   LevelEditorToolManager
    ::objectEditorMultipleCacheIts() {
  return objectEditorMultipleCacheIts_;
}

LevelObjectEntryCollectionIteratorCollection&
   LevelEditorToolManager
    ::objectEditorMultipleGroupIts() {
  return objectEditorMultipleGroupIts_;
}

int LevelEditorToolManager
    ::objectEditorLastRealX() const {
  return objectEditorLastRealX_;
}

int LevelEditorToolManager
    ::objectEditorLastRealY() const {
  return objectEditorLastRealY_;
}

void LevelEditorToolManager
    ::setObjectEditorState(LevelEditorTools
                            ::ObjectEditorState objectEditorState__) {
  objectEditorState_ = objectEditorState__;
}

void LevelEditorToolManager
    ::setObjectEditorSingleCacheIt(ObjectDisplayCacheCollection::iterator
                                    objectEditorSingleCacheIt__) {
  objectEditorSingleCacheIt_ = objectEditorSingleCacheIt__;
}

void LevelEditorToolManager
    ::setObjectEditorSingleGroupIt(LevelObjectEntryCollection::iterator
                                    objectEditorSingleGroupIt__) {
  objectEditorSingleGroupIt_ = objectEditorSingleGroupIt__;
}

void LevelEditorToolManager
    ::setObjectEditorLastRealX(int objectEditorLastRealX__) {
  objectEditorLastRealX_ = objectEditorLastRealX__;
}

void LevelEditorToolManager
    ::setObjectEditorLastRealY(int objectEditorLastRealY__) {
  objectEditorLastRealY_ = objectEditorLastRealY__;
}

int LevelEditorToolManager
    ::objectEditorMultipleSelectX() {
  return objectEditorMultipleSelectX_;
}

void LevelEditorToolManager
    ::setObjectEditorMultipleSelectX(
    int objectEditorMultipleSelectX__) {
  objectEditorMultipleSelectX_ = objectEditorMultipleSelectX__;
}
    
int LevelEditorToolManager
    ::objectEditorMultipleSelectY() {
  return objectEditorMultipleSelectY_;
}

void LevelEditorToolManager
    ::setObjectEditorMultipleSelectY(
    int objectEditorMultipleSelectY__) {
  objectEditorMultipleSelectY_ = objectEditorMultipleSelectY__;
}
    
int LevelEditorToolManager
    ::objectEditorMultipleSelectW() {
  return objectEditorMultipleSelectW_;
}

void LevelEditorToolManager
    ::setObjectEditorMultipleSelectW(
    int objectEditorMultipleSelectW__) {
  objectEditorMultipleSelectW_ = objectEditorMultipleSelectW__;
}
    
int LevelEditorToolManager
    ::objectEditorMultipleSelectH() {
  return objectEditorMultipleSelectH_;
}

void LevelEditorToolManager
    ::setObjectEditorMultipleSelectH(
    int objectEditorMultipleSelectH__) {
  objectEditorMultipleSelectH_ = objectEditorMultipleSelectH__;
}

int LevelEditorToolManager
    ::objectEditorMultipleLastRealX() const {
  return objectEditorMultipleLastRealX_;
}

int LevelEditorToolManager
    ::objectEditorMultipleLastRealY() const {
  return objectEditorMultipleLastRealY_;
}

void LevelEditorToolManager
    ::setObjectEditorMultipleLastRealX(int objectEditorMultipleLastRealX__) {
  objectEditorMultipleLastRealX_ = objectEditorMultipleLastRealX__;
}

void LevelEditorToolManager
    ::setObjectEditorMultipleLastRealY(int objectEditorMultipleLastRealY__) {
  objectEditorMultipleLastRealY_ = objectEditorMultipleLastRealY__;
}
  
LevelEditorTools::SpawnEditorState LevelEditorToolManager
    ::spawnEditorState() {
  return spawnEditorState_;
}

ObjectDisplayCacheCollection::iterator LevelEditorToolManager
    ::spawnEditorSingleCacheIt() {
  return spawnEditorSingleCacheIt_;
}

SpawnPointCollection::iterator LevelEditorToolManager
    ::spawnEditorSingleGroupIt() {
  return spawnEditorSingleGroupIt_;
}

int LevelEditorToolManager
    ::spawnEditorLastRealX() {
  return spawnEditorLastRealX_;
}

int LevelEditorToolManager
    ::spawnEditorLastRealY() {
  return spawnEditorLastRealY_;
}

void LevelEditorToolManager
    ::setSpawnEditorState(LevelEditorTools
                            ::SpawnEditorState spawnEditorState__) {
  spawnEditorState_ = spawnEditorState__;
}
                            
void LevelEditorToolManager
    ::setSpawnEditorSingleCacheIt(ObjectDisplayCacheCollection::iterator
                                    spawnEditorSingleCacheIt__) {
  spawnEditorSingleCacheIt_ = spawnEditorSingleCacheIt__;
}
                                    
void LevelEditorToolManager
    ::setSpawnEditorSingleGroupIt(SpawnPointCollection::iterator
                                    spawnEditorSingleGroupIt__) {
  spawnEditorSingleGroupIt_ = spawnEditorSingleGroupIt__;
}
                                    
void LevelEditorToolManager
    ::setSpawnEditorLastRealX(int spawnEditorLastRealX__) {
  spawnEditorLastRealX_ = spawnEditorLastRealX__;
}

void LevelEditorToolManager
    ::setSpawnEditorLastRealY(int spawnEditorLastRealY__) {
  spawnEditorLastRealY_ = spawnEditorLastRealY__;
}


};
