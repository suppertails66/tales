#include "editors/LevelObjectGraphicSceneLayer.h"
#include "gamedata/MetatileStructure.h"
#include "gamedata/ObjectStates.h"
#include <cstdlib>
#include <iostream>

namespace Tales {


LevelObjectGraphicSceneLayer::LevelObjectGraphicSceneLayer(
                               const VRAMCache& vramCache__,
                               const EditableSpriteMappings&
                                 spriteMappings__,
                               const WarpDestinationCollection*
                                 warpDestinationCollection__,
                               const ObjectGraphicsHeader&
                                 objectGraphicsHeader__,
                               EditableLevelGraphicsData&
                                 levelGraphicsData__,
                               const GGPalette& palette0__,
                               const GGPalette& palette1__,
                               EditableLevelObjectEntryGroups&
                                 levelObjectEntryGroups__,
                               int levelObjectEntryGroupIndex__,
                               LevelEditorToolManager& toolManager__)
  : objectEditDialogCallback_(NULL),
    objectEditDialogCallbackParam_(NULL),
    objectUpdateCallback_(NULL),
    objectUpdateCallbackParam_(NULL),
    objectSelectionCallback_(NULL),
    objectSelectionCallbackParam_(NULL),
    vramCache_(&vramCache__),
    spriteMappings_(&spriteMappings__),
    warpDestinationCollection_(warpDestinationCollection__),
    objectGraphicsHeader_(&objectGraphicsHeader__),
    levelGraphicsData_(&levelGraphicsData__),
    palette0_(&palette0__),
    palette1_(&palette1__),
    levelObjectEntryGroups_(&levelObjectEntryGroups__),
    levelObjectEntryGroupIndex_(levelObjectEntryGroupIndex__),
    toolManager_(&toolManager__) {
  regenerateObjectDisplayCache();
}
                        
void LevelObjectGraphicSceneLayer::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  if (levelObjectEntryGroupIndex_ == -1) { 
    return;
  }
  
  // Draw in reverse order
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupEnd(levelObjectEntryGroupIndex_);
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.end();
  if (levelObjectEntryGroups_->groupSize(levelObjectEntryGroupIndex_) > 0) {
    --groupIt;
    --cacheIt;
  }
  
  while (true) {
    int realX = groupIt->xPos() - srcbox.x();
    int realY = groupIt->yPos() - srcbox.y();
    
    int drawX = realX + cacheIt->offsetX();
    int drawY = realY + cacheIt->offsetY();
    
    dst.blit(cacheIt->graphic(),
             Box(drawX, drawY,
                 0, 0));
    
    // If object is selected, draw selection box
    switch (toolManager_->objectEditorState()) {
    case LevelEditorTools::objectEditorSingleSelected:
      if (groupIt == toolManager_->objectEditorSingleGroupIt()) {
        dst.drawRectBorder(drawX, drawY,
                           cacheIt->graphic().w(), cacheIt->graphic().h(),
                           Color(255, 255, 0, Color::fullAlphaOpacity),
                           2);
      }
      break;
    default:
      break;
    }
    
    if (cacheIt == objectDisplayCaches_.begin()) {
      break;
    }
             
    --cacheIt;
    --groupIt;
  }
  
  // If select-dragging, draw box around selected area
  switch (toolManager_->objectEditorState()) {
  case LevelEditorTools::objectEditorSelectingMultiple:
    dst.drawRectBorder(toolManager_->objectEditorMultipleSelectX()
                          - srcbox.x(),
                       toolManager_->objectEditorMultipleSelectY()
                          - srcbox.y(),
                       toolManager_->objectEditorMultipleSelectW()
                         * scale,
                       toolManager_->objectEditorMultipleSelectH()
                         * scale,
                       Color(255, 0, 0, Color::fullAlphaOpacity),
                       2);
    break;
  case LevelEditorTools::objectEditorMultipleSelected:
  // too laggy
//  case LevelEditorTools::objectEditorDraggingMultiple:
    {
     LevelObjectEntryCollectionIteratorCollection::iterator groupItIt
       = toolManager_->objectEditorMultipleGroupIts().end();
     ObjectDisplayCacheCollectionIteratorCollection::iterator cacheItIt
       = toolManager_->objectEditorMultipleCacheIts().end();
    do {
      --groupItIt;
      --cacheItIt;
      
      int realX = (*groupItIt)->xPos() - srcbox.x();
      int realY = (*groupItIt)->yPos() - srcbox.y();
      
      int drawX = realX + (*cacheItIt)->offsetX();
      int drawY = realY + (*cacheItIt)->offsetY();
                   
      dst.drawRectBorder(drawX, drawY,
                         (*cacheItIt)->graphic().w(),
                         (*cacheItIt)->graphic().h(),
                         Color(255, 255, 0, Color::fullAlphaOpacity),
                         2);
      
    } while (groupItIt
               != toolManager_->objectEditorMultipleGroupIts().begin());
    }
    break;
  default:
    break;
  }
}

void LevelObjectGraphicSceneLayer::generateObjectPreview(
                             ObjectDisplayCache& dst,
                             LevelObjectEntry entry) {
  switch (entry.objectTypeID()) {
  // special-case all objects that can't be drawn directly using parameter
  case ObjectTypeIDs::warp:
    generateWarpPreview(dst, entry);
    break;
  case ObjectTypeIDs::waterMine:
    generateEnemyMinePreview(dst, entry);
    break;
  case ObjectTypeIDs::waterMissileLauncher:
    generateMissileLauncherPreview(dst, entry);
    break;
  case ObjectTypeIDs::cutsceneAutomation:
    {
    Graphic test(16, 16);
    test.clear(Color(0, 0, 255, Color::fullAlphaOpacity));
    test.fillRect(7, 7, 2, 2, Color(255, 0, 0, Color::fullAlphaOpacity));
    dst.setGraphic(test);
    dst.setOffsetX(0);
    dst.setOffsetY(0);
    }
    break;
  case ObjectTypeIDs::itemPickup: // loads graphics real-time
    generateItemPickupPreview(dst, entry);
    break;
  case ObjectTypeIDs::electricField:
  case ObjectTypeIDs::electricFieldSwitch:  // alternate parameter use
    generateGenericPreview(dst,
                           entry.objectTypeID(),
                           1,
                           entry.leftTileVRAMIndex(),
                           entry.rightTileVRAMIndex(),
                           entry.xDirectionFlag());
    break;
  default:
/*    {
    Graphic test(16, 16);
    test.clear(Color(255, 0, 0, Color::fullAlphaOpacity));
    test.fillRect(7, 7, 2, 2, Color(0, 0, 255, Color::fullAlphaOpacity));
    dst.setGraphic(test);
    dst.setOffsetX(0);
    dst.setOffsetY(0);
    } */
    generateGenericPreview(dst,
                           entry.objectTypeID(),
                           entry.spawnParameter(),
                           entry.leftTileVRAMIndex(),
                           entry.rightTileVRAMIndex(),
                           entry.xDirectionFlag());
    break;
  }
}
  
