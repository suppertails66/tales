#ifndef GRAPHICMAPPINGMATH_H
#define GRAPHICMAPPINGMATH_H


#include "editors/TileSetPixelIdentifier.h"
#include "editors/GraphicToMappings.h"
#include "gamegear/GGTileSet.h"
#include "gamedata/SpriteMapping.h"
#include "gamedata/SpriteMappingCoordinateTable.h"
#include "gamedata/SpriteMappingTileIndexTable.h"

namespace Tales {


class GraphicMappingMath {
public:
  static TileSetPixelIdentifier findTilePositionInMapping(
      SpriteMapping& mapping,
      SpriteMappingCoordinateTable& mappingCoordinateTable,
      SpriteMappingTileIndexTable& mappingTileIndexTable,
      GraphicToMappingEntry& mappingEntry,
      int x, int y);
protected:
  
};


};


#endif
