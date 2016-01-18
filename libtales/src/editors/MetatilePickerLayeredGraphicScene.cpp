#include "editors/MetatilePickerLayeredGraphicScene.h"
#include "editors/LevelVisualGraphicSceneLayer.h"
#include "editors/LevelEffectGraphicSceneLayer.h"
#include "gamedata/MetatileStructure.h"
#include "editors/LengthMapDrawer.h"

namespace Tales {


MetatilePickerLayeredGraphicScene::MetatilePickerLayeredGraphicScene(
                                    const MetatileStructureSet&
                                      metatileStructureSet__,
                                    const EditableMetatileBehaviors&
                                      metatileBehaviors__,
                                    EditableMetatileWidthMaps&
                                      widthMaps__,
                                    EditableMetatileHeightMaps&
                                      heightMaps__,
                                    LevelEditorToolManager&
                                      toolManager__,
                                    const VRAMCache& vramCache__)
  : metatileStructureSet_(&metatileStructureSet__),
    metatileBehaviors_(&metatileBehaviors__),
    widthMaps_(&widthMaps__),
    heightMaps_(&heightMaps__),
    toolManager_(&toolManager__),
    vramCache_(&vramCache__),
    bgLayerEnabled_(true),
    fgLayerEnabled_(true),
    effectLayerEnabled_(false),
    verticalSolidityLayerEnabled_(false),
    horizontalSolidityLayerEnabled_(false),
    gridLayerEnabled_(true),
    highlightedMetatileBoxEnabled_(false),
    highlightedMetatileIndex_(0),
    gridLayer_(16,
               1,
               Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity),
               false) {
  gridLayer_.setXLimit(metatilesPerRow_ * MetatileStructure::metatileWidth);
  gridLayer_.setYLimit(metatilesPerColumn_
                          * MetatileStructure::metatileHeight);
                          
  for (int i = 0; i < numMetatiles_; i++) {
    Graphic metatileVisualBGGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    Graphic metatileVisualFGGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    Graphic metatileEffectGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    Graphic metatileVerticalSolidityGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    Graphic metatileHorizontalSolidityGraphic(MetatileStructure::metatileWidth,
                            MetatileStructure::metatileHeight);
    
    LevelVisualGraphicSceneLayer
      ::drawMetatilePriorityVisual(metatileVisualBGGraphic,
                           *vramCache_,
                           metatileStructureSet_->metatileMapping(i),
                           LevelVisualGraphicSceneLayer::priorityBG);
    
    LevelVisualGraphicSceneLayer
      ::drawMetatilePriorityVisual(metatileVisualFGGraphic,
                           *vramCache_,
                           metatileStructureSet_->metatileMapping(i),
                           LevelVisualGraphicSceneLayer::priorityFG);
    
    LevelEffectGraphicSceneLayer
      ::drawMetatileEffect(metatileEffectGraphic,
                           i,
                           metatileBehaviors_->metatileBehavior(i));
                           
    LengthMapDrawer::drawWidthMap(metatileHorizontalSolidityGraphic,
                           widthMaps_->mapAt(
                             metatileBehaviors_->metatileBehavior(i)
                               .widthMapIndex()),
                           metatileBehaviors_->metatileBehavior(i));
                           
    LengthMapDrawer::drawHeightMap(metatileVerticalSolidityGraphic,
                           heightMaps_->mapAt(
                             metatileBehaviors_->metatileBehavior(i)
                               .heightMapIndex()),
                           metatileBehaviors_->metatileBehavior(i));
                           
    metatileVisualBGGraphic.regenerateTransparencyModel();
    metatileVisualFGGraphic.regenerateTransparencyModel();
    metatileEffectGraphic.regenerateTransparencyModel();
    metatileVerticalSolidityGraphic.regenerateTransparencyModel();
    metatileHorizontalSolidityGraphic.regenerateTransparencyModel();
    
    metatilesVisualBG_.push_back(metatileVisualBGGraphic);
    metatilesVisualFG_.push_back(metatileVisualFGGraphic);
    metatilesEffect_.push_back(metatileEffectGraphic);
    metatilesVerticalSolidity_.push_back(
        metatileVerticalSolidityGraphic);
    metatilesHorizontalSolidity_.push_back(
        metatileHorizontalSolidityGraphic);
  }
}

