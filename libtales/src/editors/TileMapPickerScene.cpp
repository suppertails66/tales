#include "editors/TileMapPickerScene.h"
#include "gamegear/GGTile.h"
#include "editors/TileRenderer.h"
#include <algorithm>
#include <utility>
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
  
  // hack to keep picked index from displaying in certain modes
  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
  case TileMapEditorTools::areaClone:
    clearPickedBox();
    break;
  default:
    enablePickedBox();
    break;
  }
  
  // draw tool previews
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
                 toolManager_->pencilHFlip(),
                 toolManager_->pencilVFlip());
    }
    break;
  case TileMapEditorTools::areaClone:
    {
      switch (toolManager_->areaCloneState()) {
      case TileMapEditorTools::areaCloneSelecting:
        {
          int x = toolManager_->areaCloneBaseX();
          int y = toolManager_->areaCloneBaseY();
          int w = toolManager_->areaCloneW();
          int h = toolManager_->areaCloneH();
          
          if (w < 0) {
            x += w;
            w = (-w + 1);
          }
          
          if (h < 0) {
            y += h;
            h = (-h + 1);
          }
          
          dst.drawRectBorder(x * GGTile::width,
                             y * GGTile::height,
                             w * GGTile::width,
                             h * GGTile::height,
                             Color(0xFF, 0, 0, Color::fullAlphaOpacity),
                             1,
                             Graphic::noTransUpdate);
        }
        break;
      case TileMapEditorTools::areaCloneCloning:
        {
          int baseX = indexToTileX(highlightedIndex());
          int baseY = indexToTileY(highlightedIndex());
      
          for (int j = 0; j < toolManager_->areaCloneH(); j++) {
            for (int i = 0; i < toolManager_->areaCloneW(); i++) {
              
              
              TileReference ref = toolManager_->areaCloneBuffer(i, j);
              
              int target = ref.tileNum() + offset_;
              
              if (target < 0) {
                target = 0;
              }
              else if (target >= graphic_->numTiles()) {
                target = 0;
              }
                    
              TileRenderer::renderTile(dst,
                         Box((baseX + i) * GGTile::width,
                             (baseY + j) * GGTile::height,
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
            }
          }
          
          dst.drawRectBorder(baseX * GGTile::width,
                             baseY * GGTile::height,
                             toolManager_->areaCloneW() * GGTile::width,
                             toolManager_->areaCloneH() * GGTile::height,
                             Color(0xFF, 0, 0, Color::fullAlphaOpacity),
                             1,
                             Graphic::noTransUpdate);
        }
        break;
      default:
        break;
      }
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
  case TileMapEditorTools::areaClone:
    
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
  case TileMapEditorTools::areaClone:
    
    break;
  default:
    IndexedPickerScene::exitMouse();
    break;
  }
}

void TileMapPickerScene::moveMouse(InputEventData eventData) {
  clipInputEvent(eventData);

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
  case TileMapEditorTools::areaClone:
    areaCloneDrag(eventData);
    break;
  default:
    IndexedPickerScene::moveMouse(eventData);
    break;
  }
}

void TileMapPickerScene::pressMouse(InputEventData eventData) {
  clipInputEvent(eventData);

  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    if (eventData.mouseLeftButton()) {
      int posIndex = drawPosToSelectableIndex(
                        eventData.x(), eventData.y());
                        
      if (eventData.shift()) {
        grabPencil(posIndex);
      }
      else if (eventData.control()) {
        highlightedSelectableBoxEnabled_ = false;
        toolManager_->changeTool(TileMapEditorTools::areaClone);
        pressMouse(eventData);
      }
      else {
        drawPencil(posIndex);
      }
    }
    else if (eventData.mouseMiddleButton()) {
      toolManager_->flipPencilV();
    }
    else if (eventData.mouseRightButton()) {
      toolManager_->flipPencilH();
//      int posIndex = drawPosToSelectableIndex(
//                        eventData.x(), eventData.y());
//      grabPencil(posIndex);
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
    break;
  case TileMapEditorTools::areaClone:
    areaCloneClick(eventData);
    break;
  default:
    IndexedPickerScene::pressMouse(eventData);
    break;
  }
}

void TileMapPickerScene::releaseMouse(InputEventData eventData) {
  clipInputEvent(eventData);

  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    
    break;
  case TileMapEditorTools::areaClone:
    areaCloneRelease(eventData);
    break;
  default:
    IndexedPickerScene::releaseMouse(eventData);
    break;
  }
}

void TileMapPickerScene::doubleClickMouse(InputEventData eventData) {
  clipInputEvent(eventData);

  switch (toolManager_->currentTool()) {
  case TileMapEditorTools::pencil:
    
    break;
  default:
    IndexedPickerScene::doubleClickMouse(eventData);
    break;
  }
}
  
