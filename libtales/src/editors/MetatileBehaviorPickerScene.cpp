#include "editors/MetatileBehaviorPickerScene.h"
#include "editors/LevelEffectGraphicSceneLayer.h"
#include "editors/LengthMapDrawer.h"
#include <cstdlib>

namespace Tales {


MetatileBehaviorPickerScene::MetatileBehaviorPickerScene(
              EditableMetatileBehaviors&
                                metatileBehaviors__,
              EditableMetatileWidthMaps&
                metatileWidthMaps__,
              EditableMetatileHeightMaps&
                metatileHeightMaps__)
  : metatileBehaviors_(&metatileBehaviors__),
    metatileWidthMaps_(&metatileWidthMaps__),
    metatileHeightMaps_(&metatileHeightMaps__),
    effectLayerEnabled_(true),
    verticalSolidityLayerEnabled_(false),
    horizontalSolidityLayerEnabled_(false),
    metatilePickedCallback_(NULL),
    metatilePickedCallbackParam_(NULL) {
  reloadMetatileDisplay();
}
  
MetatileBehaviorPickerScene::~MetatileBehaviorPickerScene() { };
  
void MetatileBehaviorPickerScene::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  dst.clear();
  
  int metatileNum = 0;
  for (int j = 0; j < metatilesPerColumn_; j++) {
    for (int i = 0; i < metatilesPerRow_; i++) {
      if (effectLayerEnabled_) {
        dst.blit(metatilesEffect_[metatileNum],
                 Box(i * MetatileStructure::metatileWidth,
                     j * MetatileStructure::metatileHeight,
                     MetatileStructure::metatileWidth,
                     MetatileStructure::metatileHeight),
                 Graphic::noTransUpdate);
      }
      
      if (verticalSolidityLayerEnabled_) {
        dst.blit(metatilesVerticalSolidity_[metatileNum],
                 Box(i * MetatileStructure::metatileWidth,
                     j * MetatileStructure::metatileHeight,
                     MetatileStructure::metatileWidth,
                     MetatileStructure::metatileHeight),
                 Graphic::noTransUpdate);
      }
      
      if (horizontalSolidityLayerEnabled_) {
        dst.blit(metatilesHorizontalSolidity_[metatileNum],
                 Box(i * MetatileStructure::metatileWidth,
                     j * MetatileStructure::metatileHeight,
                     MetatileStructure::metatileWidth,
                     MetatileStructure::metatileHeight),
                 Graphic::noTransUpdate);
      }
      
      ++metatileNum;
    }
  }
      
  if (gridLayerEnabled_) {
    gridLayer_.render(dst,
                      Box(srcbox.x(),
                          srcbox.y(),
                          dst.w(),
                          dst.h()),
                      1.00);
  }
  
  if ((highlightedMetatileBoxEnabled_)) {
    dst.drawRectBorder(metatileIndexToX(highlightedMetatileIndex_),
                       metatileIndexToY(highlightedMetatileIndex_),
                       MetatileStructure::metatileWidth,
                       MetatileStructure::metatileHeight,
                       Color(0xFF, 0xFF, 0x00, Color::fullAlphaOpacity),
                       2);
  }
  
  if ((pickedMetatileBoxEnabled_)) {
    dst.drawRectBorder(metatileIndexToX(pickedMetatileIndex_),
                       metatileIndexToY(pickedMetatileIndex_),
                       MetatileStructure::metatileWidth,
                       MetatileStructure::metatileHeight,
                       Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                       2);
  }
  
/*  if ((toolManager_->currentTool() == LevelEditorTools::metatilePaint)) {
    dst.drawRectBorder(metatileIndexToX(toolManager_->pickedMetatileIndex()),
                       metatileIndexToY(toolManager_->pickedMetatileIndex()),
                       MetatileStructure::metatileWidth,
                       MetatileStructure::metatileHeight,
                       Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                       2);
  } */
}
  
void MetatileBehaviorPickerScene::setMetatilePickedCallback(
    void (*metatilePickedCallback__)(int, void*),
    void* metatilePickedCallbackParam__) {
  metatilePickedCallback_ = metatilePickedCallback__;
  metatilePickedCallbackParam_ = metatilePickedCallbackParam__;
}
    
