#include "editors/GraphicMappingMath.h"
#include "editors/MappingAssembler.h"

namespace Tales {


TileSetPixelIdentifier GraphicMappingMath::findTilePositionInMapping(
      SpriteMapping& mapping,
      SpriteMappingCoordinateTable& mappingCoordinateTable,
      SpriteMappingTileIndexTable& mappingTileIndexTable,
      GraphicToMappingEntry& mappingEntry,
      int x, int y) {
  Box dimensions = MappingAssembler::computeDimensionsOfMapping(
    mappingCoordinateTable);
  int centerX = dimensions.x();
  int centerY = dimensions.y();
  
  for (int i = mappingCoordinateTable.size() - 1;
       i >= 0;
       i--) {
    SpriteMappingCoordinateTableEntry entry
      = mappingCoordinateTable.entry(i);
    
    int adjustedMapX = entry.offsetX() + centerX;
    int adjustedMapY = entry.offsetY() + centerY;

    int distX = x - adjustedMapX;
    int distY = y - adjustedMapY;
    
    if ((distX < 0) || (distY < 0)) {
      continue;
    }
    
    if (distX < GGTile::width) {
      // Regular sprite
      if (distY < GGTile::height) {
        int index = mappingTileIndexTable.tileIndex(i)
                      + mappingEntry.tileOffset;
        
        return TileSetPixelIdentifier(index, distX, distY);
      }
      // Doubled sprite
      else if (distY < (GGTile::height * 2)) {
        int index = mappingTileIndexTable.tileIndex(i)
                      + mappingEntry.tileOffset
                      + 1;
        
        return TileSetPixelIdentifier(index, distX, distY - GGTile::height);
      }
    }
  }
  
  // Nothing at this position
  return TileSetPixelIdentifier(-1, -1, -1);
}


};
