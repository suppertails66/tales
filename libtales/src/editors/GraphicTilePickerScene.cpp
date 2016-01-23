#include "editors/GraphicTilePickerScene.h"
#include <cstdlib>

namespace Tales {


GraphicTilePickerScene::GraphicTilePickerScene()
  : IndexedPickerScene(1, 1, 1, 1),
    toolManager_(NULL),
    graphic_(NULL),
    palette_(NULL) { };
  
GraphicTilePickerScene::GraphicTilePickerScene(
                       TileMapEditorToolManager& toolManager__,
                       GGTileSet& graphic__,
                       GGPalette& palette__)
  : IndexedPickerScene(graphic__.numTiles(),
                       tilesPerRow_,
                       GGTile::width,
                       GGTile::height),
    toolManager_(&toolManager__),
    graphic_(&graphic__),
    palette_(&palette__) { };

void GraphicTilePickerScene::renderNative(
                          Graphic& dst,
                          Box srcbox) {
//  dst.clear(Color(255, 255, 255, Color::fullAlphaOpacity));
  
  graphic_->drawPalettizedGraphic(
                      dst,
                      tilesPerRow_,
                      *palette_,
                      Color(255, 255, 255, Color::fullAlphaOpacity),
                      Graphic::noTileTrans);
}
                          
int GraphicTilePickerScene::nativeW() {
  return (GGTile::width * tilesPerRow_);
}

int GraphicTilePickerScene::nativeH() {
  return (((graphic_->numTiles() / tilesPerRow_) + 1) * GGTile::height);
}


};
