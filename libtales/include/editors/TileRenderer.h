#ifndef TILERENDERER_H
#define TILERENDERER_H


#include "structs/Graphic.h"
#include "gamedata/MetatileStructure.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class TileRenderer {
public:
  static void renderMetatile(Graphic& dst,
                      Box dstbox,
                      MetatileStructure& metatile,
                      GGTileSet& tileset,
                      GGPalette& palette0,
                      GGPalette& palette1,
                      int tileOffset = 0);
                            
  static void renderTile(Graphic& dst,
                Box dstbox,
                GGTile src,
                GGPalette& palette,
                bool hFlip,
                bool vFlip);
protected:
  
};


};


#endif
