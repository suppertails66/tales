#include "editors/LevelEditor.h"
#include "gamedata/MetatileStructure.h"
#include <cstdlib>

namespace Tales {


LevelEditor::LevelEditor(
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
              EditorMetadata& metadata__)
  : levelEffectsHeaders_(levelEffectsHeaders__),
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
    metadata_(metadata__),
    toolManager_(),
    vramCache_(),
    previewScene_(levelEffectsHeaders__,
                  levelGraphicsData__,
                  levelObjectEntryGroups__,
                  paletteHeaders__,
                  mapData__,
                  metatileBehaviors__,
                  metatileHeightMaps__,
                  metatileWidthMaps__,
                  spawnPoints__,
                  spriteMappings__,
                  palettes__,
                  warpDestinations__,
                  toolManager_,
                  vramCache_),
    metatilePickerScene_(mapData_.metatileStructures()
                           .metatileStructureSet(
                             mapData_.levelHeaders().levelHeaderByIndex(
                               previewScene_.levelHeaderIndex())
                                .tileStructureID()),
                         metatileBehaviors_,
                         metatileWidthMaps_,
                         metatileHeightMaps_,
                         toolManager_,
                         vramCache_),
//    wrapScrollCache_(0, 0),
//    needWrapCacheRefresh_(false),
//    lastRenderedScrollX_(0),
//    lastRenderedScrollY_(0),
    levelViewMode_(viewLevelVisual)
//    scrollX_(0),
//    scrollY_(0)
    {
  changeMap(previewScene_.levelHeaderIndex());
}

void LevelEditor::refresh() {
  changeMap(previewScene_.levelHeaderIndex());
}
  
void LevelEditor::setObjectEditDialogCallback(
        bool (*objectEditDialogCallback__)(
          LevelObjectGraphicSceneLayer&,LevelObjectEntry&,void*),
        void* objectEditDialogCallbackParam__) {
  previewScene_.setObjectEditDialogCallback(objectEditDialogCallback__,
                                            objectEditDialogCallbackParam__);
}

void LevelEditor::setObjectUpdateCallback(
        void (*objectUpdateCallback__)(
          LevelObjectGraphicSceneLayer&,void*),
        void* objectUpdateCallbackParam__) {
  previewScene_.setObjectUpdateCallback(objectUpdateCallback__,
                                       objectUpdateCallbackParam__);
}
        
void LevelEditor::setObjectSelectionCallback(
        void (*objectSelectionCallback__)(
          LevelObjectGraphicSceneLayer&,
          LevelObjectEntryCollection::iterator,
          void*),
        void* objectSelectionCallbackParam__) {
  previewScene_.setObjectSelectionCallback(objectSelectionCallback__,
                                          objectSelectionCallbackParam__);
}

void LevelEditor::setSpawnEditDialogCallback(
        bool (*spawnEditDialogCallback__)(
          LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*),
        void* spawnEditDialogCallbackParam__) {
  previewScene_.setSpawnEditDialogCallback(spawnEditDialogCallback__,
                                           spawnEditDialogCallbackParam__);
}
  
void LevelEditor::changeMap(int levelHeaderIndex__) {
  // Get area and map num
//  AreaMapReference mapnums = mapData_.levelHeaders()
//    .areaMapNumOfIndex(levelHeaderIndex__);
  
//  areaNum_ = mapnums.areaNum();
//  mapNum_ = mapnums.mapNum();
//  levelHeaderIndex_ = levelHeaderIndex__;

  cacheVRAM(levelHeaderIndex__);
  
  // should've put these in this class
  bool bgenabled = previewScene_.bgLayerEnabled();
  bool fgenabled = previewScene_.fgLayerEnabled();
  
  previewScene_.changeMap(levelHeaderIndex__);
  
  metatilePickerScene_ = MetatilePickerLayeredGraphicScene(
                           mapData_.metatileStructures()
                             .metatileStructureSet(
                               mapData_.levelHeaders().levelHeaderByIndex(
                                 levelHeaderIndex__)
                                  .tileStructureID()),
                           metatileBehaviors_,
                           metatileWidthMaps_,
                           metatileHeightMaps_,
                           toolManager_,
                           vramCache_);
                           
  // lazy refresh of metatile picker view mode
  setLevelViewMode(levelViewMode_);
  previewScene_.setBGLayerEnabled(bgenabled);
  previewScene_.setFGLayerEnabled(fgenabled);
  metatilePickerScene_.setBGLayerEnabled(bgenabled);
  metatilePickerScene_.setFGLayerEnabled(fgenabled);
  metatilePickerScene_.setGridLayerEnabled(previewScene_.gridEnabled());
  
//  needWrapCacheRefresh_ = true;
  
//  std::cout << areaNum_ << " " << mapNum_ << " " << levelHeaderIndex_
//    << std::endl;
}
  
void LevelEditor::metatilePickerEnterMouse() {
  metatilePickerScene_.enterMouse();
}

void LevelEditor::metatilePickerExitMouse() {
  metatilePickerScene_.exitMouse();
}

void LevelEditor
    ::metatilePickerMoveMouse(int x, int y, InputEventData eventData) {
  metatilePickerScene_.moveMouse(x, y, eventData);
}

void LevelEditor
    ::metatilePickerPressMouse(int x, int y, InputEventData eventData) {
  metatilePickerScene_.pressMouse(x, y, eventData);
}
  
void LevelEditor
    ::levelEditorEnterMouse() {
  previewScene_.enterMouse();
}

void LevelEditor
    ::levelEditorExitMouse() {
  previewScene_.exitMouse();
}

void LevelEditor
    ::levelEditorMoveMouse(int x, int y, InputEventData eventData) {
  previewScene_.moveMouse(x, y, eventData);
  moveCurrentLevelSpawnsInBounds();
}

void LevelEditor
    ::levelEditorPressMouse(int x, int y, InputEventData eventData) {
  previewScene_.pressMouse(x, y, eventData);
}

void LevelEditor
    ::levelEditorDoubleClickMouse(int x, int y, InputEventData eventData) {
  previewScene_.doubleClickMouse(x, y, eventData);
}

void LevelEditor
    ::levelEditorReleaseMouse(int x, int y, InputEventData eventData) {
  previewScene_.releaseMouse(x, y, eventData);
}

void LevelEditor
    ::moveCurrentLevelSpawnsInBounds() {
  // ignore areas with no spawn points
  if (previewScene_.areaNum() > 0x0C) {
    return;
  }
  
  SpawnPointCollection& spawns
    = spawnPoints_.spawnsByMapnum(previewScene_.areaNum(),
                                  previewScene_.mapNum());
  
  for (SpawnPointCollection::iterator it = spawns.begin();
       it != spawns.end();
       ++it) {
    if (it->tailsX() < 0) {
      int target = (0) * MetatileStructure::metatileWidth;
      it->setCamX(it->camX() - (it->tailsX() - target));
      it->setTailsX(target);
    }
    else if (it->tailsX() > (previewScene_.currentLevelMetatileWidth()
                               * MetatileStructure::metatileWidth)) {
      int target = (previewScene_.currentLevelMetatileWidth() - 0)
                               * MetatileStructure::metatileWidth;
      it->setCamX(it->camX() - (it->tailsX() - target));
      it->setTailsX(target);
    }
    
    if (it->tailsY() < 0) {
      int target = (0) * MetatileStructure::metatileHeight;
      it->setCamY(it->camY() - (it->tailsY() - target));
      it->setTailsY(target);
    }
    else if (it->tailsY() > (previewScene_.currentLevelMetatileHeight()
                               * MetatileStructure::metatileHeight)) {
      int target = (previewScene_.currentLevelMetatileHeight() - 0)
                               * MetatileStructure::metatileHeight;
      it->setCamY(it->camY() - (it->tailsY() - target));
      it->setTailsY(target);
    }
  }
}
  
void LevelEditor::clearCurrentLevelObjects() {
  while (currentObjectGroup()->size()) {
    eraseObjectAtIndex(0);
  }
}

void LevelEditor::importLayout(int levelHeaderIndex__) {
  importMapLayout(levelHeaderIndex__);
  importObjectLayout(levelHeaderIndex__);
}
  
void LevelEditor::importMapLayout(int levelHeaderIndex__) {
  LevelHeader& levelHeader = previewScene_.currentLevelHeader();
                            
  LevelHeader& srcLevelHeader = levelHeaders().levelHeaderByIndex(
                                levelHeaderIndex__);
  
  MapLayout& mapLayout = mapData_.mapLayouts().mapAtIndex(
                            levelHeader.mapLayoutID());
  
  MapLayout& srcMapLayout = mapData_.mapLayouts().mapAtIndex(
                              srcLevelHeader.mapLayoutID());
  
  mapLayout = srcMapLayout;
  levelHeader.setWidth(srcLevelHeader.width());
}
  
void LevelEditor::importObjectLayout(int levelHeaderIndex__) {
  if (currentObjectGroup() == NULL) {
    return;
  }

  clearCurrentLevelObjects();
                      
  AreaMapReference mapnums = mapData_.levelHeaders()
    .areaMapNumOfIndex(levelHeaderIndex__);
  
  // areas with no layout
  if ((mapnums.areaNum() == 16) || (mapnums.areaNum() == 19)) {
    return;
  }
  
  int objectIndex
    = levelObjectEntryGroups_.indexOfMapnum(
                      mapnums.areaNum(),
                      mapnums.mapNum());
  
  LevelObjectEntryGroup& group
      = levelObjectEntryGroups_.group(objectIndex);
  
  for (LevelObjectEntryCollection::iterator it = group.begin();
       it != group.end();
       ++it) {
    appendObject(*it);
  }
}
  
bool LevelEditor::appendObject(LevelObjectEntry entry) {
  if (currentObjectGroup() == NULL) {
    return false;
  }
  
  currentObjectGroup()->addEntry(entry);
  
  return true;
}

LevelEditorTools::LevelEditorTool LevelEditor::currentTool() const {
  return toolManager_.currentTool();
}
  
void LevelEditor::changeTool(LevelEditorTools::LevelEditorTool tool) {
  toolManager_.setCurrentTool(tool);
}
  
double LevelEditor::scale() const {
  return previewScene_.scale();
}
  
void LevelEditor::setScale(double scale__) {
  previewScene_.setScale(scale__);
}
  
void LevelEditor::drawPreviewGraphic(Graphic& dst) {
//  dst.copy(levelGraphicsData_.compressedGraphic(0).toGrayscaleGraphic(16),
//          Box(0, 0, 0, 0),
//          Graphic::noTransUpdate);

//  levelGraphicsData_.compressedGraphic(0).toGrayscaleGraphic(16)
//    .scale(dst,
//           Graphic::noTransUpdate);

  previewScene_.render(dst,
                       Box(scrollX(),
                           scrollY(),
                           dst.w() / scale(),
                           dst.h() / scale()),
                       scale());

/*  if ((needWrapCacheRefresh_)
      || (wrapScrollCache_.surface().w() != (int)(dst.w() / scale()))
      || (wrapScrollCache_.surface().h() != (int)(dst.h() / scale()))) {
    wrapScrollCache_ = WrapScrollGraphic(dst.w() / scale(),
                                         dst.h() / scale());
//    std::cout << wrapScrollCache_.surface().w() << " " << dst.w() << std::endl;
    previewScene_.render(dst,
                         wrapScrollCache_,
                         Box(scrollX_,
                             scrollY_,
                             dst.w() / scale(),
                             dst.h() / scale()),
                         scale());
    needWrapCacheRefresh_ = false;
    return;
  }
  
  if (lastRenderedScrollX_ != scrollX_) {
    wrapScrollCache_.scrollInX(scrollX_ - lastRenderedScrollX_);
    
    Box scrollBox(scrollX_, scrollY_,
                  scrollX_ - lastRenderedScrollX_,
                  wrapScrollCache_.surface().h());
    // If width is negative, adjust x-position and make width positive
    if (scrollBox.w() < 0) {
      scrollBox.setX(scrollBox.x() + scrollBox.w());
      scrollBox.setW(-(scrollBox.w()));
    }
  
    // Render changed columns
    previewScene_.render(dst,
                         wrapScrollCache_,
                         scrollBox,
                         scale());
  }
  
  if (lastRenderedScrollY_ != scrollY_) {
    wrapScrollCache_.scrollInY(scrollY_ - lastRenderedScrollY_);
    
    Box scrollBox(scrollX_, scrollY_,
                  wrapScrollCache_.surface().w(),
                  scrollY_ - lastRenderedScrollY_);
    // If height is negative, adjust y-position and make height positive
    if (scrollBox.h() < 0) {
      scrollBox.setY(scrollBox.y() + scrollBox.h());
      scrollBox.setH(-(scrollBox.h()));
    }
  
    // Render changed rows
    previewScene_.render(dst,
                         wrapScrollCache_,
                         scrollBox,
                         scale());
  }
                       
  lastRenderedScrollX_ = scrollX_;
  lastRenderedScrollY_ = scrollY_; */
}

void LevelEditor::drawMetatilePickerGraphic(Graphic& dst) {
  metatilePickerScene_.render(dst,
                               Box(0, 0, 0, 0),
                               scale());
}
  
LevelObjectEntryGroup* LevelEditor::currentObjectGroup() {
  return previewScene_.currentObjectGroup();
}

void LevelEditor::selectObjectAtIndex(int index) {
  previewScene_.selectObjectAtIndex(index);
  
//  if ((toolManager_.objectEditorSingleGroupIt()->xPos())
//        > (scrollX_ + 50)) {
    setScrollX(toolManager_.objectEditorSingleGroupIt()
                 ->xPos() - (300 / scale()));
    if (scrollX() < 0) {
      setScrollX(0);
    }
    
    setScrollY(toolManager_.objectEditorSingleGroupIt()
                 ->yPos() - (300 / scale()));
    if (scrollY() < 0) {
      setScrollY(0);
    }
//  }
}

void LevelEditor::eraseObjectAtIndex(int index) {
  previewScene_.eraseObjectAtIndex(index);
}

void LevelEditor::editSelectedObject() {
  previewScene_.editSelectedObject();
}

bool LevelEditor::editAndAppendObject() {
  bool result = previewScene_.editAndAppendObject();
  
  if (result) {
    setScrollX(toolManager_.objectEditorSingleGroupIt()
                 ->xPos() - (300 / scale()));
    if (scrollX() < 0) {
      setScrollX(0);
    }
    
    setScrollY(toolManager_.objectEditorSingleGroupIt()
                 ->yPos() - (300 / scale()));
    if (scrollY() < 0) {
      setScrollY(0);
    }
  }
  
  return result;
}

void LevelEditor::refreshAllObjectVRAMOffsets() {
  previewScene_.refreshAllObjectVRAMOffsets();
}
  
int LevelEditor::currentLevelWidth() {
  return previewScene_.currentLevelMetatileWidth();
}

void LevelEditor::setCurrentLevelWidth(int width__) {
  previewScene_.setCurrentLevelMetatileWidth(width__);
}

LevelEffectsHeader& LevelEditor::currentLevelEffectsHeader() {
  return levelEffectsHeaders_.headersByMapnum(previewScene_.areaNum(),
                                              previewScene_.mapNum());
}
  
int LevelEditor::currentLevelRealWidth() {
  return (currentLevelWidth() * MetatileStructure::metatileWidth);
}

int LevelEditor::currentLevelRealHeight() {
  return (((MapLayout::dataSize + 1) / currentLevelWidth())
            * MetatileStructure::metatileHeight);
}

bool LevelEditor::currentLevelHasWarps() {
  if (previewScene_.areaNum() <= PrimaryMaps::battleFortress) {
    return true;
  }
  
  return false;
}
  
WarpDestinationCollection& LevelEditor::currentLevelWarps() {
  return warpDestinations_.warpsByMapnum(previewScene_.areaNum(),
                                         previewScene_.mapNum());
}

EditableSpawnPoints& LevelEditor::spawnPoints() {
  return spawnPoints_;
}
  
LevelEditorToolManager& LevelEditor::toolManager() {
  return toolManager_;
}
  
LevelHeaders& LevelEditor::levelHeaders() {
  return mapData_.levelHeaders();
}
  
LevelEditor::LevelViewMode LevelEditor::levelViewMode() const {
  return levelViewMode_;
}
  
void LevelEditor::setBGEnabled(bool bgEnabled__) {
  previewScene_.setBGLayerEnabled(bgEnabled__);
  metatilePickerScene_.setBGLayerEnabled(bgEnabled__);
}

void LevelEditor::setObjectsEnabled(bool objectsEnabled__) {
  previewScene_.setObjectLayerEnabled(objectsEnabled__);
}

void LevelEditor::setFGEnabled(bool fgEnabled__) {
  previewScene_.setFGLayerEnabled(fgEnabled__);
  metatilePickerScene_.setFGLayerEnabled(fgEnabled__);
}

void LevelEditor::setSpawnsEnabled(bool spawnsEnabled__) {
  previewScene_.setSpawnLayerEnabled(spawnsEnabled__);
}

void LevelEditor::setBoundsEnabled(bool boundsEnabled__) {
  previewScene_.setBoundsLayerEnabled(boundsEnabled__);
}
  
void LevelEditor::setCameraBoxEnabled(bool cameraBoxEnabled__) {
  previewScene_.setCameraBoxEnabled(cameraBoxEnabled__);
}
  
void LevelEditor::setLevelViewMode(LevelViewMode levelViewMode__) {
  levelViewMode_ = levelViewMode__;
  
  previewScene_.setBGLayerEnabled(false);
  previewScene_.setFGLayerEnabled(false);
  previewScene_.setEffectLayerEnabled(false);
  previewScene_.setVerticalSolidityLayerEnabled(false);
  previewScene_.setHorizontalSolidityLayerEnabled(false);
  metatilePickerScene_.setFGLayerEnabled(false);
  metatilePickerScene_.setBGLayerEnabled(false);
  metatilePickerScene_.setEffectLayerEnabled(false);
  metatilePickerScene_.setVerticalSolidityLayerEnabled(false);
  metatilePickerScene_.setHorizontalSolidityLayerEnabled(false);
  
  switch (levelViewMode__) {
  case LevelViewMode::viewLevelVisual:
    previewScene_.setBGLayerEnabled(true);
    previewScene_.setFGLayerEnabled(true);
    metatilePickerScene_.setFGLayerEnabled(true);
    metatilePickerScene_.setBGLayerEnabled(true);
    break;
  case LevelViewMode::viewLevelEffect:
    previewScene_.setEffectLayerEnabled(true);
    metatilePickerScene_.setEffectLayerEnabled(true);
    break;
  case LevelViewMode::viewLevelVerticalSolidity:
    previewScene_.setVerticalSolidityLayerEnabled(true);
    metatilePickerScene_.setVerticalSolidityLayerEnabled(true);
    break;
  case LevelViewMode::viewLevelHorizontalSolidity:
    previewScene_.setHorizontalSolidityLayerEnabled(true);
    metatilePickerScene_.setHorizontalSolidityLayerEnabled(true);
    break;
  default:
    break;
  }
}
  
int LevelEditor::scrollX() const {
  return previewScene_.scrollX();
}

int LevelEditor::scrollY() const {
  return previewScene_.scrollY();
}

void LevelEditor::setScrollX(int scrollX__) {
  previewScene_.setScrollX(scrollX__);
}

void LevelEditor::setScrollY(int scrollY__) {
  previewScene_.setScrollY(scrollY__);
}
  
int LevelEditor::maxScrollX() {
  return (mapData_.levelHeaders().levelHeaderByIndex(
    previewScene_.levelHeaderIndex())
      .width())
        * MetatileStructure::metatileWidth;
}

int LevelEditor::maxScrollY() {
  return (MapLayout::dataSize
    / (mapData_.levelHeaders().levelHeaderByIndex(
      previewScene_.levelHeaderIndex())
        .width())) * MetatileStructure::metatileHeight
    + MetatileStructure::metatileHeight;
}
  
bool LevelEditor::gridEnabled() const {
  return previewScene_.gridEnabled();
}

void LevelEditor::setGridEnabled(bool gridEnabled__) {
  previewScene_.setGridEnabled(gridEnabled__);
  metatilePickerScene_.setGridLayerEnabled(gridEnabled__);
}
  
int LevelEditor::cameraTopBound() {
  return previewScene_.cameraTopBound();
}

int LevelEditor::cameraBottomBound() {
  return previewScene_.cameraBottomBound();
}

int LevelEditor::cameraLeftBound() {
  return previewScene_.cameraLeftBound();
}

int LevelEditor::cameraRightBound() {
  return previewScene_.cameraRightBound();
}

void LevelEditor::setCameraTopBound(int cameraTopBound__) {
  previewScene_.setCameraTopBound(cameraTopBound__);
}

void LevelEditor::setCameraBottomBound(int cameraBottomBound__) {
  previewScene_.setCameraBottomBound(cameraBottomBound__);
}

void LevelEditor::setCameraLeftBound(int cameraLeftBound__) {
  previewScene_.setCameraLeftBound(cameraLeftBound__);
}

void LevelEditor::setCameraRightBound(int cameraRightBound__) {
  previewScene_.setCameraRightBound(cameraRightBound__);
}
  
LevelPaletteHeader& LevelEditor::currentLevelPaletteHeader() {
  return paletteHeaders_.headerByIndex(
            paletteHeaders_.indexOfMapNum(
                previewScene_.areaNum(),
                previewScene_.mapNum()));
}
  
int LevelEditor::numPalettes() {
  return palettes_.size();
}

int LevelEditor::numMetatileStructureSets() {
  return mapData_.metatileStructures().size();
}
  
int LevelEditor::currentLevelMetatileStructureIndex() {
  return previewScene_.currentLevelHeader().tileStructureID();
}

void LevelEditor::setCurrentLevelMetatileStructureIndex(int index) {
  previewScene_.currentLevelHeader().setTileStructureID(index);
}
  
std::string LevelEditor::nameOfArea(int areaNum) {
  return metadata_.areaMetadata(areaNum).name();
}
  
int LevelEditor::maxTotalObjects() {
  return levelObjectEntryGroups_.maxTotalEntries();
}
  
int LevelEditor::totalObjectCount() {
  return levelObjectEntryGroups_.totalEntries();
}
  
EditorMetadata& LevelEditor::metadata() {
  return metadata_;
}

void LevelEditor::cacheVRAM(int levelHeaderIndex) {
  AreaMapReference mapnums = mapData_.levelHeaders()
    .areaMapNumOfIndex(levelHeaderIndex);
  
  vramCache_.cacheVRAM(levelGraphicsData_,
                       paletteHeaders_,
                       palettes_,
                       mapnums.areaNum(),
                       mapnums.mapNum());
}


};