void LevelObjectGraphicSceneLayer::resetSelection() {
  toolManager_->setObjectEditorState(
      LevelEditorTools::objectEditorNothingSelected);
  toolManager_->objectEditorMultipleCacheIts().clear();
  toolManager_->objectEditorMultipleGroupIts().clear();
}

void LevelObjectGraphicSceneLayer::regenerateObjectDisplayCache() {
  if (levelObjectEntryGroupIndex_ != -1) {
    objectDisplayCaches_.clear();
    for (LevelObjectEntryCollection::iterator it
           = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
         it != levelObjectEntryGroups_->groupEnd(levelObjectEntryGroupIndex_);
         it++) {
      ObjectDisplayCache cache;
      generateObjectPreview(cache, *it);
      objectDisplayCaches_.push_back(cache);
    }
  }
}
  
void LevelObjectGraphicSceneLayer::generateWarpPreview(
                         ObjectDisplayCache& dst,
                         LevelObjectEntry entry) {
  int length = warpParameterToLength(entry.spawnParameter());
  bool vertical = warpParameterIsVertical(entry.spawnParameter());
  
  int height = 0x10;
  int width = 0x10;
  dst.setOffsetX(-0x08);
  dst.setOffsetY(-0x08);
  
  if (vertical) {
    // upward from origin
    height = length;
    dst.setOffsetY(-(length - 0x10));
  }
  else {
    // centered about origin?
    width = length * 2;
    dst.setOffsetX(-length);
//    dst.setOffsetY(-0x10);
  }
  
  Graphic test(width, height);
  test.clear(Color(128, 128, 255, Color::fullAlphaOpacity));
  dst.setGraphic(test);
}
  
void LevelObjectGraphicSceneLayer::generateMissileLauncherPreview(
                         ObjectDisplayCache& dst,
                         LevelObjectEntry entry) {
  int numMetatiles = entry.spawnParameter() & 0x0F;
  int slope = (entry.spawnParameter() & 0x70) >> 4;
  bool facingRight = (entry.spawnParameter() & 0x80) != 0;
  
  int width = MetatileStructure::metatileWidth;
  int height = MetatileStructure::metatileHeight;
  switch (slope) {
  // top-right to bottom-left
  case 0:
  default:
    width *= numMetatiles;
    height *= numMetatiles;
    dst.setOffsetX(-width + MetatileStructure::metatileWidth);
    dst.setOffsetY(MetatileStructure::metatileHeight / 2);
    break;
  // vertical
  case 1:
    height *= numMetatiles;
    dst.setOffsetX(0);
    dst.setOffsetY(MetatileStructure::metatileHeight / 2);
    break;
  // top-left to bottom-right
  case 2:
    width *= numMetatiles;
    height *= numMetatiles;
    dst.setOffsetX(0);
    dst.setOffsetY(MetatileStructure::metatileHeight / 2);
    break;
  }
  
  if (facingRight) {
    dst.setOffsetX(dst.offsetX() - MetatileStructure::metatileWidth);
  }
  
  if ((width <= 0) || (height <= 0)) {
    return;
  }
  
  Graphic preview(width, height);
  
  for (int i = 0; i < numMetatiles; i++) {
    switch (slope) {
    // top-right to bottom-left
    case 0:
    default:
      preview.fillRect(preview.w() - ((i + 1) * MetatileStructure::metatileWidth)
                         + 0x04,
                       ((i) * MetatileStructure::metatileHeight)
                         + 0x02,
                       MetatileStructure::metatileWidth - 0x08,
                       MetatileStructure::metatileHeight - 0x08,
                       Color(0, 255, 0, Color::fullAlphaOpacity));
      break;
    // vertical
    case 1:
      preview.fillRect(0
                         + 0x04,
                       ((i) * MetatileStructure::metatileHeight)
                         + 0x02,
                       MetatileStructure::metatileWidth - 0x08,
                       MetatileStructure::metatileHeight - 0x08,
                       Color(0, 255, 0, Color::fullAlphaOpacity));
      break;
    // top-left to bottom-right
    case 2:
      preview.fillRect(((i) * MetatileStructure::metatileWidth)
                         + 0x04,
                       ((i) * MetatileStructure::metatileHeight)
                         + 0x02,
                       MetatileStructure::metatileWidth - 0x08,
                       MetatileStructure::metatileHeight - 0x08,
                       Color(0, 255, 0, Color::fullAlphaOpacity));
      break;
    }
  }
  
  dst.setGraphic(preview);
}
                           
