#ifndef MAPPINGASSEMBLER_H
#define MAPPINGASSEMBLER_H


#include "structs/Graphic.h"
#include "gamegear/GGTileSet.h"
#include "gamedata/EditableSpriteMappings.h"
#include "gamegear/GGPalette.h"
#include "gamedata/ObjectStateInfo.h"
#include "editors/ObjectDisplayCache.h"

namespace Tales {


class MappingAssembler {
public:
  static void assembleMappings(ObjectDisplayCache& dst,
                               GGTileSet& src,
                               SpriteMapping& spriteMapping,
                               SpriteMappingCoordinateTable& coordinateTable,
                               SpriteMappingTileIndexTable& tileIndexTable,
                               GGPalette& palette,
                               ObjectStateInfo::FacingDirection
                                 facingDirection,
                               int tileOffset);
                               
  static void assembleMappings(ObjectDisplayCache& dst,
                               GGTileSet& src,
                               SpriteMapping& spriteMapping,
                               SpriteMappingCoordinateTable& coordinateTable,
                               SpriteMappingTileIndexTable& tileIndexTable,
                               GGPalette& palette,
                               ObjectStateInfo::FacingDirection
                                 facingDirection,
                               int tileOffset,
                               Color backgroundColor,
                               Color tileBackgroundColor);
                               
  static Box computeDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable);
                               
  static Box computeRealDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable,
    int offsetX,
    int offsetY);
protected:
  static void assembleMappingsInternal(ObjectDisplayCache& dst,
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
                               bool useTileBGColor = false,
                               Color tileBGColor = Color());
                               
};


};


#endif
