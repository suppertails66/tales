#include "editors/LevelSpawnGraphicSceneLayer.h"
#include "gamedata/PrimaryMaps.h"
#include <iostream>

namespace Tales {


LevelSpawnGraphicSceneLayer::LevelSpawnGraphicSceneLayer(
                            LevelEditorToolManager& toolManager__,
                            SpawnPointCollection* spawns__,
                            EditableLevelGraphicsData& levelGraphicsData__,
                            EditableSpriteMappings& spriteMappings__,
                            GGPalette& palette0__,
                            GGPalette& palette1__,
                            int areaNum__)
  : toolManager_(&toolManager__),
    spawns_(spawns__),
    levelGraphicsData_(&levelGraphicsData__),
    spriteMappings_(&spriteMappings__),
    palette0_(&palette0__),
    palette1_(&palette1__),
    areaNum_(areaNum__),
    cameraBoxEnabled_(true),
    spawnEditDialogCallback_(0),
    spawnEditDialogCallbackParam_(0) {
  regenerateDisplayCaches();
}

void LevelSpawnGraphicSceneLayer::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  if (spawns_ == 0) {
    return;
  }
  
  // Draw in reverse order
//  LevelObjectEntryCollection::iterator groupIt
//    = levelObjectEntryGroups_->groupEnd(levelObjectEntryGroupIndex_);
  SpawnPointCollection::iterator groupIt
    = spawns_->end();
  ObjectDisplayCacheCollection::iterator cacheIt
    = spawnDisplayCaches_.end();
  
  if (spawnDisplayCaches_.size() <= 0) {
    return;
  }
  
  do {
    --cacheIt;
    --groupIt;

    int realX = groupIt->tailsX() - srcbox.x();
    int realY = groupIt->tailsY() - srcbox.y();
    
    int drawX = realX + cacheIt->offsetX();
    int drawY = realY + cacheIt->offsetY();
    
    dst.blit(cacheIt->graphic(),
             Box(drawX, drawY,
                 0, 0));
    
    // If object is selected, draw selection box
    switch (toolManager_->spawnEditorState()) {
    case LevelEditorTools::spawnEditorSingleSelected:
      if (groupIt == toolManager_->spawnEditorSingleGroupIt()) {
        dst.drawRectBorder(drawX, drawY,
                           cacheIt->graphic().w(), cacheIt->graphic().h(),
                           Color(0, 0, 255, Color::fullAlphaOpacity),
                           2);
      }
      break;
    default:
      break;
    }
    
    // Draw camera box
    if (cameraBoxEnabled_) {
      int realCamX = groupIt->camX() - srcbox.x();
      int realCamY = groupIt->camY() - srcbox.y();
      
      dst.drawRectBorder(realCamX + marginLeft_, realCamY + marginTop_,
                         marginRight_ - marginLeft_, marginBottom_ - marginTop_,
                         Color(255, 0, 0, Color::fullAlphaOpacity),
                         2);
    }
             
  } while (cacheIt != spawnDisplayCaches_.begin());
}
                      
bool LevelSpawnGraphicSceneLayer::cameraBoxEnabled() const {
  return cameraBoxEnabled_;
}

void LevelSpawnGraphicSceneLayer
    ::setCameraBoxEnabled(bool cameraBoxEnabled__) {
  cameraBoxEnabled_ = cameraBoxEnabled__;
}

void LevelSpawnGraphicSceneLayer::regenerateDisplayCaches() {
  spawnDisplayCaches_.clear();
  
  if (spawns_ == 0) {
    return;
  }
  
  for (SpawnPointCollection::iterator it = spawns_->begin();
       it != spawns_->end();
       ++it) {
    ObjectDisplayCache cache;
    
    // Tails standing sprite
    int spriteNum = 75;
    int mappingNum = 75;
    
    // Change to Sea Fox sprite for appropriate levels
    if ((areaNum_ == PrimaryMaps::lakeRocky)
        || (areaNum_ == PrimaryMaps::lakeCrystal)
        || (areaNum_ == PrimaryMaps::battleFortressFlight)) {
      spriteNum = 119;
      mappingNum = 119;
    }
    
    SpriteMapping mapping = spriteMappings_->spriteMapping(mappingNum);
    
    MappingAssembler::assembleMappings(
                               cache,
                               levelGraphicsData_->uncompressedGraphic(
                                 spriteNum),
                               mapping,
                               spriteMappings_->coordinateTable(
                                 mapping.coordinateTableIndex()),
                               spriteMappings_->tileIndexTable(
                                 mapping.tileIndexTableIndex()),
                               *palette1_,
                               ObjectStateInfo::left,
                               0);
    
    spawnDisplayCaches_.push_back(cache);
  }
}
                             
void LevelSpawnGraphicSceneLayer
    ::moveMouse(int realX, int realY, InputEventData eventData) {
  if (spawns_ == 0) {
    return;
  }
  
  switch (toolManager_->spawnEditorState()) {
  case LevelEditorTools::spawnEditorSingleSelected:
    handleSelectionDrag(realX, realY, eventData);
    break;
  default:
    break;
  }
}

void LevelSpawnGraphicSceneLayer
    ::pressMouse(int realX, int realY, InputEventData eventData) {
  if (spawns_ == 0) {
    return;
  }
  
  switch (toolManager_->spawnEditorState()) {
  case LevelEditorTools::spawnEditorNothingSelected:
    handleInitialClick(realX, realY, eventData);
    break;
  case LevelEditorTools::spawnEditorSingleSelected:
    handleSelectionClick(realX, realY, eventData);
    break;
  default:
    break;
  }
}

