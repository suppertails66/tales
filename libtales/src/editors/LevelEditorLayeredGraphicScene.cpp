#include "editors/LevelEditorLayeredGraphicScene.h"
#include "gamedata/MetatileStructure.h"
#include "util/MiscMath.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


LevelEditorLayeredGraphicScene::LevelEditorLayeredGraphicScene(
                EditableLevelEffectsHeaders& levelEffectsHeaders__,
              EditableLevelGraphicsData& levelGraphicsData__,
              EditableLevelObjectEntryGroups& levelObjectEntryGroups__,
              EditableLevelPaletteHeaders& paletteHeaders__,
              EditableMapData& mapData__,
              EditableMetatileBehaviors& metatileBehaviors__,
              EditableMetatileHeightMaps& metatileHeightMaps__,
              EditableMetatileWidthMaps& metatileWidthMaps__,
              EditableSpawnPoints& spawnPoints__,
              EditableSpriteMappings& spriteMappings__,
              EditableStandardPalettes& palettes__,
              EditableWarpDestinations& warpDestinations__,
              LevelEditorToolManager& toolManager__,
              VRAMCache& vramCache__)
  : LayeredGraphicScene(),
    objectEditDialogCallback_(0),
    objectEditDialogCallbackParam_(0),
    levelEffectsHeaders_(levelEffectsHeaders__),
    levelGraphicsData_(levelGraphicsData__),
    levelObjectEntryGroups_(levelObjectEntryGroups__),
    paletteHeaders_(paletteHeaders__),
    mapData_(mapData__),
    metatileBehaviors_(metatileBehaviors__),
    metatileHeightMaps_(metatileHeightMaps__),
    metatileWidthMaps_(metatileWidthMaps__),
    spawnPoints_(spawnPoints__),
    spriteMappings_(spriteMappings__),
    palettes_(palettes__),
    warpDestinations_(warpDestinations__),
    toolManager_(toolManager__),
    vramCache_(vramCache__),
    sourceCache_(0, 0),
    areaNum_(1),
    mapNum_(1),
    levelHeaderIndex_(mapData_.levelHeaders()
                        .levelHeaderIndex(areaNum_, mapNum_)),
    bgLayerEnabled_(true),
    objectLayerEnabled_(true),
    fgLayerEnabled_(true),
    effectLayerEnabled_(false),
    verticalSolidityLayerEnabled_(false),
    horizontalSolidityLayerEnabled_(false),
    spawnLayerEnabled_(true),
    gridEnabled_(true),
    boundsLayerEnabled_(true),
    highlightedMetatileBoxEnabled_(false),
    highlightedMetatileIndex_(0),
    scrollX_(0),
    scrollY_(0),
    lastScrollX_(0),
    lastScrollY_(0),
    scale_(1.00),
    bgLayer_(vramCache_,
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             mapData_.metatileStructures().metatileStructureSet(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).tileStructureID()),
             LevelVisualGraphicSceneLayer::priorityBG),
    objectLayer_(vramCache_,
                 spriteMappings_,
                 (areaNum_ < 0x10) 
                   ? (&(warpDestinations_.warpsByMapnum(areaNum_, mapNum_)))
                   : 0,
                 levelGraphicsData_.objectGraphicsHeader(
                   levelGraphicsData_.levelGraphicsHeader(
                     levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_, mapNum_)
                   ).objectGraphicsHeaderIndex()
                 ),
                 levelGraphicsData_,
                 palettes_.palette(
                   paletteHeaders_.headerByIndex(
                     paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                   ).palette0Index()
                 ),
                 palettes_.palette(
                   paletteHeaders_.headerByIndex(
                     paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                   ).palette1Index()
                 ),
                 levelObjectEntryGroups_,
                 levelObjectEntryGroups_.indexOfMapnum(
                    areaNum_, mapNum_),
                 toolManager_),
    fgLayer_(vramCache_,
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             mapData_.metatileStructures().metatileStructureSet(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).tileStructureID()),
             LevelVisualGraphicSceneLayer::priorityFG),
    effectLayer_(
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             metatileBehaviors_),
    verticalSolidityLayer_(
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             metatileHeightMaps_,
             metatileBehaviors_,
             LevelSolidityGraphicSceneLayer::verticalMode),
    horizontalSolidityLayer_(
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             metatileWidthMaps_,
             metatileBehaviors_,
             LevelSolidityGraphicSceneLayer::horizontalMode),
    spawnLayer_(toolManager_,
                ((areaNum_ <= 0x0C)
                  ? (&(spawnPoints_.spawnsByMapnum(areaNum_,
                                                mapNum_)))
                  : 0),
                levelGraphicsData_,
                spriteMappings_,
                 palettes_.palette(
                   paletteHeaders_.headerByIndex(
                     paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                   ).palette0Index()
                 ),
                 palettes_.palette(
                   paletteHeaders_.headerByIndex(
                     paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                   ).palette1Index()
                 ),
                 areaNum_),
    grid_(16,
          1,
          Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity),
          false),
    boundsLayer_(
              mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_)) {
  changeMap(levelHeaderIndex_);
}

