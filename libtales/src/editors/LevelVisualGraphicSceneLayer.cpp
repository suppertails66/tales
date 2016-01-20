#include "editors/LevelVisualGraphicSceneLayer.h"
#include "gamedata/MetatileStructures.h"
#include "gamedata/MetatileStructure.h"
#include <iostream>

namespace Tales {


LevelVisualGraphicSceneLayer::LevelVisualGraphicSceneLayer(
                             const VRAMCache& vramCache__,
                             const LevelHeader& levelHeader__,
                             const MapLayout& mapLayout__,
                             const MetatileStructureSet& metatileStructureSet__,
                             PriorityLevel priority__)
  : LevelGraphicSceneLayer(levelHeader__,
                           mapLayout__),
    vramCache_(&vramCache__),
    metatileStructureSet_(&metatileStructureSet__),
    priority_(priority__)
//    renderCache_(0, 0),
/*    scaleCache_(0, 0) */ {
  // Cache metatiles
  for (int i = 0; i < MetatileStructures::numMetatilesPerTable; i++) {
    Graphic metatile(MetatileStructure::metatileWidth,
                     MetatileStructure::metatileHeight);
    
    MetatileStructure metatileStructure
      = metatileStructureSet_->metatileMapping(i);
    
    drawMetatileWithPriority(metatile,
                             *vramCache_,
                             metatileStructure,
                             0,
                             0,
                             priority_);
                             
    metatile.regenerateTransparencyModel();
                             
    metatileCache_.push_back(metatile);
  }
}
                      
void LevelVisualGraphicSceneLayer::render(Graphic& dst,
                    Box srcbox,
                    double scale) {
  drawMetatiles(dst,
                srcbox,
                scale);
}
                        
/*void LevelVisualGraphicSceneLayer::render(
                    WrapScrollGraphic& dst,
                    Box dstbox,
                    Box srcbox) {
  // Convert source X and Y to base metatile position
  int metatileBaseX = srcbox.x() / MetatileStructure::metatileWidth
                     * MetatileStructure::metatileWidth
                       / MetatileStructure::metatileWidth;
  int metatileBaseY = srcbox.y() / MetatileStructure::metatileHeight
                     * MetatileStructure::metatileHeight
                       / MetatileStructure::metatileHeight;
                       
  // Compute width and height, adding extra metatiles so the entire
  // visible area is covered
  int metatileEndX = metatileBaseX
          + (srcbox.w() / MetatileStructure::metatileWidth
               * MetatileStructure::metatileWidth / MetatileStructure::metatileWidth)
          + 2;
  int metatileEndY = metatileBaseY
          + (srcbox.h() / MetatileStructure::metatileHeight
               * MetatileStructure::metatileHeight / MetatileStructure::metatileHeight)
          + 2;
  
  for (int j = metatileBaseY; j < metatileEndY; j++) {
    for (int i = metatileBaseX; i < metatileEndX; i++) {
//      std::cout << i << " " << j << std::endl;
      int sourceTileIndex = (j * levelHeader_->width()) + i;
      // If metatile does not exist (outside of level bounds), draw nothing
      if ((i < 0) || (j < 0)
          || (i >= levelHeader_->width())
          // check if metatile is below level
          || (sourceTileIndex >= MapLayout::dataSize)) {
        continue;
      }
      
      int baseDrawX = (i * MetatileStructure::metatileWidth) - srcbox.x();
      int baseDrawY = (j * MetatileStructure::metatileHeight) - srcbox.y();
      
      // Don't draw graphics off the right or bottom of the screen
      if ((baseDrawX >= srcbox.w())
          || (baseDrawY >= srcbox.h())) {
        continue;
      }
      
      Tbyte metatileID = mapLayout_->getMetatile(sourceTileIndex);
      
      dst.blit(metatileCache_[(int)metatileID],
                    Box(baseDrawX,
                        baseDrawY,
                        MetatileStructure::metatileWidth,
                        MetatileStructure::metatileHeight),
                    Box(0, 0, 0, 0),
                    Graphic::noTransUpdate);
    }
  }
} */

void LevelVisualGraphicSceneLayer::drawMetatileWithPriority(Graphic& dst,
                              const VRAMCache& vramCache_,
                              MetatileStructure metatileStructure,
                              int baseDrawX,
                              int baseDrawY,
                              PriorityLevel tilePriority) {
  drawTileIfSamePriority(dst, vramCache_, metatileStructure.upperLeft(),
                         baseDrawX, baseDrawY,
                         tilePriority);
  drawTileIfSamePriority(dst, vramCache_, metatileStructure.upperRight(),
                         baseDrawX + GGTile::width, baseDrawY,
                         tilePriority);
  drawTileIfSamePriority(dst, vramCache_, metatileStructure.lowerLeft(),
                         baseDrawX, baseDrawY + GGTile::height,
                         tilePriority);
  drawTileIfSamePriority(dst, vramCache_, metatileStructure.lowerRight(),
                         baseDrawX + GGTile::width,
                         baseDrawY + GGTile::height,
                         tilePriority);
}

void LevelVisualGraphicSceneLayer::drawTileIfSamePriority(
                            Graphic& dst,
                            const VRAMCache& vramCache_,
                            TileReference tileRef,
                            int drawX,
                            int drawY,
                            PriorityLevel tilePriority) {
  switch (tilePriority) {
  case priorityBG:
    if (tileRef.priorityOption() != TileReference::priorityBG) {
      return;
    }
    break;
  case priorityFG:
    if (tileRef.priorityOption() != TileReference::priorityFG) {
      return;
    }
    break;
  default:
    break;
  }
  
  drawTile(dst,
           vramCache_,
           tileRef,
           drawX,
           drawY);
}

void LevelVisualGraphicSceneLayer::drawTile(
                     Graphic& dst,
                     const VRAMCache& src,
                     TileReference tileRef,
                     int drawX,
                     int drawY) {
  int tileNum = tileRef.tileNum();
  if (tileRef.tileNum() < mapTileOffset_) {
    // Hack: Treat all object-area tiles as tile 256.
    // I think only 0 is ever used, but it causes erroneous transparency
    // (since object tiles are rendered with transparency, but map tiles
    // are not).
    tileNum = mapTileOffset_;
  }
  
  int flipFlags = 0;
  
  if (tileRef.horizontalMirroringOption() == TileReference::horizontalMirror) {
    flipFlags |= VRAMCache::flipHorizontal;
  }
  
  if (tileRef.verticalMirroringOption() == TileReference::verticalMirror) {
    flipFlags |= VRAMCache::flipVertical;
  }
  
  src.copyTile(dst,
                Box(drawX, drawY, 0, 0),
                tileNum,
                flipFlags,
                Graphic::noTransUpdate);
}

void LevelVisualGraphicSceneLayer::drawMetatile(
                          Graphic& drawSurf,
                          int metatileID,
                          int baseDrawX,
                          int baseDrawY) {
  drawSurf.blit(metatileCache_[(int)metatileID],
                Box(baseDrawX,
                    baseDrawY,
                    MetatileStructure::metatileWidth,
                    MetatileStructure::metatileHeight),
                Graphic::noTransUpdate);
}

void LevelVisualGraphicSceneLayer::drawMetatileVisual(
                               Graphic& metatileGraphic,
                               const VRAMCache& src,
                               MetatileStructure metatileStructure) {
  drawTile(metatileGraphic,
           src,
           metatileStructure.upperLeft(),
           0, 0);
  drawTile(metatileGraphic,
           src,
           metatileStructure.upperRight(),
           GGTile::width, 0);
  drawTile(metatileGraphic,
           src,
           metatileStructure.lowerLeft(),
           0, GGTile::height);
  drawTile(metatileGraphic,
           src,
           metatileStructure.lowerRight(),
           GGTile::width, GGTile::height);
}
                                 
void LevelVisualGraphicSceneLayer::drawMetatilePriorityVisual(
                               Graphic& metatileGraphic,
                               const VRAMCache& src,
                               MetatileStructure metatileStructure,
                               PriorityLevel tilePriority) {
  drawMetatileWithPriority(metatileGraphic,
                           src,
                           metatileStructure,
                           0,
                           0,
                           tilePriority);
}
  
Graphic& LevelVisualGraphicSceneLayer::metatileGraphic(int metatileID) {
  return metatileCache_[metatileID];
}


};
