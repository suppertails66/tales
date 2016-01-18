#include "editors/TileRenderer.h"
#include "util/MiscMath.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


void TileRenderer::renderMetatile(Graphic& dst,
                    Box dstbox,
                    MetatileStructure& metatile,
                    GGTileSet& tileset,
                    GGPalette& palette0,
                    GGPalette& palette1,
                    int tileOffset) {
  int ulTileNum = metatile.upperLeft().tileNum()
                        + tileOffset;
  int urTileNum = metatile.upperRight().tileNum()
                        + tileOffset;
  int llTileNum = metatile.lowerLeft().tileNum()
                        + tileOffset;
  int lrTileNum = metatile.lowerRight().tileNum()
                        + tileOffset;
                        
//  std::cout << ulTileNum << std::endl;

  if (ulTileNum >= tileset.numTiles()) {
    ulTileNum = 0;
  }

  if (urTileNum >= tileset.numTiles()) {
    urTileNum = 0;
  }

  if (llTileNum >= tileset.numTiles()) {
    llTileNum = 0;
  }

  if (lrTileNum >= tileset.numTiles()) {
    lrTileNum = 0;
  }
                        
  MiscMath::clamp(ulTileNum, 0, tileset.numTiles() - 1);
  MiscMath::clamp(urTileNum, 0, tileset.numTiles() - 1);
  MiscMath::clamp(llTileNum, 0, tileset.numTiles() - 1);
  MiscMath::clamp(lrTileNum, 0, tileset.numTiles() - 1);
                    
  renderTile(dst,
             Box(dstbox.x(), dstbox.y(),
                 GGTile::width, GGTile::height),
             tileset[ulTileNum],
             (metatile.upperLeft().paletteOption()
                 == TileReference::palette0)
               ? palette0
               : palette1,
             (metatile.upperLeft().horizontalMirroringOption()
                 == TileReference::horizontalMirror)
               ? true
               : false,
             (metatile.upperLeft().verticalMirroringOption()
                 == TileReference::verticalMirror)
               ? true
               : false);
  
  renderTile(dst,
             Box(dstbox.x() + GGTile::width, dstbox.y(),
                 GGTile::width, GGTile::height),
             tileset[urTileNum],
             (metatile.upperRight().paletteOption()
                 == TileReference::palette0)
               ? palette0
               : palette1,
             (metatile.upperRight().horizontalMirroringOption()
                 == TileReference::horizontalMirror)
               ? true
               : false,
             (metatile.upperRight().verticalMirroringOption()
                 == TileReference::verticalMirror)
               ? true
               : false);
  
  renderTile(dst,
             Box(dstbox.x(), dstbox.y() + GGTile::height,
                 GGTile::width, GGTile::height),
             tileset[llTileNum],
             (metatile.lowerLeft().paletteOption()
                 == TileReference::palette0)
               ? palette0
               : palette1,
             (metatile.lowerLeft().horizontalMirroringOption()
                 == TileReference::horizontalMirror)
               ? true
               : false,
             (metatile.lowerLeft().verticalMirroringOption()
                 == TileReference::verticalMirror)
               ? true
               : false);
  
  renderTile(dst,
             Box(dstbox.x() + GGTile::width, dstbox.y() + GGTile::height,
                 GGTile::width, GGTile::height),
             tileset[lrTileNum],
             (metatile.lowerRight().paletteOption()
                 == TileReference::palette0)
               ? palette0
               : palette1,
             (metatile.lowerRight().horizontalMirroringOption()
                 == TileReference::horizontalMirror)
               ? true
               : false,
             (metatile.lowerRight().verticalMirroringOption()
                 == TileReference::verticalMirror)
               ? true
               : false);
}

void TileRenderer::renderTile(Graphic& dst,
                Box dstbox,
                GGTile src,
                GGPalette& palette,
                bool hFlip,
                bool vFlip) {
  if (hFlip) {
    src.flipHorizontal();
  }
  
  if (vFlip) {
    src.flipVertical();
  }
                
  Graphic tileRenderBuffer = Graphic(src, palette, Graphic::noTileTrans);
  
  dst.copy(tileRenderBuffer,
           dstbox);
}


}; 