void LevelEditorLayeredGraphicScene::render(Graphic& dst,
                                            Box srcbox,
                                            double scale) {
//  dst = Graphic(srcbox.w() * scale, srcbox.h() * scale);
  if ((sourceCache_.w() != srcbox.w())
      || (sourceCache_.h() != srcbox.h())) {
    sourceCache_ = Graphic(srcbox.w(), srcbox.h());
  }

  sourceCache_.clear();
  
//  dst.clear();
  
  if (bgLayerEnabled_) {
    bgLayer_.render(sourceCache_,
                    srcbox,
                    1.00);
  }
                     
  if (effectLayerEnabled_) {
    effectLayer_.render(sourceCache_,
                  srcbox,
                  1.00);
  }
                     
  if (verticalSolidityLayerEnabled_) {
    verticalSolidityLayer_.render(sourceCache_,
                  srcbox,
                  1.00);
  }
                     
  if (horizontalSolidityLayerEnabled_) {
    horizontalSolidityLayer_.render(sourceCache_,
                  srcbox,
                  1.00);
  }
  
  if (objectLayerEnabled_) {
    objectLayer_.render(sourceCache_,
                        srcbox,
                        1.00);
  }
  
  if (fgLayerEnabled_) {
    fgLayer_.render(sourceCache_,
                    srcbox,
                    1.00);
  }
  
  if (spawnLayerEnabled_) {
    spawnLayer_.render(sourceCache_,
                       srcbox,
                       1.00);
  }
  
  drawToolPreview(sourceCache_,
                  srcbox,
                  scale);
  
  sourceCache_.scale(dst,
                     Graphic::noTransUpdate);
  
  if (gridEnabled_) {
    grid_.render(dst,
                 srcbox,
                 scale);
  }
  
  if (boundsLayerEnabled_) {
    boundsLayer_.render(dst,
                        srcbox,
                        scale);
  }
  
  // Draw scalable components of tools
  switch (toolManager_.currentTool()) {
  case LevelEditorTools::metatilePaint:
    if (highlightedMetatileBoxEnabled_) {
      int xPos = metatileIndexToX(highlightedMetatileIndex_) - scrollX_;
      int yPos = metatileIndexToY(highlightedMetatileIndex_) - scrollY_;
      
      dst.drawRectBorder(xPos * scale,
                         yPos * scale,
                         MetatileStructure::metatileWidth * scale,
                         MetatileStructure::metatileHeight * scale,
                         Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                         2);
    }
    break;
  case LevelEditorTools::metatileAreaClone:
    if (highlightedMetatileBoxEnabled_) {
      if ((toolManager_.metatileAreaCloneState()
            == LevelEditorTools::waitingForSelectionRelease)
          || (toolManager_.metatileAreaCloneState()
            == LevelEditorTools::readyToClone)) {
        int xPos = metatileXToRelative(toolManager_.metatileAreaCloneBaseX());
        int yPos = metatileYToRelative(toolManager_.metatileAreaCloneBaseY());
        if (toolManager_.metatileAreaCloneState()
            == LevelEditorTools::readyToClone) {
          xPos = (metatileIndexToX(highlightedMetatileIndex_) - scrollX_)
                    * scale;
          yPos = (metatileIndexToY(highlightedMetatileIndex_) - scrollY_)
                    * scale;
        }
        int width = toolManager_.metatileAreaCloneWidth()
                      * MetatileStructure::metatileWidth * scale;
        int height = toolManager_.metatileAreaCloneHeight()
                      * MetatileStructure::metatileHeight * scale;
        
        if ((width == 0) || (height == 0)) {
          break;
        }
        
        // hacky fix to make negative positions work intuitively
        // proper solution would use an anchor position in tool manager
        if (width < 0) {
          xPos += width;
          width = -width + (MetatileStructure::metatileWidth * scale);
        }
        
        if (height < 0) {
          yPos += height;
          height = -height + (MetatileStructure::metatileHeight * scale);
        }
        
        dst.drawRectBorder(xPos,
                           yPos,
                           width,
                           height,
                           Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                           2);
      }
    }
    break;
  default:
    break;
  }

//  dst.copy(vramCache_,
//           srcbox,
//           Graphic::noTransUpdate);
}
  
void LevelEditorLayeredGraphicScene::setObjectEditDialogCallback(
        bool (*objectEditDialogCallback__)(
          LevelObjectGraphicSceneLayer&,LevelObjectEntry&,void*),
        void* objectEditDialogCallbackParam__) {
  objectEditDialogCallback_ = objectEditDialogCallback__;
  objectEditDialogCallbackParam_ = objectEditDialogCallbackParam__;
  objectLayer_.setObjectEditDialogCallback(objectEditDialogCallback_,
                                           objectEditDialogCallbackParam_);
}

void LevelEditorLayeredGraphicScene::setObjectUpdateCallback(
        void (*objectUpdateCallback__)(
          LevelObjectGraphicSceneLayer&,void*),
        void* objectUpdateCallbackParam__) {
  objectUpdateCallback_ = objectUpdateCallback__;
  objectUpdateCallbackParam_ = objectUpdateCallbackParam__;
  objectLayer_.setObjectUpdateCallback(objectUpdateCallback_,
                                       objectUpdateCallbackParam_);
}
        