void LevelObjectGraphicSceneLayer::generateItemPickupPreview(
                         ObjectDisplayCache& dst,
                         LevelObjectEntry entry) {
  // item pickup mapping
  SpriteMapping spriteMapping = spriteMappings_->spriteMapping(
                                    238);
  SpriteMappingCoordinateTable coordinateTable
    = spriteMappings_->coordinateTable(spriteMapping.coordinateTableIndex());
  SpriteMappingTileIndexTable tileIndexTable
    = spriteMappings_->tileIndexTable(spriteMapping.tileIndexTableIndex());
  
  // base index for regular items
  int baseIndex = 170 + entry.spawnParameter();
  
  // chaos emeralds
  switch (entry.spawnParameter()) {
  case 32:
    baseIndex = 223;
    break;
  case 33:
    baseIndex = 220;
    break;
  case 34:
    baseIndex = 224;
    break;
  case 35:
    baseIndex = 222;
    break;
  case 36:
    baseIndex = 221;
    break;
  case 37:
    baseIndex = 225;
    break;
  default:
    break;
  }
  
  GGTileSet& tiles = levelGraphicsData_->uncompressedGraphic(baseIndex);
  
  Box dimensions = computeDimensionsOfMapping(coordinateTable);
  
  Graphic graphic(dimensions.w(), dimensions.h());
  graphic.clear();
  
  int baseX = dimensions.x();
  int baseY = dimensions.y();
  
  for (int i = 0; i < tileIndexTable.size(); i++) {
    if (i >= coordinateTable.size()) {
      break;
    }
  
    // uh?
    int tileIndex = tileIndexTable.tileIndex(i) - 252;
    
    Graphic g(tiles[tileIndex],
              *palette1_,
              Graphic::tileTrans);
    Graphic g2(tiles[tileIndex + 1],
              *palette1_,
              Graphic::tileTrans);
    
    graphic.copy(g,
                 Box(baseX + coordinateTable.entry(i).offsetX(),
                            baseY + coordinateTable.entry(i).offsetY(),
                            GGTile::width,
                            GGTile::height),
                 Graphic::noTransUpdate);
                 
    graphic.copy(g2,
                 Box(baseX + coordinateTable.entry(i).offsetX(),
                            baseY + coordinateTable.entry(i).offsetY()
                              + GGTile::height,
                            GGTile::width,
                            GGTile::height),
                 Graphic::noTransUpdate);
    
    // first sprite
/*    vramCache_->copyTile(graphic,
                        Box(baseX + coordinateTable.entry(i).offsetX(),
                            baseY + coordinateTable.entry(i).offsetY(),
                            GGTile::width,
                            GGTile::height),
                        tileIndex,
                        VRAMCache::flipNone,
                        Graphic::noTransUpdate);
    
    // second sprite (8x16 mode)
    vramCache_->copyTile(graphic,
                        Box(baseX + coordinateTable.entry(i).offsetX(),
                            baseY + coordinateTable.entry(i).offsetY()
                              + GGTile::height,
                            GGTile::width,
                            GGTile::height),
                        tileIndex + 1,
                        VRAMCache::flipNone,
                        Graphic::noTransUpdate); */
                        
  }
  
  graphic.regenerateTransparencyModel();
  
  dst.setGraphic(graphic);
  dst.setOffsetX(spriteMapping.offsetX() - baseX);
  dst.setOffsetY(spriteMapping.offsetY() - baseY
    + (MetatileStructure::metatileHeight)
    + (MetatileStructure::metatileHeight / 8));
}
  
void LevelObjectGraphicSceneLayer::generateGenericPreview(
                            ObjectDisplayCache& dst,
                            int objNum,
                            int stateNum,
                            int leftTileIndex,
                            int rightTileIndex,
                            LevelObjectEntry::XDirectionFlag
                              facingFlag) {
  ObjectStateInfo stateInfo = ObjectStates
      ::findObjectStateInfo(objNum, stateNum);
  
  if (stateInfo.previewMappingIndex == -1) {
//    std::cerr << objNum << " " << stateNum << std::endl;
    return;
  }
    
  ObjectStateInfo::FacingDirection realdir
    = ObjectStateInfo::left;
  if (stateInfo.facingDirection == ObjectStateInfo::left) {
    realdir = ObjectStateInfo::left;
  }
  else if (stateInfo.facingDirection == ObjectStateInfo::right) {
    realdir = ObjectStateInfo::right;
  }
  else {
    realdir = ObjectStateInfo::left;
    // Object facing flag is extremely unreliable, so we use it
    // as a last resort
/*    if (facingFlag == LevelObjectEntry::left) {
      realdir = ObjectStateInfo::left;
    }
    else {
      realdir = ObjectStateInfo::right;
    } */
  }
  
  SpriteMapping spriteMapping = spriteMappings_->spriteMapping(
                                    stateInfo.previewMappingIndex);
  
  SpriteMappingCoordinateTable coordinateTable
    = spriteMappings_->coordinateTable(spriteMapping.coordinateTableIndex());
  SpriteMappingTileIndexTable tileIndexTable
    = spriteMappings_->tileIndexTable(spriteMapping.tileIndexTableIndex());
  
  if (realdir == ObjectStateInfo::right) {
    coordinateTable
      = spriteMappings_->flipCoordinateTable(
          spriteMapping.coordinateTableIndex());
  }
  
  Box dimensions = computeDimensionsOfMapping(coordinateTable);
  
//  if ((dimensions.w() <= 0) || (dimensions.h() <= 0)) {
//    return;
//  }
  
  Graphic graphic(dimensions.w(), dimensions.h());
  graphic.clear();
  
//  std::cout << width << " " << height << std::endl;
    
  int baseX = dimensions.x();
  int baseY = dimensions.y();
  
//  std::cout << tileIndexTable.size() << std::endl;
  
  for (int i = 0; i < tileIndexTable.size(); i++) {
    if (i >= coordinateTable.size()) {
      break;
    }
  
    int tileIndex = tileIndexTable.tileIndex(i);
    switch (realdir) {
    case ObjectStateInfo::left:
    default:
      tileIndex += leftTileIndex;
      break;
    case ObjectStateInfo::right:
      tileIndex += rightTileIndex;
      break;
    }
    
    // first sprite
    vramCache_->copyTile(graphic,
                        Box(baseX + coordinateTable.entry(i).offsetX(),
                            baseY + coordinateTable.entry(i).offsetY(),
                            GGTile::width,
                            GGTile::height),
                        tileIndex,
                        VRAMCache::flipNone,
                        Graphic::noTransUpdate);
    
    // second sprite (8x16 mode)
    vramCache_->copyTile(graphic,
                        Box(baseX + coordinateTable.entry(i).offsetX(),
                            baseY + coordinateTable.entry(i).offsetY()
                              + GGTile::height,
                            GGTile::width,
                            GGTile::height),
                        tileIndex + 1,
                        VRAMCache::flipNone,
                        Graphic::noTransUpdate);
                        
  }
  
  graphic.regenerateTransparencyModel();
  
  dst.setGraphic(graphic);
  dst.setOffsetX(spriteMapping.offsetX() - baseX);
  dst.setOffsetY(spriteMapping.offsetY() - baseY
    + (MetatileStructure::metatileHeight)
    + (MetatileStructure::metatileHeight / 8));
    
  switch (realdir) {
  case ObjectStateInfo::left:
  default:
    break;
  case ObjectStateInfo::right:
    dst.setOffsetX(-spriteMapping.offsetX() - baseX);
    break;
  }
}
  
