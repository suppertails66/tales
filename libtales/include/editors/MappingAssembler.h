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
                               
  static Box computeDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable);
                               
  static Box computeRealDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable,
    int offsetX,
    int offsetY);
};


};


#endif
