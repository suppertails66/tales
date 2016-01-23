#include "editors/TileMapPickerScene.h"
#include "gamegear/GGTile.h"
#include "editors/TileRenderer.h"
#include <cstdlib>
#include <iostream>

namespace Tales {


TileMapPickerScene::TileMapPickerScene()
  : IndexedPickerScene(1,
                       1,
                       1,
                       1),
    tileMap_(NULL),
    graphic_(NULL),
    palette0_(NULL) { };

TileMapPickerScene::TileMapPickerScene(TileMap& tileMap__,
                   GGTileSet& graphic__,
                   GGPalette& palette0__,
                   int offset__)
  : IndexedPickerScene(tileMap__.w() * tileMap__.h(),
                        tileMap__.w(),
                        GGTile::width,
                        GGTile::height),
    tileMap_(&tileMap__),
    graphic_(&graphic__),
    palette0_(&palette0__),
    offset_(offset__) { };
  
void TileMapPickerScene::renderNative(Graphic& dst,
                            Box srcbox) {
//  dst = Graphic(tileMap_->w() * GGTile::width,
//                tileMap_->h() * GGTile::height);

  dst.clear(Color(255, 255, 255, Color::fullAlphaOpacity));
  
  for (int j = 0; j < tileMap_->h(); j++) {
    for (int i = 0; i < tileMap_->w(); i++) {
      TileReference ref = tileMap_->tileData(i, j);
      
      int target = ref.tileNum() + offset_;
      
      if (target < 0) {
        target = 0;
      }
      else if (target >= graphic_->numTiles()) {
        target = 0;
      }
      
//      std::cout << target << std::endl;

//      GGTile tile = (*graphic_)[target];
                    
      TileRenderer::renderTile(dst,
                 Box(i * GGTile::width,
                     j * GGTile::height,
                     GGTile::width,
                     GGTile::height),
                 (*graphic_)[target],
                 *palette0_,
                 (ref.horizontalMirroringOption()
                    == TileReference::horizontalMirror)
                    ? true
                    : false,
                 (ref.verticalMirroringOption()
                    == TileReference::verticalMirror)
                    ? true
                    : false);
      
/*      GGTile tile = (*graphic_)[target];
      
      if (ref.horizontalMirroringOption()) {
        tile.flipHorizontal();
      }
      
      if (ref.verticalMirroringOption()) {
        tile.flipVertical();
      }
      
      Graphic g(tile, *palette0_);
      g.regenerateTransparencyModel();
      dst.copy(g,
               Box(i * GGTile::width, j * GGTile::height, 0, 0),
               Graphic::noTransUpdate); */
    }
  }
}
                            
int TileMapPickerScene::nativeW() {
  return tileMap_->w() * GGTile::width;
}

int TileMapPickerScene::nativeH() {
  return tileMap_->h() * GGTile::height;
}


};