int LevelObjectGraphicSceneLayer
    ::computeWidthOfMapping(SpriteMappingCoordinateTable coordinateTable) {
  int minimum = 0;
  int maximum = 0;
  for (int i = 0; i < coordinateTable.size(); i++) {
    SpriteMappingCoordinateTableEntry entry
      = coordinateTable.entry(i);
    if (entry.offsetX() < minimum) {
      minimum = coordinateTable.entry(i).offsetX();
    }
    else if (entry.offsetX() > maximum + GGTile::width) {
      maximum = coordinateTable.entry(i).offsetX() + GGTile::width;
    }
  }
  
  return maximum - minimum;
}

int LevelObjectGraphicSceneLayer
    ::computeHeightOfMapping(SpriteMappingCoordinateTable coordinateTable) {
  int minimum = 0;
  int maximum = 0;
  for (int i = 0; i < coordinateTable.size(); i++) {
    SpriteMappingCoordinateTableEntry entry
      = coordinateTable.entry(i);
    if (entry.offsetY() < minimum) {
      minimum = coordinateTable.entry(i).offsetY();
    }
    else if (entry.offsetY() > maximum + GGTile::height) {
      maximum = coordinateTable.entry(i).offsetY() + GGTile::height;
    }
  }
  
  return maximum - minimum;
}

Box LevelObjectGraphicSceneLayer::computeDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable) {
  Box result(0, 0, 0, 0);
  
  int minX = 0;
  int maxX = 0;
  int minY = 0;
  int maxY = 0;
  
  for (int i = 0; i < coordinateTable.size(); i++) {
    SpriteMappingCoordinateTableEntry entry
      = coordinateTable.entry(i);
    
    if (entry.offsetX() < minX) {
      minX = coordinateTable.entry(i).offsetX();
    }
    
    if ((entry.offsetX() + GGTile::width) > maxX) {
      maxX = coordinateTable.entry(i).offsetX() + GGTile::width;
    }
    
    if (entry.offsetY() < minY) {
      minY = coordinateTable.entry(i).offsetY();
    }
    
    if ((entry.offsetY() + GGTile::height) > maxY) {
      maxY = coordinateTable.entry(i).offsetY() + GGTile::height;
    }
  }
  
  result.setX(-minX);
  result.setY(-minY);
  result.setW(maxX - minX);
  result.setH(maxY - minY);
  
  return result;
}
    
int LevelObjectGraphicSceneLayer::findObjectGraphic(int index,
                                                    bool wantFlipped) {
  int lastReg = 0;
  int lastFlipped = 0;
  bool foundReg = false;
  bool foundFlipped = false;
  for (int i = 0; i < objectGraphicsHeader_->size(); i++) {
    ObjectGraphicSubheader subheader = objectGraphicsHeader_->subheader(i);
    if (subheader.objectGraphicIndex() == index) {
      if (subheader.substitutionOption() == ObjectGraphicSubheader
                                              ::substitutionEnabled) {
        lastFlipped = subheader.tileWriteIndex();
        foundFlipped = true;
      }
      else {
        lastReg = subheader.tileWriteIndex();
        foundReg = true;
      }
    }
  }
  
  if (wantFlipped && foundFlipped) {
    return lastFlipped;
  }
  else if ((!wantFlipped) && foundReg) {
    return lastReg;
  }
  else {
    return -1;
  }
/*  else if (wantFlipped && foundReg) {
    return lastReg;
  }
  else {
    return lastFlipped;
  } */
}

void LevelObjectGraphicSceneLayer::refreshGraphicVRAMOffsets(
            LevelObjectEntry& entry,
            ObjectGraphicInfo graphicInfo) {
  // special-case item pickup (always 86)
  if (entry.objectTypeID() == ObjectTypeIDs::itemPickup) {
    entry.setLeftTileVRAMIndex(86);
    entry.setRightTileVRAMIndex(86);
    return;
  }
            
  int newLeftIndex = findObjectGraphic(graphicInfo.leftGraphicID,
                                       false)
                           + graphicInfo.offset;
  int newRightIndex = 0;
  if (graphicInfo.leftGraphicID != graphicInfo.rightGraphicID) {
    newRightIndex = findObjectGraphic(graphicInfo.rightGraphicID,
                                       false)
                           + graphicInfo.offset;
  }
  else {
    newRightIndex = findObjectGraphic(graphicInfo.leftGraphicID,
                                      true)
                           + graphicInfo.offset;
  }
  
  if (newLeftIndex != -1) {
    entry.setLeftTileVRAMIndex(newLeftIndex);
  }
  
  if (newRightIndex != -1) {
    entry.setRightTileVRAMIndex(newRightIndex);
  }
}

void LevelObjectGraphicSceneLayer::refreshAllGraphicVRAMOffsets() {
  // deselect to avoid cache iterator invalidation
  toolManager_->setObjectEditorState(LevelEditorTools
                                      ::objectEditorNothingSelected);

  for (LevelObjectEntryCollection::iterator groupIt
        = levelObjectEntryGroups_
            ->groupBegin(levelObjectEntryGroupIndex_);
       groupIt != levelObjectEntryGroups_
            ->groupEnd(levelObjectEntryGroupIndex_);
       groupIt++) {
    ObjectGraphicInfo graphicInfo = ObjectToGraphics::objectToGraphics(
      groupIt->objectTypeID());
    
    if (graphicInfo.graphicCompressionType 
          == GraphicCompressionTypes::uncompressed) {
      continue;
    }
    
    refreshGraphicVRAMOffsets(*groupIt, graphicInfo);
  }
  
  regenerateObjectDisplayCache();
}
  