void LevelEditorLayeredGraphicScene::setObjectSelectionCallback(
        void (*objectSelectionCallback__)(
          LevelObjectGraphicSceneLayer&,
          LevelObjectEntryCollection::iterator,
          void*),
        void* objectSelectionCallbackParam__) {
  objectSelectionCallback_ = objectSelectionCallback__;
  objectSelectionCallbackParam_ = objectSelectionCallbackParam__;
  objectLayer_.setObjectSelectionCallback(objectSelectionCallback_,
                                          objectSelectionCallbackParam_);
}

void LevelEditorLayeredGraphicScene::setSpawnEditDialogCallback(
        bool (*spawnEditDialogCallback__)(
          LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*),
        void* spawnEditDialogCallbackParam__) {
  spawnEditDialogCallback_ = spawnEditDialogCallback__;
  spawnEditDialogCallbackParam_ = spawnEditDialogCallbackParam__;
  spawnLayer_.setSpawnEditDialogCallback(spawnEditDialogCallback_,
                                         spawnEditDialogCallbackParam_);
}
  
LevelObjectEntryGroup* LevelEditorLayeredGraphicScene::currentObjectGroup() {
  return objectLayer_.currentGroup();
}
  
void LevelEditorLayeredGraphicScene::selectObjectAtIndex(int index) {
  objectLayer_.selectObjectAtIndex(index);
}
  
void LevelEditorLayeredGraphicScene::eraseObjectAtIndex(int index) {
  objectLayer_.eraseObjectAtIndex(index);
}

void LevelEditorLayeredGraphicScene::editSelectedObject() {
  objectLayer_.editSelectedObject();
}

bool LevelEditorLayeredGraphicScene::editAndAppendObject() {
  return objectLayer_.editAndAppendObject();
}

void LevelEditorLayeredGraphicScene::refreshAllObjectVRAMOffsets() {
  objectLayer_.refreshAllGraphicVRAMOffsets();
}
                      
/*void LevelEditorLayeredGraphicScene::render(
                    Graphic& dst,
                    WrapScrollGraphic& cache,
                    Box srcbox,
                    double scale) {
  
//  dst.clear();
  
//  std::cout << srcbox.x() << " " << srcbox.y() << " " << srcbox.w()
//    << " " << srcbox.h() << std::endl;
  
  bgLayer_.render(cache,
                  Box(0, 0, 0, 0),
                  srcbox);
  
  fgLayer_.render(cache,
                  Box(0, 0, 0, 0),
                  srcbox);
                  
//  sourceCache_.scale(dst,
//                     Graphic::noTransUpdate);

  cache.surface().scale(dst,
                        Graphic::noTransUpdate);
  
  if (gridEnabled_) {
    grid_.render(dst,
                 srcbox,
                 scale);
  }

//  dst.copy(vramCache_,
//           srcbox,
//           Graphic::noTransUpdate);
} */
  
