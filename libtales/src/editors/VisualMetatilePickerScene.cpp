#include "editors/VisualMetatilePickerScene.h"
#include "editors/TileRenderer.h"
#include "gamedata/MetatileStructure.h"
#include <cstdlib>
#include <iostream>

namespace Tales {


//Graphic VisualMetatilePickerScene::tileRenderBuffer_
//    (GGTile::width, GGTile::height);

VisualMetatilePickerScene::VisualMetatilePickerScene()
  : IndexedPickerScene(256, 16,
                       MetatileStructure::metatileWidth,
                       MetatileStructure::metatileHeight),
    tiles_(NULL),
    palette0_(NULL),
    palette1_(NULL),
    metatiles_(NULL) { };
  
VisualMetatilePickerScene::~VisualMetatilePickerScene() { };

void VisualMetatilePickerScene::renderNative(Graphic& dst,
                          Box srcbox) {
  dst.clear(Color(255, 255, 255, Color::fullAlphaOpacity));
                          
  if ((tiles_ == NULL) || (metatiles_ == NULL)) {
    return;
  }
  
  for (int i = 0; i < metatiles_->numMetatileMappings(); i++) {
    MetatileStructure& metatile = metatiles_->metatileMapping(i);
    int drawX = selectableIndexToDrawX(i);
    int drawY = selectableIndexToDrawY(i);
    TileRenderer::renderMetatile(dst,
                                 Box(drawX, drawY,
                                     MetatileStructure::metatileWidth,
                                     MetatileStructure::metatileHeight),
                                 metatile,
                                 *tiles_,
                                 *palette0_,
                                 *palette1_,
                                 tileOffset_);
  }
}
  
void VisualMetatilePickerScene::setTiles(GGTileSet& tiles__) {
  tiles_ = &tiles__;
}

void VisualMetatilePickerScene::setPalette0(GGPalette& palette0__) {
  palette0_ = &palette0__;
}

void VisualMetatilePickerScene::setPalette1(GGPalette& palette1__) {
  palette1_ = &palette1__;
}

void VisualMetatilePickerScene
    ::setMetatiles(MetatileStructureSet& metatiles__) {
  metatiles_ = &metatiles__;
}
  
GGTileSet& VisualMetatilePickerScene
    ::tiles() {
  return *tiles_;
}

GGPalette& VisualMetatilePickerScene
    ::palette0() {
  return *palette0_;
}

GGPalette& VisualMetatilePickerScene
    ::palette1() {
  return *palette1_;
}

MetatileStructureSet& VisualMetatilePickerScene
    ::metatiles() {
  return *metatiles_;
}


};
