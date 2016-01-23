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
                       GGPalette& palette__,
                       int offset__)
  : IndexedPickerScene(graphic__.numTiles(),
                       tilesPerRow_,
                       GGTile::width,
                       GGTile::height),
    toolManager_(&toolManager__),
    graphic_(&graphic__),
    palette_(&palette__),
    offset_(offset__) { };

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
  
void GraphicTilePickerScene::enterMouse() {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::enterMouse();
    break;
  default:
    IndexedPickerScene::enterMouse();
    break;
  }
}

void GraphicTilePickerScene::exitMouse() {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::exitMouse();
    break;
  default:
    IndexedPickerScene::exitMouse();
    break;
  }
}

void GraphicTilePickerScene::moveMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::moveMouse(eventData);
    break;
  default:
    IndexedPickerScene::moveMouse(eventData);
    break;
  }
}

void GraphicTilePickerScene::pressMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::pressMouse(eventData);
    toolManager_->setPencilDrawIndex(
      drawPosToSelectableIndex(eventData.x(), eventData.y())
        - offset_);
    break;
  default:
    IndexedPickerScene::pressMouse(eventData);
    break;
  }
}

void GraphicTilePickerScene::releaseMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::releaseMouse(eventData);
    break;
  default:
    IndexedPickerScene::releaseMouse(eventData);
    break;
  }
}

void GraphicTilePickerScene::doubleClickMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::doubleClickMouse(eventData);
    break;
  default:
    IndexedPickerScene::doubleClickMouse(eventData);
    break;
  }
}
                          
int GraphicTilePickerScene::nativeW() {
  return (GGTile::width * tilesPerRow_);
}

int GraphicTilePickerScene::nativeH() {
  return (((graphic_->numTiles() / tilesPerRow_) + 1) * GGTile::height);
}


};