void LevelObjectGraphicSceneLayer::generateEnemyMinePreview(
                         ObjectDisplayCache& dst,
                         LevelObjectEntry entry) {
  if (entry.spawnParameter() == 0xFF) {
    // draw passive mine graphic?
    generateGenericPreview(dst,
                           entry.objectTypeID(),
                           1,
                           entry.leftTileVRAMIndex(),
                           entry.rightTileVRAMIndex(),
                           entry.xDirectionFlag());
    return;
  }
  
  if ((entry.spawnParameter() & 0x80) == 0) {
    // draw passive mine graphic
    generateGenericPreview(dst,
                           entry.objectTypeID(),
                           1,
                           entry.leftTileVRAMIndex(),
                           entry.rightTileVRAMIndex(),
                           entry.xDirectionFlag());
    return;
  }
  
  int numMetatiles = entry.spawnParameter() & 0x0F;
  int slope = (entry.spawnParameter() & 0x70) >> 4;
  
  int width = MetatileStructure::metatileWidth;
  int height = MetatileStructure::metatileHeight;
  switch (slope) {
  // top-left to bottom-right
  case 0:
  default:
    width *= numMetatiles;
    height *= numMetatiles;
    dst.setOffsetX(MetatileStructure::metatileWidth / 2);
    dst.setOffsetY(MetatileStructure::metatileHeight
            + 0x02);
    break;
  // horizontal
  case 1:
    width *= numMetatiles;
    dst.setOffsetX(MetatileStructure::metatileWidth / 2);
    dst.setOffsetY(0
            + 0x02);
    break;
  // bottom-left to top-right
  case 2:
    width *= numMetatiles;
    height *= numMetatiles;
    dst.setOffsetX(MetatileStructure::metatileWidth / 2);
    dst.setOffsetY(-height
            + 0x02);
    break;
  }
  
  if ((width <= 0) || (height <= 0)) {
    return;
  }
  
  Graphic preview(width, height);
  
  for (int i = 0; i < numMetatiles; i++) {
    switch (slope) {
    // top-left to bottom-right
    case 0:
    default:
      preview.fillRect(((i) * MetatileStructure::metatileWidth)
                         + 0x04,
                       ((i) * MetatileStructure::metatileHeight)
                         + 0x02,
                       MetatileStructure::metatileWidth - 0x08,
                       MetatileStructure::metatileHeight - 0x08,
                       Color(0, 255, 0, Color::fullAlphaOpacity));
      break;
    // horizontal
    case 1:
      preview.fillRect(((i) * MetatileStructure::metatileWidth)
                         + 0x04,
                       0
                         + 0x02,
                       MetatileStructure::metatileWidth - 0x08,
                       MetatileStructure::metatileHeight - 0x08,
                       Color(0, 255, 0, Color::fullAlphaOpacity));
      break;
    // bottom-left to top-right
    case 2:
      preview.fillRect(((i) * MetatileStructure::metatileWidth)
                         + 0x04,
                       preview.h()
                         - ((i + 1) * MetatileStructure::metatileHeight)
                         + 0x02,
                       MetatileStructure::metatileWidth - 0x08,
                       MetatileStructure::metatileHeight - 0x08,
                       Color(0, 255, 0, Color::fullAlphaOpacity));
      break;
    }
  }
  
  dst.setGraphic(preview);
}
                           
void LevelObjectGraphicSceneLayer::setObjectEditDialogCallback(
          bool (*objectEditDialogCallback__)(
            LevelObjectGraphicSceneLayer&,LevelObjectEntry&,void*),
          void* objectEditDialogCallbackParam__) {
  objectEditDialogCallback_ = objectEditDialogCallback__;
  objectEditDialogCallbackParam_ = objectEditDialogCallbackParam__;
}

void LevelObjectGraphicSceneLayer::setObjectUpdateCallback(
        void (*objectUpdateCallback__)(
          LevelObjectGraphicSceneLayer&,void*),
        void* objectUpdateCallbackParam__) {
  objectUpdateCallback_ = objectUpdateCallback__;
  objectUpdateCallbackParam_ = objectUpdateCallbackParam__;
}
        
void LevelObjectGraphicSceneLayer::setObjectSelectionCallback(
        void (*objectSelectionCallback__)(
          LevelObjectGraphicSceneLayer&,
          LevelObjectEntryCollection::iterator,
          void*),
        void* objectSelectionCallbackParam__) {
  objectSelectionCallback_ = objectSelectionCallback__;
  objectSelectionCallbackParam_ = objectSelectionCallbackParam__;
}
          
const WarpDestinationCollection* LevelObjectGraphicSceneLayer
    ::warpDestinationCollection() const {
  return warpDestinationCollection_;
}
  
LevelObjectEntryGroup* LevelObjectGraphicSceneLayer
    ::currentGroup() {
  if (levelObjectEntryGroupIndex_ == -1) {
    return 0;
  }
  else {
    return &(levelObjectEntryGroups_->group(levelObjectEntryGroupIndex_));
  }
}

ObjectDisplayCacheCollection::iterator LevelObjectGraphicSceneLayer
    ::findCache(int index) {
  ObjectDisplayCacheCollection::iterator it = objectDisplayCaches_.begin();
  for (int i = 0; i < index; i++ ) {
    ++it;
  }
  return it;
}

void LevelObjectGraphicSceneLayer::eraseObjectAtIndex(int index) {
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.begin();
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
    
  for (int i = 0; i < index; i++) {
    ++cacheIt;
    ++groupIt;
  }
  
  // Clear selection (iterators may be invalidated)
//  toolManager_->setCurrentTool(LevelEditorTools::objectEditor);
  eraseObject(cacheIt,
              groupIt);
}

void LevelObjectGraphicSceneLayer::eraseObject(
                 ObjectDisplayCacheCollection::iterator cacheIt,
                 LevelObjectEntryCollection::iterator groupIt) {
  toolManager_->setObjectEditorState(
      LevelEditorTools::objectEditorNothingSelected);
  
  objectDisplayCaches_.erase(cacheIt);
  levelObjectEntryGroups_->eraseEntry(levelObjectEntryGroupIndex_,
                                      groupIt);
  regenerateObjectDisplayCache();
  
  if (objectUpdateCallback_ != NULL) {
    objectUpdateCallback_(*this, objectUpdateCallbackParam_);
  }
}