void LevelSpawnGraphicSceneLayer
    ::doubleClickMouse(int realX, int realY, InputEventData eventData) {
  if (spawns_ == 0) {
    return;
  }
  
  if (toolManager_->currentTool() != LevelEditorTools::spawnEditor) {
    return;
  }
  
  searchAndSelectOrDeselect(realX, realY);
  
  if (toolManager_->spawnEditorState()
        == LevelEditorTools::spawnEditorNothingSelected) {
    return;
  }
  
//  toolManager_->setSpawnEditorLastRealX(realX);
//  toolManager_->setSpawnEditorLastRealY(realY);
  if (spawnEditDialogCallback_ != NULL) {
    SpawnPoint newEntry = *(toolManager_->spawnEditorSingleGroupIt());
    bool result = spawnEditDialogCallback_(
                                  *this,
                                  newEntry,
                                  spawnEditDialogCallbackParam_);
    if (result) {
      *(toolManager_->spawnEditorSingleGroupIt()) = newEntry;
    }
  }
}

void LevelSpawnGraphicSceneLayer
    ::releaseMouse(int realX, int realY, InputEventData eventData) {
  if (spawns_ == 0) {
    return;
  }
  
  
}
  
void LevelSpawnGraphicSceneLayer
    ::selectSpawn(ObjectDisplayCacheCollection::iterator cacheIt,
                   SpawnPointCollection::iterator groupIt) {
  toolManager_->setCurrentTool(LevelEditorTools::spawnEditor);
  toolManager_->setSpawnEditorState(
      LevelEditorTools::spawnEditorSingleSelected);
  toolManager_->setSpawnEditorSingleGroupIt(groupIt);
  toolManager_->setSpawnEditorSingleCacheIt(cacheIt);
}

bool LevelSpawnGraphicSceneLayer
    ::pointOverlaps(int realX, int realY,
                   ObjectDisplayCacheCollection::iterator cacheIt,
                   SpawnPointCollection::iterator groupIt) {
  int objX = groupIt->tailsX();
  int objY = groupIt->tailsY();
  
  int graphicWidth = cacheIt->graphic().w();
  int graphicHeight = cacheIt->graphic().h();
  
  if (Box(objX + cacheIt->offsetX(), objY + cacheIt->offsetY(),
          graphicWidth, graphicHeight)
            .pointOverlaps(realX, realY)) {
    return true;
  }
  
  return false;
}
                     
void LevelSpawnGraphicSceneLayer
    ::handleInitialClick(int realX, int realY, InputEventData eventData) {
  if (!eventData.mouseLeftButton()) {
    return;
  }
    
  searchAndSelectOrDeselect(realX, realY);
}

void LevelSpawnGraphicSceneLayer
    ::handleSelectionClick(int realX, int realY, InputEventData eventData) {
  if (!eventData.mouseLeftButton()) {
    return;
  }
    
  searchAndSelectOrDeselect(realX, realY);
}

void LevelSpawnGraphicSceneLayer
    ::handleSelectionDrag(int realX, int realY, InputEventData eventData) {
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
  SpawnPoint& entry = *(toolManager_->spawnEditorSingleGroupIt());
  
  entry.setTailsX(entry.tailsX() + 
                    (realX - toolManager_->spawnEditorLastRealX()));
  entry.setTailsY(entry.tailsY() + 
                    (realY - toolManager_->spawnEditorLastRealY()));
  entry.setCamX(entry.camX() +
                    (realX - toolManager_->spawnEditorLastRealX()));
  entry.setCamY(entry.camY() +
                    (realY - toolManager_->spawnEditorLastRealY()));
  toolManager_->setSpawnEditorLastRealX(realX);
  toolManager_->setSpawnEditorLastRealY(realY);
}
  
void LevelSpawnGraphicSceneLayer
    ::searchAndSelectOrDeselect(int realX, int realY) {
  ObjectDisplayCacheCollection::iterator cacheIt
    = spawnDisplayCaches_.begin();
  SpawnPointCollection::iterator groupIt
    = spawns_->begin();
  
  while (cacheIt != spawnDisplayCaches_.end()) {
    if (pointOverlaps(realX, realY,
                      cacheIt,
                      groupIt)) {
      // Clicked an object: select it
      selectSpawn(cacheIt, groupIt);
      toolManager_->setSpawnEditorLastRealX(realX);
      toolManager_->setSpawnEditorLastRealY(realY);
      return;
    }
             
    ++cacheIt;
    ++groupIt;
  }
  
  // Didn't click anything: deselect
  toolManager_->setSpawnEditorState(LevelEditorTools::
                                      spawnEditorNothingSelected);
}

void LevelSpawnGraphicSceneLayer
    ::setSpawnEditDialogCallback(
        bool (*spawnEditDialogCallback__)(
          LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*),
        void* spawnEditDialogCallbackParam__) {
  spawnEditDialogCallback_ = spawnEditDialogCallback__;
  spawnEditDialogCallbackParam_ = spawnEditDialogCallbackParam__;
}
          
int LevelSpawnGraphicSceneLayer
    ::selectedSpawnNumber() {
  if (spawns_ == 0) {
    return -1;
  }
  
  int num = 0;
  for (SpawnPointCollection::iterator it = spawns_->begin();
       it != spawns_->end();
       ++it) {
    if (it == toolManager_->spawnEditorSingleGroupIt()) {
      return num;
    }
    
    ++num;
  }
    
  return -1;
}


};
