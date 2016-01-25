#include "editors/MappingAssembler.h"
#include "gamedata/MetatileStructure.h"
#include <cmath>
#include <iostream>

namespace Tales {


void MappingAssembler::assembleMappings(ObjectDisplayCache& dst,
                             GGTileSet& src,
                             SpriteMapping& spriteMapping,
                             SpriteMappingCoordinateTable& coordinateTable,
                             SpriteMappingTileIndexTable& tileIndexTable,
                             GGPalette& palette,
                             ObjectStateInfo::FacingDirection
                               facingDirection,
                             int tileOffset) {
  Box offsetInfo = computeDimensionsOfMapping(coordinateTable);
  
  Graphic graphic(offsetInfo.w(), offsetInfo.h());
  graphic.clear();
  
  assembleMappingsInternal(dst,
                           src,
                           graphic,
                           spriteMapping,
                           coordinateTable,
                           tileIndexTable,
                           palette,
                           facingDirection,
                           tileOffset,
                           offsetInfo);
}
                             
void MappingAssembler::assembleMappings(ObjectDisplayCache& dst,
                             GGTileSet& src,
                             SpriteMapping& spriteMapping,
                             SpriteMappingCoordinateTable& coordinateTable,
                             SpriteMappingTileIndexTable& tileIndexTable,
                             GGPalette& palette,
                             ObjectStateInfo::FacingDirection
                               facingDirection,
                             int tileOffset,
                             Color backgroundColor,
                             Color tileBackgroundColor) {
  Box offsetInfo = computeDimensionsOfMapping(coordinateTable);
  
  Graphic graphic(offsetInfo.w(), offsetInfo.h());
  graphic.clear(backgroundColor);
  
  assembleMappingsInternal(dst,
                           src,
                           graphic,
                           spriteMapping,
                           coordinateTable,
                           tileIndexTable,
                           palette,
                           facingDirection,
                           tileOffset,
                           offsetInfo,
                           true,
                           tileBackgroundColor);
}
                               
void MappingAssembler::assembleMappingsInternal(
                               ObjectDisplayCache& dst,
                               GGTileSet& src,
                               Graphic& graphic,
                               SpriteMapping& spriteMapping,
                               SpriteMappingCoordinateTable& coordinateTable,
                               SpriteMappingTileIndexTable& tileIndexTable,
                               GGPalette& palette,
                               ObjectStateInfo::FacingDirection
                                 facingDirection,
                               int tileOffset,
                               Box offsetInfo,
                               bool useTileBGColor,
                               Color tileBGColor) {
  int baseX = offsetInfo.x();
  int baseY = offsetInfo.y();
  
  for (int i = 0; i < tileIndexTable.size(); i++) {
    if (i >= coordinateTable.size()) {
      break;
    }
  
    int tileIndex = tileIndexTable.tileIndex(i) + tileOffset;
    
    Graphic g;
    Graphic g2;
    if (useTileBGColor) {
      g = Graphic(src[tileIndex],
                palette,
                Graphic::tileTrans,
                tileBGColor);
      g2 = Graphic(src[tileIndex + 1],
                palette,
                Graphic::tileTrans,
                tileBGColor);
    }
    else {
      g = Graphic(src[tileIndex],
                palette,
                Graphic::tileTrans);
      g2 = Graphic(src[tileIndex + 1],
                palette,
                Graphic::tileTrans);
    }
    
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
  }
  
  graphic.regenerateTransparencyModel();
  
  dst.setGraphic(graphic);
  dst.setOffsetX(spriteMapping.offsetX() - baseX);
  dst.setOffsetY(spriteMapping.offsetY() - baseY
    + (MetatileStructure::metatileHeight)
    + (MetatileStructure::metatileHeight / 8));
}

Box MappingAssembler::computeDimensionsOfMapping(
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
                               
Box MappingAssembler::computeRealDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable,
    int offsetX,
    int offsetY) {
  Box result = computeDimensionsOfMapping(coordinateTable);
  
//  std::cout << result.x() << " " << result.y() << std::endl;
  if (offsetX < 0) {
    result.setX(result.x() - offsetX);
  }
  
  if (offsetY < 0) {
    result.setY(result.y() - offsetY);
  }
  
  
  result.setW(result.w() + std::abs((double)(offsetX)));
  result.setH(result.h() + std::abs((double)(offsetY)));
  
  return result;
}


};