void LevelObjectGraphicSceneLayer::selectObjectAtIndex(int index) {
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.begin();
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
    
  for (int i = 0; i < index; i++) {
    ++cacheIt;
    ++groupIt;
  }
  
  selectObject(cacheIt, groupIt);
}

void LevelObjectGraphicSceneLayer::editSelectedObject() {
  if (objectEditDialogCallback_ != NULL) {
    LevelObjectEntry newEntry = *(toolManager_->objectEditorSingleGroupIt());
    bool result = objectEditDialogCallback_(
                                  *this,
                                  newEntry,
                                  objectEditDialogCallbackParam_);
    if (result) {
      *(toolManager_->objectEditorSingleGroupIt()) = newEntry;
      
      if (objectUpdateCallback_ != NULL) {
        objectUpdateCallback_(*this, objectUpdateCallbackParam_);
      }
    }
    
    regenerateObjectDisplayCache();
    
    ObjectDisplayCacheCollection::iterator cacheIt
      = objectDisplayCaches_.begin();
    LevelObjectEntryCollection::iterator groupIt
      = levelObjectEntryGroups_->groupBegin(
          levelObjectEntryGroupIndex_);
    
    while (groupIt != toolManager_->objectEditorSingleGroupIt()) {
      ++cacheIt;
      ++groupIt;
    }
    
    selectObject(cacheIt,
                 groupIt);
  }
}

bool LevelObjectGraphicSceneLayer::editAndAppendObject() {
  bool result = false;
  if (objectEditDialogCallback_ != NULL) {
    LevelObjectEntry newEntry(ObjectTypeIDs::flyingMechDuck,
                              100, 100,
                              LevelObjectEntry::right,
                              LevelObjectEntry::notBlinking,
                              LevelObjectEntry::visible,
                              1,
                              0, 0);
    result = objectEditDialogCallback_(
                                  *this,
                                  newEntry,
                                  objectEditDialogCallbackParam_);
                                  
    if (result) {
      appendObject(newEntry);
    }
    else {
      
    }
//    *(toolManager_->objectEditorSingleGroupIt()) = newEntry;
    
    regenerateObjectDisplayCache();
  }
  
  return result;
}

bool LevelObjectGraphicSceneLayer::appendObject(LevelObjectEntry newObject) {
  // Can't add new objects if max number reached
  if (levelObjectEntryGroups_->groupSize(levelObjectEntryGroupIndex_)
        == LevelObjectEntryGroup::maxGroupSize) {
    return false;
  }
  
  levelObjectEntryGroups_->addEntry(levelObjectEntryGroupIndex_,
                                    newObject);
  ObjectDisplayCache newCache;
  generateObjectPreview(newCache,
                        newObject);
  objectDisplayCaches_.push_back(newCache);
  
  if (objectUpdateCallback_ != NULL) {
    objectUpdateCallback_(*this, objectUpdateCallbackParam_);
  }
  
  selectObject(--(objectDisplayCaches_.end()),
               --(levelObjectEntryGroups_->groupEnd(
                    levelObjectEntryGroupIndex_)));
  
  return true;
}

void LevelObjectGraphicSceneLayer::selectObject(
                  ObjectDisplayCacheCollection::iterator cacheIt,
                  LevelObjectEntryCollection::iterator groupIt) {
  toolManager_->setCurrentTool(LevelEditorTools::objectEditor);
  toolManager_->setObjectEditorState(
      LevelEditorTools::objectEditorSingleSelected);
  toolManager_->setObjectEditorSingleGroupIt(groupIt);
  toolManager_->setObjectEditorSingleCacheIt(cacheIt);
  
  if (objectSelectionCallback_ != NULL) {
    objectSelectionCallback_(*this, groupIt, objectSelectionCallbackParam_);
  }
}

/*LevelObjectEntryCollection::iterator LevelObjectGraphicSceneLayer
    ::currentGroupBegin() {
  return levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
}
  
LevelObjectEntryCollection::iterator LevelObjectGraphicSceneLayer
    ::currentGroupEnd() {
  return levelObjectEntryGroups_->groupEnd(levelObjectEntryGroupIndex_);
} */
                             
void LevelObjectGraphicSceneLayer
    ::moveMouse(int realX, int realY, InputEventData eventData) {
  switch (toolManager_->objectEditorState()) {
  case LevelEditorTools::objectEditorNothingSelected:
    break;
  case LevelEditorTools::objectEditorSingleSelected:
  case LevelEditorTools::objectEditorDraggingSingle:
    handleSelectionDrag(realX, realY, eventData);
    break;
  case LevelEditorTools::objectEditorMultipleSelected:
    break;
  case LevelEditorTools::objectEditorSelectingMultiple:
    handleMultipleSelectionPreDrag(realX, realY, eventData);
    break;
  case LevelEditorTools::objectEditorDraggingMultiple:
    handleMultipleSelectionDrag(realX, realY, eventData);
    break;
  default:
    break;
  }
}

void LevelObjectGraphicSceneLayer
    ::pressMouse(int realX, int realY, InputEventData eventData) {
  switch (toolManager_->objectEditorState()) {
  case LevelEditorTools::objectEditorNothingSelected:
    handleInitialClick(realX, realY, eventData);
    break;
  case LevelEditorTools::objectEditorSingleSelected:
    handleSelectionClick(realX, realY, eventData);
    break;
  case LevelEditorTools::objectEditorMultipleSelected:
    handleMultipleSelectionClick(realX, realY, eventData);
    break;
  case LevelEditorTools::objectEditorSelectingMultiple:
    break;
  case LevelEditorTools::objectEditorDraggingSingle:
    break;
  case LevelEditorTools::objectEditorDraggingMultiple:
    break;
  default:
    break;
  }
}