void TileMapPickerScene::clipInputEvent(InputEventData& eventData) {
  if (eventData.x() < 0) {
    eventData.setX(0);
  }
  
  if (eventData.x() >= nativeW() * sceneScale_) {
    eventData.setX((nativeW() - 1) * sceneScale_);
  }
  
  if (eventData.y() < 0) {
    eventData.setY(0);
  
  }
  
  if (eventData.y() >= nativeH() * sceneScale_) {
    eventData.setY((nativeH() * sceneScale_) - 1);
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
                      (toolManager_->pencilHFlip())
                        ? TileReference::horizontalMirror
                        : TileReference::noHorizontalMirror,
                      (toolManager_->pencilVFlip())
                        ? TileReference::verticalMirror
                        : TileReference::noVerticalMirror,
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
  toolManager_->setPencilHFlip(
                 (ref.horizontalMirroringOption()
                    == TileReference::horizontalMirror)
                    ? true
                    : false);
  toolManager_->setPencilVFlip(
                 (ref.verticalMirroringOption()
                    == TileReference::verticalMirror)
                    ? true
                    : false);
}

int TileMapPickerScene::indexToTileX(int index) const {
  return (index % tileMap_->w());
}

int TileMapPickerScene::indexToTileY(int index) const {
  return (index / tileMap_->w());
}
                            
int TileMapPickerScene::nativeW() {
  return tileMap_->w() * GGTile::width;
}

int TileMapPickerScene::nativeH() {
  return tileMap_->h() * GGTile::height;
}
  
void TileMapPickerScene::areaCloneClick(InputEventData eventData) {
  if ((eventData.mouseRightButton())
      || (eventData.mouseLeftButton() && eventData.shift())) {
    toolManager_->changeTool(TileMapEditorTools::pencil);
    highlightedSelectableIndex_
      = drawPosToSelectableIndex(eventData.x(), eventData.y());
    highlightedSelectableBoxEnabled_ = true;
    grabPencil(highlightedSelectableIndex_);
    return;
  }
  
  switch (toolManager_->areaCloneState()) {
  case TileMapEditorTools::areaCloneWaitingForSelect:
    {
      if (!eventData.mouseLeftButton()) {
        return;
      }
      
      int index = drawPosToSelectableIndex(eventData.x(), eventData.y());
      
      toolManager_->setAreaCloneBaseX(indexToTileX(index));
      toolManager_->setAreaCloneBaseY(indexToTileY(index));
      toolManager_->setAreaCloneW(1);
      toolManager_->setAreaCloneH(1);
      
      toolManager_->setAreaCloneState(
        TileMapEditorTools::areaCloneSelecting);
    }
    break;
  case TileMapEditorTools::areaCloneSelecting:
    
    break;
  case TileMapEditorTools::areaCloneCloning:
    {
      if (eventData.mouseLeftButton()) {
        if (eventData.control()) {
          toolManager_->setAreaCloneState(
              TileMapEditorTools::areaCloneWaitingForSelect);
          areaCloneClick(eventData);
        }
        else {
          cloneArea(drawPosToSelectableIndex(eventData.x(), eventData.y()));
        }
      }
      
    }
    break;
  default:
    break;
  }
}
  
void TileMapPickerScene::cloneArea(int index) {
  int baseX = indexToTileX(index);
  int baseY = indexToTileY(index);
  
  for (int j = 0; j < toolManager_->areaCloneH(); j++) {
    if (baseY + j < 0) {
      continue;
    }
    else if (baseY + j >= tileMap_->h()) {
      break;
    }
    
    for (int i = 0; i < toolManager_->areaCloneW(); i++) {
      if (baseX + i < 0) {
        continue;
      }
      else if (baseX + i >= tileMap_->w()) {
        break;
      }
      
      tileMap_->tileData(baseX + i, baseY + j)
          = toolManager_->areaCloneBuffer(i, j);
    }
  }
}

void TileMapPickerScene::areaCloneDrag(InputEventData eventData) {
  switch (toolManager_->areaCloneState()) {
//  case TileMapEditorTools::areaCloneWaitingForSelect:
//    break;
  case TileMapEditorTools::areaCloneSelecting:
    {
      int index = drawPosToSelectableIndex(eventData.x(), eventData.y());
      int w = indexToTileX(index) - toolManager_->areaCloneBaseX();
      int h = indexToTileY(index) - toolManager_->areaCloneBaseY();
      
      if (w == 0) {
        w = 1;
      }
      else if (w > 0) {
        ++w;
      }
      
      if (h == 0) {
        h = 1;
      }
      else if (h > 0) {
        ++h;
      }
      
      toolManager_->setAreaCloneW(w);
      toolManager_->setAreaCloneH(h);
    }
    break;
  case TileMapEditorTools::areaCloneCloning:
    highlightedSelectableIndex_
      = drawPosToSelectableIndex(eventData.x(), eventData.y());
    
    if (eventData.mouseLeftButton()) {
      cloneArea(drawPosToSelectableIndex(eventData.x(), eventData.y()));
    }
    break;
  default:
    break;
  }
}

void TileMapPickerScene::areaCloneRelease(InputEventData eventData) {
  switch (toolManager_->areaCloneState()) {
//  case TileMapEditorTools::areaCloneWaitingForSelect:
//    break;
  case TileMapEditorTools::areaCloneSelecting:
    toolManager_->finalizeCloneArea(*tileMap_);
    break;
//  case TileMapEditorTools::areaCloneCloning:
//    break;
  default:
    break;
  }
}


};
