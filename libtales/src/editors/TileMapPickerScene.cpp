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
    toolManager_(NULL),
    tileMap_(NULL),
    graphic_(NULL),
    palette0_(NULL) { };

TileMapPickerScene::TileMapPickerScene(
                   TileMapEditorToolManager& toolManager__,
                   TileMap& tileMap__,
                   GGTileSet& graphic__,
                   GGPalette& palette0__,
                   int offset__)
  : IndexedPickerScene(tileMap__.w() * tileMap__.h(),
                        tileMap__.w(),
                        GGTile::width,
                        GGTile::height),
    toolManager_(&toolManager__),
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
  
  // hack to keep picked index from displaying in pencil mode
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    clearPickedBox();
    break;
  default:
    enablePickedBox();
    break;
  }
  
  // draw pencil preview if using pencil
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    {
      if (!highlightedSelectableBoxEnabled_) {
        return;
      }
      
      int tileX = indexToTileX(highlightedIndex());
      int tileY = indexToTileY(highlightedIndex());
      
      TileReference ref = tileMap_->tileData(
        tileX,
        tileY);
      
      int target = toolManager_->pencilDrawIndex() + offset_;
      
      if (target < 0) {
        target = 0;
      }
      else if (target >= graphic_->numTiles()) {
        target = 0;
      }
                    
      TileRenderer::renderTile(dst,
                 Box(tileX * GGTile::width,
                     tileY * GGTile::height,
                     GGTile::width,
                     GGTile::height),
                 (*graphic_)[target],
                 *palette0_,
                 false,
                 false);
    }
    break;
  default:
    break;
  }
}
  
void TileMapPickerScene::enterMouse() {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::enterMouse();
    break;
  default:
    IndexedPickerScene::enterMouse();
    break;
  }
}

void TileMapPickerScene::exitMouse() {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::exitMouse();
    break;
  default:
    IndexedPickerScene::exitMouse();
    break;
  }
}

void TileMapPickerScene::moveMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    IndexedPickerScene::moveMouse(eventData);
    
    if (eventData.mouseLeftButton()) {
      int posIndex = drawPosToSelectableIndex(
                        eventData.x(), eventData.y());
      if (eventData.control()) {
        
      }
      else {
        drawPencil(posIndex);
      }
    }
    break;
  default:
    IndexedPickerScene::moveMouse(eventData);
    break;
  }
}

void TileMapPickerScene::pressMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    if (eventData.mouseLeftButton()) {
      int posIndex = drawPosToSelectableIndex(
                        eventData.x(), eventData.y());
      if (eventData.control()) {
        grabPencil(posIndex);
      }
      else {
        drawPencil(posIndex);
      }
    }
    else if (eventData.mouseRightButton()) {
      int posIndex = drawPosToSelectableIndex(
                        eventData.x(), eventData.y());
      grabPencil(posIndex);
    }
    break;
  case TileMapEditorTools::regular:
    if (eventData.mouseLeftButton()) {
      IndexedPickerScene::pressMouse(eventData);
    }
    else if (eventData.mouseMiddleButton()) {
      int posIndex = drawPosToSelectableIndex(
                        eventData.x(), eventData.y());
      TileReference& ref = tileMap_->tileData(
          indexToTileX(posIndex), indexToTileY(posIndex));
      if (ref.verticalMirroringOption()
            == TileReference::verticalMirror) {
        ref.setVerticalMirroringOption(TileReference::noVerticalMirror);
      }
      else {
        ref.setVerticalMirroringOption(TileReference::verticalMirror);
      }
    }
    else if (eventData.mouseRightButton()) {
      int posIndex = drawPosToSelectableIndex(
                        eventData.x(), eventData.y());
      TileReference& ref = tileMap_->tileData(
          indexToTileX(posIndex), indexToTileY(posIndex));
      if (ref.horizontalMirroringOption()
            == TileReference::horizontalMirror) {
        ref.setHorizontalMirroringOption(TileReference::noHorizontalMirror);
      }
      else {
        ref.setHorizontalMirroringOption(TileReference::horizontalMirror);
      }
    }
  default:
    IndexedPickerScene::pressMouse(eventData);
    break;
  }
}
  
void TileMapPickerScene::drawPencil(int posIndex) {
  if ((posIndex >= totalSelectables_)
      || (posIndex < 0)) {
    return;
  }

  TileReference& ref = tileMap_->tileData(
      indexToTileX(posIndex), indexToTileY(posIndex));
      
//      toolManager_->setPencilDrawIndex(

//  ref.setTileNum(toolManager_->pencilDrawIndex());
  ref = TileReference(toolManager_->pencilDrawIndex(),
                      TileReference::noHorizontalMirror,
                      TileReference::noVerticalMirror,
                      TileReference::palette0,
                      TileReference::priorityBG);
}

void TileMapPickerScene::grabPencil(int posIndex) {
  if ((posIndex >= totalSelectables_)
      || (posIndex < 0)) {
    return;
  }

  TileReference& ref = tileMap_->tileData(
      indexToTileX(posIndex), indexToTileY(posIndex));
      
  toolManager_->setPencilDrawIndex(ref.tileNum());
}

int TileMapPickerScene::indexToTileX(int index) const {
  return (index % tileMap_->w());
}

int TileMapPickerScene::indexToTileY(int index) const {
  return (index / tileMap_->w());
}

void TileMapPickerScene::releaseMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    
    break;
  default:
    IndexedPickerScene::releaseMouse(eventData);
    break;
  }
}

void TileMapPickerScene::doubleClickMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    
    break;
  default:
    IndexedPickerScene::doubleClickMouse(eventData);
    break;
  }
}
                            
int TileMapPickerScene::nativeW() {
  return tileMap_->w() * GGTile::width;
}

int TileMapPickerScene::nativeH() {
  return tileMap_->h() * GGTile::height;
}


};