void MetatileBehaviorPickerScene::setViewMode(ViewMode viewMode__) {
  effectLayerEnabled_ = false;
  verticalSolidityLayerEnabled_ = false;
  horizontalSolidityLayerEnabled_ = false;

  switch (viewMode__) {
  case viewEffect:
    effectLayerEnabled_ = true;
    break;
  case viewVerticalSolidity:
    verticalSolidityLayerEnabled_ = true;
    break;
  case viewHorizontalSolidity:
    horizontalSolidityLayerEnabled_ = true;
    break;
  default:
    break;
  }
}
  
Graphic& MetatileBehaviorPickerScene
    ::metatileEffectGraphic(int index) {
  return metatilesEffect_[index];
}

Graphic& MetatileBehaviorPickerScene
    ::metatileVerticalSolidityGraphic(int index) {
  return metatilesVerticalSolidity_[index];
}

Graphic& MetatileBehaviorPickerScene
    ::metatileHorizontalSolidityGraphic(int index) {
  return metatilesHorizontalSolidity_[index];
}

void MetatileBehaviorPickerScene::pickMetatile(int index) {
  pickedMetatileBoxEnabled_ = true;
  pickedMetatileIndex_ = index;
  
  if (metatilePickedCallback_ != NULL) {
    metatilePickedCallback_(pickedMetatileIndex_,
                            metatilePickedCallbackParam_);
  }
}

int MetatileBehaviorPickerScene::pickedMetatile() {
  return pickedMetatileIndex_;
}
  
void MetatileBehaviorPickerScene::reloadMetatileDisplay() {
  metatilesEffect_.clear();
  metatilesVerticalSolidity_.clear();
  metatilesHorizontalSolidity_.clear();

  for (int i = 0; i < numMetatiles_; i++) {
    Graphic metatileEffectGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    Graphic metatileVerticalSolidityGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    Graphic metatileHorizontalSolidityGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    
    LevelEffectGraphicSceneLayer
      ::drawMetatileEffect(metatileEffectGraphic,
                           i,
                           metatileBehaviors_->metatileBehavior(i));
    
    LengthMapDrawer::drawHeightMap(metatileVerticalSolidityGraphic,
                         metatileHeightMaps_->mapAt(
                           metatileBehaviors_->metatileBehavior(i)
                             .heightMapIndex()),
                         metatileBehaviors_->metatileBehavior(i));
  
    LengthMapDrawer::drawWidthMap(metatileHorizontalSolidityGraphic,
                         metatileWidthMaps_->mapAt(
                           metatileBehaviors_->metatileBehavior(i)
                             .widthMapIndex()),
                         metatileBehaviors_->metatileBehavior(i));
                           
    metatileEffectGraphic.regenerateTransparencyModel();
    metatileVerticalSolidityGraphic.regenerateTransparencyModel();
    metatileHorizontalSolidityGraphic.regenerateTransparencyModel();
    
    metatilesEffect_.push_back(metatileEffectGraphic);
    metatilesVerticalSolidity_.push_back(
        metatileVerticalSolidityGraphic);
    metatilesHorizontalSolidity_.push_back(
        metatileHorizontalSolidityGraphic);
  }
}

void MetatileBehaviorPickerScene::enterMouse() {
  highlightedMetatileBoxEnabled_ = true;
}

void MetatileBehaviorPickerScene::exitMouse() {
  highlightedMetatileBoxEnabled_ = false;
}

/*void MetatileBehaviorPickerScene
    ::setEffectLayerEnabled(bool effectLayerEnabled__) {
  effectLayerEnabled_ = effectLayerEnabled__;
} */

void MetatileBehaviorPickerScene
    ::moveMouse(InputEventData eventData) {
  highlightedMetatileIndex_ = coordinateToMetatileIndex(
    eventData.x(), eventData.y());
}

void MetatileBehaviorPickerScene
    ::pressMouse(InputEventData eventData) {
  if (eventData.mouseLeftButton()
      || eventData.mouseRightButton()) {
    // Pick tile
    pickMetatile(coordinateToMetatileIndex(
      eventData.x(), eventData.y()));
  }
}


};
