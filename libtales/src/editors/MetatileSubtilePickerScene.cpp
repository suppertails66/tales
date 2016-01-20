#include "editors/MetatileSubtilePickerScene.h"
#include "editors/TileRenderer.h"
#include <cstdlib>

namespace Tales {


MetatileSubtilePickerScene::MetatileSubtilePickerScene()
  : IndexedPickerScene(4, 2, 8, 8),
    tiles_(NULL),
    palette0_(NULL),
    palette1_(NULL),
    metatile_(NULL) {
  sceneScale_ = 8.00;
}
  
MetatileSubtilePickerScene::~MetatileSubtilePickerScene() { };

void MetatileSubtilePickerScene::renderNative(Graphic& dst,
                          Box srcbox) {
  int drawX = selectableIndexToDrawX(0);
  int drawY = selectableIndexToDrawY(0);
  TileRenderer::renderMetatile(dst,
                               Box(drawX, drawY,
                                   MetatileStructure::metatileWidth,
                                   MetatileStructure::metatileHeight),
                               *metatile_,
                               *tiles_,
                               *palette0_,
                               *palette1_,
                               tileOffset_);
}

void MetatileSubtilePickerScene::setTiles(GGTileSet& tiles__) {
  tiles_ = &tiles__;
}

void MetatileSubtilePickerScene::setPalette0(GGPalette& palette0__) {
  palette0_ = &palette0__;
}

void MetatileSubtilePickerScene::setPalette1(GGPalette& palette1__) {
  palette1_ = &palette1__;
}

void MetatileSubtilePickerScene::setMetatile(MetatileStructure& metatile__) {
  metatile_ = &metatile__;
}

void MetatileSubtilePickerScene::pressMouse(InputEventData eventData) {
  int index = drawPosToSelectableIndex(eventData.x(), eventData.y());
  
  TileReference* target = NULL;
  switch (index) {
  case 0:
    target = &(metatile_->upperLeft());
    break;
  case 1:
    target = &(metatile_->upperRight());
    break;
  case 2:
    target = &(metatile_->lowerLeft());
    break;
  case 3:
    target = &(metatile_->lowerRight());
    break;
  default:
    break;
  }
    
  if (eventData.mouseRightButton()) {
    // Horizontal flip
    if (target->horizontalMirroringOption()
          == TileReference::noHorizontalMirror) {
      target->setHorizontalMirroringOption(TileReference::horizontalMirror);
    }
    else {
      target->setHorizontalMirroringOption(TileReference::noHorizontalMirror);
    }
    
    return;
  }
  else if (eventData.mouseMiddleButton()) {
    // Vertical flip
    if (target->verticalMirroringOption()
          == TileReference::noVerticalMirror) {
      target->setVerticalMirroringOption(TileReference::verticalMirror);
    }
    else {
      target->setVerticalMirroringOption(TileReference::noVerticalMirror);
    }
    
    return;
  }
  else {
    IndexedPickerScene::pressMouse(eventData);
  }
}



};