void LevelEditorLayeredGraphicScene::changeMap(int levelHeaderIndex__) {
  // Get area and map num
  AreaMapReference mapnums = mapData_.levelHeaders()
    .areaMapNumOfIndex(levelHeaderIndex__);
  
  areaNum_ = mapnums.areaNum();
  mapNum_ = mapnums.mapNum();
  levelHeaderIndex_ = levelHeaderIndex__;
  
  bgLayer_ = LevelVisualGraphicSceneLayer(
              vramCache_,
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             mapData_.metatileStructures().metatileStructureSet(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).tileStructureID()),
             LevelVisualGraphicSceneLayer::priorityBG);
  
  // HACK: Areas 16 (world map) and 19 (intro) have standard map data,
  // but use hardcoded object layouts we can't modify.
  // LevelObjectGraphicSceneLayer recognizes index -1 as "no objects".
  int objectIndex = -1;
  if ((areaNum_ != 16) && (areaNum_ != 19)) {
    objectIndex = levelObjectEntryGroups_.indexOfMapnum(
                      areaNum_, mapNum_);
  }
             
  objectLayer_ = LevelObjectGraphicSceneLayer(
                   vramCache_,
                   spriteMappings_,
                   (areaNum_ < 0x10) 
                     ? (&(warpDestinations_.warpsByMapnum(areaNum_, mapNum_)))
                     : 0,
                   levelGraphicsData_.objectGraphicsHeader(
                     levelGraphicsData_.levelGraphicsHeader(
                       levelGraphicsData_
                         .levelHeaderIndexByMapnum(areaNum_, mapNum_)
                     ).objectGraphicsHeaderIndex()
                   ),
                   levelGraphicsData_,
                   palettes_.palette(
                     paletteHeaders_.headerByIndex(
                       paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                     ).palette0Index()
                   ),
                   palettes_.palette(
                     paletteHeaders_.headerByIndex(
                       paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                     ).palette1Index()
                   ),
                   levelObjectEntryGroups_,
                   objectIndex,
                   toolManager_);
  
  fgLayer_ = LevelVisualGraphicSceneLayer(
              vramCache_,
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             mapData_.metatileStructures().metatileStructureSet(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).tileStructureID()),
             LevelVisualGraphicSceneLayer::priorityFG);
  
  effectLayer_ = LevelEffectGraphicSceneLayer(
             mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_),
             mapData_.mapLayouts().mapAtIndex(
               mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
             metatileBehaviors_);
             
  verticalSolidityLayer_ = LevelSolidityGraphicSceneLayer(
           mapData_.levelHeaders()
              .levelHeaderByIndex(levelHeaderIndex_),
           mapData_.mapLayouts().mapAtIndex(
             mapData_.levelHeaders()
              .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
           metatileHeightMaps_,
           metatileBehaviors_,
           LevelSolidityGraphicSceneLayer::verticalMode);
           
  horizontalSolidityLayer_ = LevelSolidityGraphicSceneLayer(
           mapData_.levelHeaders()
              .levelHeaderByIndex(levelHeaderIndex_),
           mapData_.mapLayouts().mapAtIndex(
             mapData_.levelHeaders()
              .levelHeaderByIndex(levelHeaderIndex_).mapLayoutID()),
           metatileWidthMaps_,
           metatileBehaviors_,
           LevelSolidityGraphicSceneLayer::horizontalMode);
  
  spawnLayer_ = LevelSpawnGraphicSceneLayer(toolManager_,
                ((areaNum_ <= 0x0C)
                  ? (&(spawnPoints_.spawnsByMapnum(areaNum_,
                                                mapNum_)))
                  : 0),
                levelGraphicsData_,
                spriteMappings_,
                 palettes_.palette(
                   paletteHeaders_.headerByIndex(
                     paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                   ).palette0Index()
                 ),
                 palettes_.palette(
                   paletteHeaders_.headerByIndex(
                     paletteHeaders_.indexOfMapNum(areaNum_, mapNum_)
                   ).palette1Index()
                 ),
                 areaNum_);
             
  boundsLayer_ = LevelBoundsGraphicSceneLayer(
              mapData_.levelHeaders()
                .levelHeaderByIndex(levelHeaderIndex_));
             
  grid_.setXLimit(
    (mapData_.levelHeaders().levelHeaderByIndex(
    levelHeaderIndex())
      .width())
        * MetatileStructure::metatileWidth);
             
  grid_.setYLimit(
    ((MapLayout::dataSize + 1)
    / (mapData_.levelHeaders().levelHeaderByIndex(
      levelHeaderIndex())
        .width())) * MetatileStructure::metatileHeight);
  
  objectLayer_.setObjectEditDialogCallback(objectEditDialogCallback_,
                                           objectEditDialogCallbackParam_);
  objectLayer_.setObjectUpdateCallback(objectUpdateCallback_,
                                       objectUpdateCallbackParam_);
  objectLayer_.setObjectSelectionCallback(objectSelectionCallback_,
                                       objectSelectionCallbackParam_);
  spawnLayer_.setSpawnEditDialogCallback(spawnEditDialogCallback_,
                                         spawnEditDialogCallbackParam_);
  
  resetSelection();
}
  
void LevelEditorLayeredGraphicScene::resetSelection() {
  toolManager_.setObjectEditorState(
      LevelEditorTools::objectEditorNothingSelected);
  toolManager_.objectEditorMultipleCacheIts().clear();
  toolManager_.objectEditorMultipleGroupIts().clear();
}
  
void LevelEditorLayeredGraphicScene::enterMouse() {
  highlightedMetatileBoxEnabled_ = true;
}

void LevelEditorLayeredGraphicScene::exitMouse() {
  highlightedMetatileBoxEnabled_ = false;
}

void LevelEditorLayeredGraphicScene
    ::moveMouse(int x, int y, InputEventData eventData) {
  int realX = relativeToRealX(x);
  int realY = relativeToRealY(y);
  
  if ((realX / MetatileStructure::metatileWidth)
         < (mapData_.levelHeaders().levelHeaderByIndex(
                levelHeaderIndex()).width())) {
    highlightedMetatileIndex_ = coordinateToMetatileIndex(
      realX, realY);
  }
  
//  triggerTool(eventData);

  switch (toolManager_.currentTool()) {
  case LevelEditorTools::metatilePaint:
    triggerMetatilePaint(eventData);
    break;
  case LevelEditorTools::metatileAreaClone:
    doMetatileAreaClone(x, y, eventData);
    break;
  case LevelEditorTools::objectEditor:
  case LevelEditorTools::spawnEditor:
    if (objectLayerEnabled_) {
      objectLayer_.moveMouse(realX, realY, eventData);
    }
//    break;
//  case LevelEditorTools::spawnEditor:
    if (spawnLayerEnabled_) {
      spawnLayer_.moveMouse(realX, realY, eventData);
    }
    break;
  default:
    break;
  }
}

