#include "editors/TilePickerScene.h"
#include "editors/TileRenderer.h"
#include "util/MiscMath.h"
#include <cstdlib>
#include <iostream>

using namespace Luncheon;

namespace Tales {


TilePickerScene::TilePickerScene()
  : IndexedPickerScene(256, 16, 8, 8),
    tiles_(NULL),
    palette0_(NULL),
    palette1_(NULL) {
  sceneScale_ = 2.00;
}
  
TilePickerScene::~TilePickerScene() { };

void TilePickerScene::renderNative(Graphic& dst,
                            Box srcbox) {
  dst.clear(Color(255, 255, 255, Color::fullAlphaOpacity));
                            
  if ((tiles_ == NULL)
      || (palette0_ == NULL)
      || (palette1_ == NULL)) {
    return;
  }
                            
  for (int i = 0; i < tiles_->numTiles(); i++) {
    int drawX = selectableIndexToNativeDrawX(i);
    int drawY = selectableIndexToNativeDrawY(i);
                    
    TileRenderer::renderTile(dst,
               Box(drawX, drawY,
                   GGTile::width, GGTile::height),
               (*tiles_)[i],
               *palette0_,
               false,
               false);
  }
}
  
void TilePickerScene::setTiles(GGTileSet& tiles__) {
  tiles_ = &tiles__;
}

void TilePickerScene::setPalette0(GGPalette& palette0__) {
  palette0_ = &palette0__;
}

void TilePickerScene::setPalette1(GGPalette& palette1__) {
  palette1_ = &palette1__;
}


};