void MetatilePickerLayeredGraphicScene::render(Graphic& dst,
                      Box srcbox,
                      double scale) {
  dst.clear();
  
  int metatileNum = 0;
  for (int j = 0; j < metatilesPerColumn_; j++) {
    for (int i = 0; i < metatilesPerRow_; i++) {
      if (bgLayerEnabled_) {
        dst.blit(metatilesVisualBG_[metatileNum],
                 Box(i * MetatileStructure::metatileWidth,
                     j * MetatileStructure::metatileHeight,
                     MetatileStructure::metatileWidth,
                     MetatileStructure::metatileHeight),
                 Graphic::transUpdate);
      }
      
      if (fgLayerEnabled_) {
        dst.blit(metatilesVisualFG_[metatileNum],
                 Box(i * MetatileStructure::metatileWidth,
                     j * MetatileStructure::metatileHeight,
                     MetatileStructure::metatileWidth,
                     MetatileStructure::metatileHeight),
                 Graphic::transUpdate);
      }
      
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
  
  if ((toolManager_->currentTool() == LevelEditorTools::metatilePaint)) {
    dst.drawRectBorder(metatileIndexToX(toolManager_->pickedMetatileIndex()),
                       metatileIndexToY(toolManager_->pickedMetatileIndex()),
                       MetatileStructure::metatileWidth,
                       MetatileStructure::metatileHeight,
                       Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                       2);
  }
}

void MetatilePickerLayeredGraphicScene::enterMouse() {
  highlightedMetatileBoxEnabled_ = true;
}
  
void MetatilePickerLayeredGraphicScene::exitMouse() {
  highlightedMetatileBoxEnabled_ = false;
}
                      
void MetatilePickerLayeredGraphicScene
    ::moveMouse(int x, int y, InputEventData eventData) {
/*  if (eventData.mouseLeftButton()) {
    // Pick tile
    toolManager_->setCurrentTool(LevelEditorTools::metatilePaint);
    toolManager_->setPickedMetatileIndex(coordinateToMetatileIndex(x, y));
  } */
  
  highlightedMetatileIndex_ = coordinateToMetatileIndex(x, y);
}

void MetatilePickerLayeredGraphicScene
    ::pressMouse(int x, int y, InputEventData eventData) {
  if (eventData.mouseLeftButton()
      || eventData.mouseRightButton()) {
    // Pick tile
    toolManager_->setCurrentTool(LevelEditorTools::metatilePaint);
    toolManager_->setPickedMetatileIndex(coordinateToMetatileIndex(x, y));
  }
}
                      
void MetatilePickerLayeredGraphicScene::setBGLayerEnabled(
    bool bgLayerEnabled__) {
  bgLayerEnabled_ = bgLayerEnabled__;
}
                      
void MetatilePickerLayeredGraphicScene::setFGLayerEnabled(
    bool fgLayerEnabled__) {
  fgLayerEnabled_ = fgLayerEnabled__;
}

void MetatilePickerLayeredGraphicScene::setEffectLayerEnabled(
    bool effectLayerEnabled__) {
  effectLayerEnabled_ = effectLayerEnabled__;
}

void MetatilePickerLayeredGraphicScene
    ::setVerticalSolidityLayerEnabled(
    bool verticalSolidityLayerEnabled__) {
  verticalSolidityLayerEnabled_ = verticalSolidityLayerEnabled__;
}

void MetatilePickerLayeredGraphicScene
    ::setHorizontalSolidityLayerEnabled(
    bool horizontalSolidityLayerEnabled__) {
  horizontalSolidityLayerEnabled_ = horizontalSolidityLayerEnabled__;
}

void MetatilePickerLayeredGraphicScene::setGridLayerEnabled(
    bool gridLayerEnabled__) {
  gridLayerEnabled_ = gridLayerEnabled__;
}
  
int MetatilePickerLayeredGraphicScene::metatileIndexToX(int index) const {
  return (index % metatilesPerRow_)
    * MetatileStructure::metatileWidth;
}

int MetatilePickerLayeredGraphicScene::metatileIndexToY(int index) const {
  return (index / metatilesPerRow_)
    * MetatileStructure::metatileHeight;
}

int MetatilePickerLayeredGraphicScene
    ::coordinateToMetatileIndex(int x, int y) const {
  return ((y / MetatileStructure::metatileHeight) * metatilesPerRow_)
            + (x / MetatileStructure::metatileWidth);
}



};