void LevelEditorLayeredGraphicScene
    ::pressMouse(int x, int y, InputEventData eventData) {
//  triggerTool(eventData);

  switch (toolManager_.currentTool()) {
  case LevelEditorTools::metatilePaint:
    triggerMetatilePaint(eventData);
    break;
  case LevelEditorTools::metatileAreaClone:
    doMetatileAreaClone(x, y, eventData);
    break;
  case LevelEditorTools::objectEditor:
  case LevelEditorTools::spawnEditor:
    if (objectLayerEnabled_) {
      objectLayer_.pressMouse(
          relativeToRealX(x), relativeToRealY(y), eventData);
    }
//    break;
//  case LevelEditorTools::spawnEditor:
    if (spawnLayerEnabled_) {
      spawnLayer_.pressMouse(
          relativeToRealX(x), relativeToRealY(y), eventData);
    }
    break;
  default:
    break;
  }
}

void LevelEditorLayeredGraphicScene
    ::doubleClickMouse(int x, int y, InputEventData eventData) {

  switch (toolManager_.currentTool()) {
  case LevelEditorTools::objectEditor:
  case LevelEditorTools::spawnEditor:
    if (objectLayerEnabled_) {
      objectLayer_.doubleClickMouse(relativeToRealX(x), relativeToRealY(y),
                                    eventData);
    }
//    break;
//  case LevelEditorTools::spawnEditor:
    if (spawnLayerEnabled_) {
      spawnLayer_.doubleClickMouse(relativeToRealX(x), relativeToRealY(y),
                                    eventData);
    }
    break;
  default:
    break;
  }
}

void LevelEditorLayeredGraphicScene
    ::releaseMouse(int x, int y, InputEventData eventData) {
  switch (toolManager_.currentTool()) {
  case LevelEditorTools::metatileAreaClone:
    doMetatileAreaCloneRelease(x, y, eventData);
    break;
  case LevelEditorTools::objectEditor:
  case LevelEditorTools::spawnEditor:
    if (objectLayerEnabled_) {
      objectLayer_.releaseMouse(
          relativeToRealX(x), relativeToRealY(y), eventData);
    }
//    break;
//  case LevelEditorTools::spawnEditor:
    if (spawnLayerEnabled_) {
      spawnLayer_.releaseMouse(
          relativeToRealX(x), relativeToRealY(y), eventData);
    }
    break;
  default:
    break;
  }
}
  
int LevelEditorLayeredGraphicScene::areaNum() const {
  return areaNum_;
}

int LevelEditorLayeredGraphicScene::mapNum() const {
  return mapNum_;
}

int LevelEditorLayeredGraphicScene::levelHeaderIndex() const {
  return levelHeaderIndex_;
}
  
int LevelEditorLayeredGraphicScene::scrollX() const {
  return scrollX_;
}

void LevelEditorLayeredGraphicScene::setScrollX(int scrollX__) {
  scrollX_ = scrollX__;
}

int LevelEditorLayeredGraphicScene::scrollY() const {
  return scrollY_;
}

void LevelEditorLayeredGraphicScene::setScrollY(int scrollY__) {
  scrollY_ = scrollY__;
}
  
double LevelEditorLayeredGraphicScene::scale() const {
  return scale_;
}

void LevelEditorLayeredGraphicScene::setScale(double scale__) {
  scale_ = scale__;
}

