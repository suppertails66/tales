#include "editors/GraphicTileEditorLayer.h"

namespace Tales {


GraphicTileEditorLayer::GraphicTileEditorLayer(
                 GraphicsEditorToolManager& toolManager__)
  : toolManager_(&toolManager__),
    grid_(8, 1, Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity), false) { };
                 
void GraphicTileEditorLayer::render(Graphic& dst,
    Box srcbox,
    double scale) {
  if ((buffer_.w() != nativeWidth())
      || (buffer_.h() != nativeHeight())) {
    buffer_ = Graphic(nativeWidth(), nativeHeight());
  }
    
  // Draw raster elements
  toolManager_->tiles().drawPalettizedGraphic(
                buffer_,
                tilesPerRow_,
                toolManager_->palette(),
                Color(255, 255, 255, Color::fullAlphaTransparency),
                toolManager_->transOption());
  
  
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    // Draw pencil preview if in range
    if ((toolManager_->pencilPreviewEnabled())
        && (toolManager_->pencilTileIndex() >= 0)
        && (toolManager_->pencilTileIndex() <
              toolManager_->tiles().numTiles())) {
      int baseX = tileIndexToDrawX(toolManager_->pencilTileIndex());
      int baseY = tileIndexToDrawY(toolManager_->pencilTileIndex());
      int targetX = baseX + toolManager_->pencilTileX();
      int targetY = baseY + toolManager_->pencilTileY();
      if ((targetX < 0)
          || (targetX >= buffer_.size())
          || (targetY < 0)
          || (targetY >= buffer_.size())) {
        break;
      }
      
      GGColor nativeColor = toolManager_->palette()[
                   toolManager_->currentColorIndex()];
      buffer_.setPixel(targetX,
                 targetY,
                 Color(nativeColor.realR(),
                       nativeColor.realG(),
                       nativeColor.realB(),
                       Color::fullAlphaOpacity));
    }
    break;
  default:
    break;
  }
  
  // Scale
  if (toolManager_->scale() == 1.00) {
    dst.copy(buffer_, Box(0, 0, buffer_.w() * toolManager_->scale(),
                           buffer_.h() * toolManager_->scale()),
            Graphic::transUpdate);
  }
  else {
    buffer_.scale(dst, Box(0, 0, buffer_.w() * toolManager_->scale(),
                           buffer_.h() * toolManager_->scale()),
            Graphic::transUpdate);
  }
  
  // Draw vector elements
  if (toolManager_->gridEnabled()) {
    grid_.render(dst,
                 Box(0, 0, buffer_.w() * toolManager_->scale(),
                           buffer_.h() * toolManager_->scale()),
                 toolManager_->scale());
  }
}
  
int GraphicTileEditorLayer::nativeWidth() {
  return (tilesPerRow_ * GGTile::width);
}

int GraphicTileEditorLayer::nativeHeight() {
  return ((toolManager_->tiles().numTiles() / tilesPerRow_) + 1)
    * GGTile::height;
}
  
void GraphicTileEditorLayer::enterMouse() {
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    toolManager_->setPencilPreviewEnabled(true);
    break;
  default:
    break;
  }
}

void GraphicTileEditorLayer::exitMouse() {
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    toolManager_->setPencilPreviewEnabled(false);
    break;
  default:
    break;
  }
}

void GraphicTileEditorLayer::moveMouse(InputEventData eventData) {
  
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    {
    int nativeX = realToNative(eventData.x());
    int nativeY = realToNative(eventData.y());
    
    if ((nativeX < 0)
        || (nativeX >= nativeWidth())
        || (nativeY < 0)
        || (nativeY >= nativeHeight())) {
      return;
    }
    
    int tileIndex = nativeToIndex(nativeX, nativeY);
    
    if ((tileIndex < 0)
        || (tileIndex >= toolManager_->tiles().numTiles())) {
      return;
    }
    
    toolManager_->setPencilTileIndex(tileIndex);
    toolManager_->setPencilTileX(nativeToTileX(nativeX));
    toolManager_->setPencilTileY(nativeToTileY(nativeY));
    drawPencil(eventData);
    }
    break;
  default:
    break;
  }
}

void GraphicTileEditorLayer::pressMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    if (eventData.control()) {
      // Set current color to one under mouse
      toolManager_->setCurrentColorIndex(
        toolManager_->tiles()[toolManager_->pencilTileIndex()]
          .getPixel(toolManager_->pencilTileX(),
                    toolManager_->pencilTileY()));
    }
    else {
      drawPencil(eventData);
    }
    break;
  default:
    break;
  }
}

void GraphicTileEditorLayer::releaseMouse(InputEventData eventData) {
  
}

void GraphicTileEditorLayer::doubleClickMouse(InputEventData eventData) {
  
}

int GraphicTileEditorLayer::realToNative(int coordinate) {
  return (coordinate / toolManager_->scale());
}

int GraphicTileEditorLayer::nativeToIndex(int x, int y) {
  return ((y / GGTile::height) * tilesPerRow_)
              + (x / GGTile::width);
}

int GraphicTileEditorLayer::nativeToTileX(int x) {
  return (x % GGTile::width);
}

int GraphicTileEditorLayer::nativeToTileY(int y) {
  return (y % GGTile::height);
}

int GraphicTileEditorLayer::tileIndexToDrawX(int index) {
  return ((index % tilesPerRow_) * GGTile::width);
}

int GraphicTileEditorLayer::tileIndexToDrawY(int index) {
  return ((index / tilesPerRow_) * GGTile::height);
}
  
void GraphicTileEditorLayer::drawPencil(InputEventData eventData) {
  // Change pixel if target tile in range
  if ((toolManager_->pencilTileIndex() >= 0)
    && (toolManager_->pencilTileIndex() <
          toolManager_->tiles().numTiles())) {
    if (eventData.mouseLeftButton()) {
      toolManager_->tiles()[toolManager_->pencilTileIndex()]
        .setPixel(toolManager_->pencilTileX(),
                  toolManager_->pencilTileY(),
                  toolManager_->currentColorIndex());
    }
    else if (eventData.mouseRightButton()) {
      toolManager_->tiles()[toolManager_->pencilTileIndex()]
        .setPixel(toolManager_->pencilTileX(),
                  toolManager_->pencilTileY(),
                  0);
    }
  }
}


};