void LevelObjectGraphicSceneLayer
    ::doubleClickMouse(int realX, int realY, InputEventData eventData) {
  if (toolManager_->currentTool() != LevelEditorTools::objectEditor) {
    return;
  }
    
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.begin();
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
  
  while (cacheIt != objectDisplayCaches_.end()) {
    if (pointOverlaps(realX, realY,
                      cacheIt,
                      groupIt)) {
      // Clicked an object: select it and open edit dialog
      selectObject(cacheIt, groupIt);
      toolManager_->setObjectEditorLastRealX(realX);
      toolManager_->setObjectEditorLastRealY(realY);
      if (objectEditDialogCallback_ != NULL) {
        LevelObjectEntry newEntry = *groupIt;
        bool result = objectEditDialogCallback_(
                                      *this,
                                      newEntry,
                                      objectEditDialogCallbackParam_);
        if (result) {
          *groupIt = newEntry;
  
          if (objectUpdateCallback_ != NULL) {
            objectUpdateCallback_(*this,
                                  objectUpdateCallbackParam_);
          }
          
          selectObject(cacheIt, groupIt);
        }
        
        regenerateObjectDisplayCache();
      }
      return;
    }
             
    ++cacheIt;
    ++groupIt;
  }
  
  // Didn't click anything: deselect
  toolManager_->setObjectEditorState(LevelEditorTools::
                                      objectEditorNothingSelected);
}

void LevelObjectGraphicSceneLayer
    ::releaseMouse(int realX, int realY, InputEventData eventData) {
  switch (toolManager_->objectEditorState()) {
  case LevelEditorTools::objectEditorSelectingMultiple:
    handleMultipleSelectionPreRelease(
      realX, realY, eventData);
    break;
  case LevelEditorTools::objectEditorDraggingSingle:
    toolManager_->setObjectEditorState(
        LevelEditorTools::objectEditorSingleSelected);
    break;
  case LevelEditorTools::objectEditorDraggingMultiple:
    toolManager_->setObjectEditorState(
        LevelEditorTools::objectEditorMultipleSelected);
    break;
  default:
    break;
  }
}
                     
void LevelObjectGraphicSceneLayer
    ::handleInitialClick(int realX, int realY, InputEventData eventData) {
  if (!(eventData.mouseLeftButton()
           || eventData.mouseMiddleButton())) {
    return;
  }
  
  toolManager_->setCurrentToolNoReset(
      LevelEditorTools::objectEditor);
    
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.begin();
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
  
  while (cacheIt != objectDisplayCaches_.end()) {
    if (pointOverlaps(realX, realY,
                      cacheIt,
                      groupIt)) {
      if (eventData.mouseMiddleButton()) {
        // Delete object
        eraseObject(cacheIt, groupIt);
        return;
      }
      else if (eventData.control()) {
        // Clone object
        if (appendObject(*groupIt)) {
          toolManager_->setObjectEditorLastRealX(realX);
          toolManager_->setObjectEditorLastRealY(realY);
          regenerateObjectDisplayCache();
          selectObject(--(objectDisplayCaches_.end()),
                       --(levelObjectEntryGroups_
                           ->groupEnd(levelObjectEntryGroupIndex_)));
        }
        return;
      }
      else {
        // Clicked an object: select it and return
        selectObject(cacheIt, groupIt);
        toolManager_->setObjectEditorLastRealX(realX);
        toolManager_->setObjectEditorLastRealY(realY);
        toolManager_->setObjectEditorState(
            LevelEditorTools::objectEditorDraggingSingle);
        return;
      }
    }
             
    ++cacheIt;
    ++groupIt;
  }
  
  // Clicked empty spot: begin drag-select
  toolManager_->setObjectEditorState(
      LevelEditorTools::objectEditorSelectingMultiple);
  toolManager_->setObjectEditorMultipleSelectX(realX);
  toolManager_->setObjectEditorMultipleSelectY(realY);
  toolManager_->setObjectEditorMultipleSelectW(0);
  toolManager_->setObjectEditorMultipleSelectH(0);
  
}

void LevelObjectGraphicSceneLayer
    ::handleSelectionClick(int realX, int realY, InputEventData eventData) {
  if (!(eventData.mouseLeftButton()
           || eventData.mouseMiddleButton())) {
    return;
  }
    
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.begin();
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
  
  while (cacheIt != objectDisplayCaches_.end()) {
    if (pointOverlaps(realX, realY,
                      cacheIt,
                      groupIt)) {
      
      if (eventData.mouseMiddleButton()) {
        // Delete object
        eraseObject(cacheIt, groupIt);
        return;
      }
      else if (eventData.control()) {
        // Clone object
        if (appendObject(*groupIt)) {
          toolManager_->setObjectEditorLastRealX(realX);
          toolManager_->setObjectEditorLastRealY(realY);
          regenerateObjectDisplayCache();
          selectObject(--(objectDisplayCaches_.end()),
                       --(levelObjectEntryGroups_
                           ->groupEnd(levelObjectEntryGroupIndex_)));
        }
        return;
      }
      else {
        // Clicked an object: select it and return
        selectObject(cacheIt, groupIt);
        toolManager_->setObjectEditorLastRealX(realX);
        toolManager_->setObjectEditorLastRealY(realY);
        
        toolManager_->setObjectEditorState(
            LevelEditorTools::objectEditorDraggingSingle);
        return;
      }
    }
             
    ++cacheIt;
    ++groupIt;
  }
  
  // Didn't click anything: deselect
  toolManager_->setObjectEditorState(LevelEditorTools::
                                      objectEditorNothingSelected);
  handleInitialClick(realX, realY, eventData);
}

void LevelObjectGraphicSceneLayer::handleMultipleSelectionClick(
    int realX, int realY, InputEventData eventData) {
    
  LevelObjectEntryCollectionIteratorCollection::iterator groupItIt
      = toolManager_->objectEditorMultipleGroupIts().end();
  ObjectDisplayCacheCollectionIteratorCollection::iterator cacheItIt
      = toolManager_->objectEditorMultipleCacheIts().end();
  do {
    --groupItIt;
    --cacheItIt;
    
    if (pointOverlaps(realX, realY,
                      *(cacheItIt),
                      *(groupItIt))) {
      toolManager_->setObjectEditorMultipleLastRealX(realX);
      toolManager_->setObjectEditorMultipleLastRealY(realY);
      toolManager_->setObjectEditorState(LevelEditorTools::
                                          objectEditorDraggingMultiple);
      return;
    }
    
  } while (groupItIt
             != toolManager_->objectEditorMultipleGroupIts().begin());
    
  // Nothing in selection clicked: return to initial state
  toolManager_->setObjectEditorState(LevelEditorTools::
                                      objectEditorNothingSelected);
  handleInitialClick(realX, realY, eventData);
}