bool LevelEditorLayeredGraphicScene::bgLayerEnabled() const {
  return bgLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setBGLayerEnabled(bool bgLayerEnabled__) {
  bgLayerEnabled_ = bgLayerEnabled__;
}

bool LevelEditorLayeredGraphicScene::objectLayerEnabled() const {
  return objectLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setObjectLayerEnabled(bool objectLayerEnabled__) {
  objectLayerEnabled_ = objectLayerEnabled__;
}
  
bool LevelEditorLayeredGraphicScene::fgLayerEnabled() const {
  return fgLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setFGLayerEnabled(bool fgLayerEnabled__) {
  fgLayerEnabled_ = fgLayerEnabled__;
}
  
bool LevelEditorLayeredGraphicScene::effectLayerEnabled() const {
  return effectLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setEffectLayerEnabled(bool effectLayerEnabled__) {
  effectLayerEnabled_ = effectLayerEnabled__;
}

bool LevelEditorLayeredGraphicScene
    ::verticalSolidityLayerEnabled() const {
  return verticalSolidityLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setVerticalSolidityLayerEnabled(
    bool verticalSolidityLayerEnabled__) {
  verticalSolidityLayerEnabled_ = verticalSolidityLayerEnabled__;
}

bool LevelEditorLayeredGraphicScene
    ::horizontalSolidityLayerEnabled() const {
  return horizontalSolidityLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setHorizontalSolidityLayerEnabled(
    bool horizontalSolidityLayerEnabled__) {
  horizontalSolidityLayerEnabled_ = horizontalSolidityLayerEnabled__;
}

bool LevelEditorLayeredGraphicScene
    ::spawnLayerEnabled() const {
  return spawnLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setSpawnLayerEnabled(bool spawnLayerEnabled__) {
  spawnLayerEnabled_ = spawnLayerEnabled__;
}
  
bool LevelEditorLayeredGraphicScene::gridEnabled() const {
  return gridEnabled_;
}

void LevelEditorLayeredGraphicScene::setGridEnabled(bool gridEnabled__) {
  gridEnabled_ = gridEnabled__;
}

bool LevelEditorLayeredGraphicScene::boundsLayerEnabled() const {
  return boundsLayerEnabled_;
}

void LevelEditorLayeredGraphicScene
    ::setBoundsLayerEnabled(bool boundsLayerEnabled__) {
  boundsLayerEnabled_ = boundsLayerEnabled__;
}
  
int LevelEditorLayeredGraphicScene::cameraTopBound() {
  return currentLevelHeader().cameraTopLimit();
}

int LevelEditorLayeredGraphicScene::cameraBottomBound() {
  return currentLevelHeader().cameraBottomLimit();
}

int LevelEditorLayeredGraphicScene::cameraLeftBound() {
  return currentLevelHeader().cameraLeftLimit();
}

int LevelEditorLayeredGraphicScene::cameraRightBound() {
  return currentLevelHeader().cameraRightLimit();
}

void LevelEditorLayeredGraphicScene
    ::setCameraTopBound(int cameraTopBound__) {
  currentLevelHeader().setCameraTopLimit(cameraTopBound__);
}

void LevelEditorLayeredGraphicScene
    ::setCameraBottomBound(int cameraBottomBound__) {
  currentLevelHeader().setCameraBottomLimit(cameraBottomBound__);
}

void LevelEditorLayeredGraphicScene
    ::setCameraLeftBound(int cameraLeftBound__) {
  currentLevelHeader().setCameraLeftLimit(cameraLeftBound__);
}

void LevelEditorLayeredGraphicScene
    ::setCameraRightBound(int cameraRightBound__) {
  currentLevelHeader().setCameraRightLimit(cameraRightBound__);
}
  
int LevelEditorLayeredGraphicScene::metatileIndexToX(int index) {
  return (index 
            % (mapData_.levelHeaders().levelHeaderByIndex(
                levelHeaderIndex()).width()))
         * MetatileStructure::metatileWidth;
}

int LevelEditorLayeredGraphicScene::metatileIndexToY(int index) {
  return (index 
            / (mapData_.levelHeaders().levelHeaderByIndex(
                levelHeaderIndex()).width()))
         * MetatileStructure::metatileHeight;
}

int LevelEditorLayeredGraphicScene
    ::coordinateToMetatileIndex(int x, int y) {
  int width = currentLevelMetatileWidth();
  
  int index = ((y / MetatileStructure::metatileHeight) * width)
           + (x / MetatileStructure::metatileWidth);
           
  // Clamp to valid range
  MiscMath::clamp(index, 0, MapLayout::dataSize - 1);
  
  return index;
}

int LevelEditorLayeredGraphicScene
    ::relativeXToMetatile(int x) {
  int mCoord = (x / scale_) + scrollX_;
  return mCoord / MetatileStructure::metatileWidth;
}

int LevelEditorLayeredGraphicScene
    ::relativeYToMetatile(int y) {
  int mCoord = (y / scale_) + scrollY_;
  return mCoord / MetatileStructure::metatileHeight;
}

int LevelEditorLayeredGraphicScene
    ::relativeToRealX(int x) {
  return ((int)(x / scale_)) + scrollX_;
}

int LevelEditorLayeredGraphicScene
    ::relativeToRealY(int y) {
  return ((int)(y / scale_)) + scrollY_;
}

int LevelEditorLayeredGraphicScene
    ::metatileXToRelative(int x) {
  return ((x * MetatileStructure::metatileWidth - scrollX_) * scale_);
}
    
int LevelEditorLayeredGraphicScene
    ::metatileYToRelative(int y) {
  return ((y * MetatileStructure::metatileHeight - scrollY_) * scale_);
}

LevelHeader& LevelEditorLayeredGraphicScene
    ::currentLevelHeader() {
  return mapData_.levelHeaders().levelHeaderByIndex(
        levelHeaderIndex());
}

MapLayout& LevelEditorLayeredGraphicScene
    ::currentMapLayout() {
  return mapData_.mapLayouts().mapAtIndex(
                     currentLevelHeader().mapLayoutID());
}

int LevelEditorLayeredGraphicScene
    ::currentLevelMetatileWidth() {
  return currentLevelHeader().width();
}

void LevelEditorLayeredGraphicScene
    ::setCurrentLevelMetatileWidth(int width__) {
  currentLevelHeader().setWidth(width__);
}

int LevelEditorLayeredGraphicScene
    ::currentLevelMetatileHeight() {
  return MapLayout::dataSize / currentLevelMetatileWidth();
}
  
void LevelEditorLayeredGraphicScene
    ::drawToolPreview(Graphic& dst,
                     Box srcbox,
                     double scale) {
  switch (toolManager_.currentTool()) {
  case LevelEditorTools::metatilePaint:
    // Draw the tile to be placed at the cursor position
    if (highlightedMetatileBoxEnabled_) {
      int xPos = metatileIndexToX(highlightedMetatileIndex_) - scrollX_;
      int yPos = metatileIndexToY(highlightedMetatileIndex_) - scrollY_;
      renderMetatile(dst,
                     toolManager_.pickedMetatileIndex(),
                     xPos, yPos);
    }
    break;
  case LevelEditorTools::metatileAreaClone:
    switch (toolManager_.metatileAreaCloneState()) {
    case LevelEditorTools::waitingForSelectionClick:
      break;
    case LevelEditorTools::waitingForSelectionRelease:
      {
      
      }
      break;
    case LevelEditorTools::readyToClone:
      if (highlightedMetatileBoxEnabled_) {
        int xPos = metatileIndexToX(highlightedMetatileIndex_) - scrollX_;
        int yPos = metatileIndexToY(highlightedMetatileIndex_) - scrollY_;
        
        int mXPos = metatileIndexToX(highlightedMetatileIndex_)
              / MetatileStructure::metatileWidth;
        int mYPos = metatileIndexToY(highlightedMetatileIndex_)
              / MetatileStructure::metatileHeight;
        
        int mapWidth = currentLevelMetatileWidth();
        int mapHeight = currentLevelMetatileHeight();
        
        for (int j = 0; j < toolManager_.metatileAreaCloneHeight(); j++) {
          for (int i = 0; i < toolManager_.metatileAreaCloneWidth(); i++) {
            if (((mXPos + i) > mapWidth)
                || ((mYPos + j) > mapHeight)) {
              continue;
            }
            
            int targetX = xPos + (i * MetatileStructure::metatileWidth);
            int targetY = yPos + (j * MetatileStructure::metatileHeight);
            
            renderMetatile(dst,
                           toolManager_.metatileAreaCloneMetatile(i, j),
                           targetX, targetY);
          }
        }
      }
      break;
    default:
      break;
    } // end of switch
    break;
  default:
    break;
  } // end of switch
}
                       
void LevelEditorLayeredGraphicScene
    ::triggerMetatilePaint(InputEventData eventData) {
  if (eventData.mouseLeftButton()) {
    if (eventData.control()) {
      // Switch to area clone tool
      toolManager_.setCurrentTool(LevelEditorTools::metatileAreaClone);
      return;
    }
    else {
      // Change tile
      mapData_.mapLayouts().mapAtIndex(
                     currentLevelHeader().mapLayoutID())
                        .setMetatile(highlightedMetatileIndex_,
                                     toolManager_.pickedMetatileIndex());
    }
  }
  else if (eventData.mouseRightButton()) {
    // Select tile under mouse as current
    toolManager_.setPickedMetatileIndex(
      mapData_.mapLayouts().mapAtIndex(
                     currentLevelHeader().mapLayoutID())
                        .getMetatile(highlightedMetatileIndex_));
  }
}

void LevelEditorLayeredGraphicScene
    ::doMetatileAreaClone(int x, int y, InputEventData eventData) {
  switch (toolManager_.metatileAreaCloneState()) {
  case LevelEditorTools::waitingForSelectionClick:
    metatileAreaCloneClickStep(x, y, eventData);
    break;
  case LevelEditorTools::waitingForSelectionRelease:
    metatileAreaCloneSelectionStep(x, y, eventData);
    break;
  case LevelEditorTools::readyToClone:
    metatileAreaCloneCloneStep(x, y, eventData);
    break;
  default:
    break;
  }
}

void LevelEditorLayeredGraphicScene
    ::doMetatileAreaCloneRelease(int x, int y, InputEventData eventData) {
  switch (toolManager_.metatileAreaCloneState()) {
  case LevelEditorTools::waitingForSelectionRelease:
    {
      // check if mouse released
    if ((!(eventData.mouseLeftButton()))
        && (!(eventData.mouseRightButton()))) {
      // verify that final position is in range
      int finalX = toolManager_.metatileAreaCloneBaseX()
                     + toolManager_.metatileAreaCloneWidth();
      int finalY = toolManager_.metatileAreaCloneBaseY()
                     + toolManager_.metatileAreaCloneHeight();
    
      if ((finalX < 0)
          || (finalY < 0)
          || (finalX - 1 > currentLevelMetatileWidth())
          || (finalY - 1 > currentLevelMetatileHeight())
          || toolManager_.metatileAreaCloneWidth() == 0
          || toolManager_.metatileAreaCloneHeight() == 0) {
        toolManager_.setMetatileAreaCloneState(
          LevelEditorTools::waitingForSelectionClick);
        return;
      }
    
      toolManager_.finalizeMetatileAreaClone(
        currentMapLayout(),
        currentLevelMetatileWidth());
      toolManager_.setMetatileAreaCloneState(
        LevelEditorTools::readyToClone);
      return;
    }
    }
    break;
  default:
    break;
  }
}

void LevelEditorLayeredGraphicScene
    ::metatileAreaCloneClickStep(int x, int y, InputEventData eventData) {
  if ((!(eventData.mouseLeftButton()))
      && (!(eventData.mouseRightButton()))) {
    return;
  }
  
  int realX = relativeXToMetatile(x);
  int realY = relativeYToMetatile(y);
  
  if ((realX < 0)
      || (realY < 0)
      || (realX > currentLevelMetatileWidth())
      || (realY > currentLevelMetatileHeight())) {
    return;
  }
  
  toolManager_.setMetatileAreaCloneBaseX(
    realX);
  toolManager_.setMetatileAreaCloneBaseY(
    realY);
  toolManager_.setMetatileAreaCloneWidth(1);
  toolManager_.setMetatileAreaCloneHeight(1);
  toolManager_.setMetatileAreaCloneState(
    LevelEditorTools::waitingForSelectionRelease);
}

void LevelEditorLayeredGraphicScene
    ::metatileAreaCloneSelectionStep(int x, int y, InputEventData eventData) {
  int realX = relativeXToMetatile(x);
  int realY = relativeYToMetatile(y);
  
  int xDiff = realX - toolManager_.metatileAreaCloneBaseX();
  int yDiff = realY - toolManager_.metatileAreaCloneBaseY();
  
  if (realX >= currentLevelMetatileWidth()) {
    xDiff = currentLevelMetatileWidth()
      - toolManager_.metatileAreaCloneBaseX();
  }
  else if (realX < 0) {
    xDiff = -toolManager_.metatileAreaCloneBaseX();
  }
  else {
    if (xDiff > -1) {
      ++xDiff;
    }
  }
  
  if (realY > currentLevelMetatileHeight()) {
    yDiff = currentLevelMetatileHeight()
      - toolManager_.metatileAreaCloneBaseY() + 1;
  }
  else if (realY < 0) {
    yDiff = -toolManager_.metatileAreaCloneBaseY();
  }
  else {
    if (yDiff > -1) {
      ++yDiff;
    }
  }
  
//  if (xDiff == 0) {
//    toolManager_.setMetatileAreaCloneWidth(1);
//  }
//  else {
    toolManager_.setMetatileAreaCloneWidth(xDiff);
//  }
  
//  if (yDiff == 0) {
//    toolManager_.setMetatileAreaCloneWidth(1);
//  }
//  else {
    toolManager_.setMetatileAreaCloneHeight(yDiff);
//  }
}

void LevelEditorLayeredGraphicScene
    ::metatileAreaCloneCloneStep(int x, int y, InputEventData eventData) {
    
  if ((eventData.mouseLeftButton())
      && (eventData.control())) {
    // select new area
    toolManager_.setMetatileAreaCloneState(
      LevelEditorTools::waitingForSelectionClick);
    metatileAreaCloneClickStep(x, y, eventData);
    return;
  }
                        
  if (eventData.mouseRightButton()) {
    // Switch to paint mode
    toolManager_.setCurrentTool(LevelEditorTools::metatilePaint);
    // Pass off event
    triggerMetatilePaint(eventData);
    return;
  }
  
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
  int realX = relativeXToMetatile(x);
  int realY = relativeYToMetatile(y);
  
  if ((realX < 0) || (realY < 0)) {
    return;
  }
  
  int limitX = realX + toolManager_.metatileAreaCloneWidth();
  int limitY = realY + toolManager_.metatileAreaCloneHeight();
  
  if (limitX > currentLevelMetatileWidth()) {
    limitX = currentLevelMetatileWidth();
  }
  
  if (limitY > currentLevelMetatileHeight()) {
    // TODO: this will probably break something eventually, look here
    // when it happens
    limitY = currentLevelMetatileHeight() + 1;
  }
  
  limitX -= realX;
  limitY -= realY;
  
  for (int j = 0; j < limitY; j++) {
    for (int i = 0; i < limitX; i++) {
      int targetX = realX + i;
      int targetY = realY + j;
      int targetIndex = coordinateToMetatileIndex(
                          targetX * MetatileStructure::metatileWidth,
                          targetY * MetatileStructure::metatileHeight);
      if (targetIndex >= MapLayout::dataSize) {
        continue;
      }
      
      int metatileIndex = toolManager_.metatileAreaCloneMetatile(i, j);
      currentMapLayout().setMetatile(targetIndex, (Tbyte)metatileIndex);
    }
  }
}
  
void LevelEditorLayeredGraphicScene
    ::renderMetatile(Graphic& dst,
                     int metatileID,
                     int x, int y) {
  if (bgLayerEnabled_) {
    dst.blit(bgLayer_.metatileGraphic(metatileID),
             Box(x, y, 0, 0),
             Graphic::transUpdate);
  }
  
  if (fgLayerEnabled_) {
    dst.blit(fgLayer_.metatileGraphic(metatileID),
             Box(x, y, 0, 0),
             Graphic::transUpdate);
  }
  
  if (effectLayerEnabled_) {
    dst.blit(effectLayer_.metatileGraphic(metatileID),
             Box(x, y, 0, 0),
             Graphic::transUpdate);
  }
  
  if (verticalSolidityLayerEnabled_) {
    dst.blit(verticalSolidityLayer_.metatileGraphic(metatileID),
             Box(x, y, 0, 0),
             Graphic::transUpdate);
  }
  
  if (horizontalSolidityLayerEnabled_) {
    dst.blit(horizontalSolidityLayer_.metatileGraphic(metatileID),
             Box(x, y, 0, 0),
             Graphic::transUpdate);
  }
}


};
