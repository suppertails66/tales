#ifndef VRAMCACHE_H
#define VRAMCACHE_H


#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableLevelPaletteHeaders.h"
#include "gamedata/EditableStandardPalettes.h"

namespace Tales {


class VRAMCache {
public:
  enum FlipFlag {
    flipNone        = 0,
    flipHorizontal  = 1,
    flipVertical    = 2
  };

  VRAMCache();
  
  void cacheVRAM(EditableLevelGraphicsData& levelGraphicsData_,
                 EditableLevelPaletteHeaders& paletteHeaders_,
                 EditableStandardPalettes& palettes_,
                 int areaNum_,
                 int mapNum_);
  
  void copyTile(Graphic& dst,
                Box dstbox,
                int tileIndex,
                int flipFlags = 0,
                Graphic::TransBlitOption updateTrans
                  = Graphic::noTransUpdate) const;
protected:

  void renderAllFlips(
                      int tileIndex,
                      GGTileSet& tiles,
                      GGPalette& palette,
                      Graphic::TileTransferTransOption tileTransOption);
  
  void renderTiles(Graphic& g,
                   int tileIndex,
                   GGTileSet& tiles,
                   GGPalette& palette,
                   Graphic::TileTransferTransOption tileTransOption);

  const static int cacheWidth_ = 512 * 8;
  const static int cacheHeight_ = 32;
  
  Graphic cache_;
  Graphic horizontalFlipCache_;
  Graphic verticalFlipCache_;
  Graphic bothFlipCache_;
  
};


};


#endif