void LevelObjectGraphicSceneLayer
    ::handleSelectionDrag(int realX, int realY, InputEventData eventData) {
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
  toolManager_->setObjectEditorState(
      LevelEditorTools::objectEditorDraggingSingle);
  
  LevelObjectEntry& entry = *(toolManager_->objectEditorSingleGroupIt());
  
  entry.setXPos(entry.xPos() + 
                    (realX - toolManager_->objectEditorLastRealX()));
  entry.setYPos(entry.yPos() + 
                    (realY - toolManager_->objectEditorLastRealY()));
  
  if (entry.xPos() < 0) {
    entry.setXPos(0);
  }
  
  if (entry.yPos() < 0) {
    entry.setYPos(0);
  }
  
  toolManager_->setObjectEditorLastRealX(realX);
  toolManager_->setObjectEditorLastRealY(realY);
}

void LevelObjectGraphicSceneLayer::handleMultipleSelectionPreDrag(
    int realX, int realY, InputEventData eventData) {
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
  toolManager_->setObjectEditorMultipleSelectW(
    realX - toolManager_->objectEditorMultipleSelectX());
  toolManager_->setObjectEditorMultipleSelectH(
    realY - toolManager_->objectEditorMultipleSelectY());
}

void LevelObjectGraphicSceneLayer::handleMultipleSelectionPreRelease(
    int realX, int realY, InputEventData eventData) {
  // Clear existing selection
  toolManager_->objectEditorMultipleCacheIts().clear();
  toolManager_->objectEditorMultipleGroupIts().clear();
      
  // Create Box containing selected area
  Box areaBox = Box(toolManager_->objectEditorMultipleSelectX(),
                    toolManager_->objectEditorMultipleSelectY(),
                    toolManager_->objectEditorMultipleSelectW(),
                    toolManager_->objectEditorMultipleSelectH());
  
  if (areaBox.w() < 0) {
    areaBox = Box(areaBox.x() + areaBox.w(),
                  areaBox.y(),
                  -(areaBox.w()),
                  areaBox.h());
  }
  
  if (areaBox.h() < 0) {
    areaBox = Box(areaBox.x(),
                  areaBox.y() + areaBox.h(),
                  areaBox.w(),
                  -(areaBox.h()));
  }

  // Check which objects, if any, intersect the selection box
  ObjectDisplayCacheCollection::iterator cacheIt
    = objectDisplayCaches_.begin();
  LevelObjectEntryCollection::iterator groupIt
    = levelObjectEntryGroups_->groupBegin(levelObjectEntryGroupIndex_);
  
  while (cacheIt != objectDisplayCaches_.end()) {
  
    if (boxOverlaps(areaBox,
                    cacheIt,
                    groupIt)) {
      // Add object to selection
      toolManager_->objectEditorMultipleCacheIts().push_back(cacheIt);
      toolManager_->objectEditorMultipleGroupIts().push_back(groupIt);
    }
             
    ++cacheIt;
    ++groupIt;
  }
                    
  // If no objects were selected, change to nothing-selected state
  if (toolManager_->objectEditorMultipleCacheIts().empty()) {
    toolManager_->setObjectEditorState(
          LevelEditorTools::objectEditorNothingSelected);
  }
  // Something was selected: go to multiple-selected state
  else {
    toolManager_->setObjectEditorState(
          LevelEditorTools::objectEditorMultipleSelected);
  }
}

void LevelObjectGraphicSceneLayer::handleMultipleSelectionDrag(
    int realX, int realY, InputEventData eventData) {
  if (!(eventData.mouseLeftButton())) {
    return;
  }
  
  int xDiff = realX - toolManager_->objectEditorMultipleLastRealX();
  int yDiff = realY - toolManager_->objectEditorMultipleLastRealY();
  
  LevelObjectEntryCollectionIteratorCollection::iterator groupItIt
      = toolManager_->objectEditorMultipleGroupIts().end();
  ObjectDisplayCacheCollectionIteratorCollection::iterator cacheItIt
      = toolManager_->objectEditorMultipleCacheIts().end();
  do {
    --groupItIt;
    --cacheItIt;
    
    (*groupItIt)->setXPos((*groupItIt)->xPos() + xDiff);
    (*groupItIt)->setYPos((*groupItIt)->yPos() + yDiff);
    
  } while (groupItIt
             != toolManager_->objectEditorMultipleGroupIts().begin());
  
  toolManager_->setObjectEditorMultipleLastRealX(realX);
  toolManager_->setObjectEditorMultipleLastRealY(realY);
}

bool LevelObjectGraphicSceneLayer
    ::pointOverlaps(int realX, int realY,
                   ObjectDisplayCacheCollection::iterator cacheIt,
                   LevelObjectEntryCollection::iterator groupIt) {
  int objX = groupIt->xPos();
  int objY = groupIt->yPos();
  
  int graphicWidth = cacheIt->graphic().w();
  int graphicHeight = cacheIt->graphic().h();
  
  if (Box(objX + cacheIt->offsetX(), objY + cacheIt->offsetY(),
          graphicWidth, graphicHeight)
            .pointOverlaps(realX, realY)) {
    return true;
  }
  
  return false;
}

bool LevelObjectGraphicSceneLayer::boxOverlaps(Box srcbox,
                 ObjectDisplayCacheCollection::iterator cacheIt,
                 LevelObjectEntryCollection::iterator groupIt) {
  int objX = groupIt->xPos();
  int objY = groupIt->yPos();
  
  int graphicWidth = cacheIt->graphic().w();
  int graphicHeight = cacheIt->graphic().h();
  
  if (Box(objX + cacheIt->offsetX(), objY + cacheIt->offsetY(),
          graphicWidth, graphicHeight)
            .boxOverlaps(srcbox)) {
    return true;
  }
  
  return false;
}

int LevelObjectGraphicSceneLayer
    ::warpParameterToLength(Tbyte parameter) {
  return ((parameter & 0x70) + 0x0F) * 2;
}

bool LevelObjectGraphicSceneLayer
    ::warpParameterIsVertical(Tbyte parameter) {
  return (parameter & 0x80) != 0;
}



};
