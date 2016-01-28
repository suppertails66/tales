#include "editors/GraphicMappingEditorLayer.h"
#include "editors/MappingAssembler.h"
#include "editors/GraphicMappingMath.h"
#include <iostream>

namespace Tales {


GraphicMappingEditorLayer::GraphicMappingEditorLayer(
                 GraphicsEditorToolManager& toolManager__)
  : toolManager_(&toolManager__),
    grid_(8, 1, Color(0x80, 0x80, 0x80, Color::fullAlphaOpacity), false) { };
                 
void GraphicMappingEditorLayer::render(Graphic& dst,
    Box srcbox,
    double scale) {
  if (!(toolManager_->mappingExists())) {
    return;
  }
  
//  Box dimensions = MappingAssembler::computeRealDimensionsOfMapping(
//    toolManager_->mappingCoordinateTable(),
//    toolManager_->mapping().offsetX(),
//    toolManager_->mapping().offsetY());

  Box dimensions = MappingAssembler::computeDimensionsOfMapping(
    toolManager_->mappingCoordinateTable());
    
  if ((cache_.graphic().w() != nativeWidth())
      || (cache_.graphic().h() != nativeHeight())) {
    cache_.setGraphic(Graphic(nativeWidth(), nativeHeight()));
    buffer_ = Graphic(nativeWidth(), nativeHeight());
  }
  
  buffer_.clear(Color(0xFF, 0xFF, 0xFF, Color::fullAlphaTransparency));
    
  // Draw raster elements
  MappingAssembler::assembleMappings(cache_,
                                     toolManager_->tiles(),
                                     toolManager_->mapping(),
                                     toolManager_->mappingCoordinateTable(),
                                     toolManager_->mappingTileIndexTable(),
                                     toolManager_->palette(),
                                     ObjectStateInfo::left,
                                     toolManager_->mappingEntry()
                                       .tileOffset,
                                     Color(0xFF, 0xFF, 0xFF,
                                           Color::fullAlphaTransparency),
                                     Color(0xFF, 0xFF, 0xFF,
                                           Color::fullAlphaOpacity));
//  cache_.graphic().regenerateTransparencyModel();
  
  buffer_.blit(cache_.graphic());
//  cache_.graphic().copy(buffer_, Box(0, 0, 0, 0));
                                     
/*  toolManager_->tiles().drawPalettizedGraphic(
                buffer_,
                tilesPerRow_,
                toolManager_->palette(),
                Color(255, 255, 255, Color::fullAlphaTransparency),
                toolManager_->transOption()); */
  
  
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    // Draw pencil preview if in range
    if ((toolManager_->pencilPreviewEnabled())
        && (toolManager_->pencilTileIndex() >= 0)
        && (toolManager_->pencilTileIndex() <
              toolManager_->tiles().numTiles())) {
      drawPencilPreview(buffer_);
/*      int baseX = tileIndexToDrawX(toolManager_->pencilTileIndex());
      int baseY = tileIndexToDrawY(toolManager_->pencilTileIndex());
      GGColor nativeColor = toolManager_->palette()[
                   toolManager_->currentColorIndex()];
      buffer_.setPixel(baseX + toolManager_->pencilTileX(),
                 baseY + toolManager_->pencilTileY(),
                 Color(nativeColor.realR(),
                       nativeColor.realG(),
                       nativeColor.realB(),
                       Color::fullAlphaOpacity)); */
    }
    break;
  default:
    break;
  }
  
  // Scale
  if (toolManager_->scale() == 1.00) {
    dst.copy(buffer_,
             Box(0, 0, buffer_.w() * toolManager_->scale(),
                       buffer_.h() * toolManager_->scale()),
            Graphic::transUpdate);
  }
  else {
    buffer_.scale(dst, Box(0, 0,
                           buffer_.w() * toolManager_->scale(),
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
  
  if (toolManager_->collisionViewEnabled()) {
//    std::cout << dimensions.x() << " " << dimensions.y() << std::endl;
    int centerX = dimensions.x()- toolManager_->mapping().offsetX();
    int centerY = dimensions.y()- toolManager_->mapping().offsetY();

    dst.drawRectBorder((centerX
                         - toolManager_->mapping().collisionXLength())
                         * toolManager_->scale(),
                       (centerY
                         - toolManager_->mapping().collisionYLength())
                         * toolManager_->scale(),
                       (((toolManager_->mapping().collisionXLength()) * 2)
                          + 0)
                         * toolManager_->scale(),
                       (((toolManager_->mapping().collisionYLength()))
                          + 0)
                         * toolManager_->scale(),
                       Color(0xFF, 0x00, 0x00, Color::fullAlphaOpacity),
                       2);
                       
    // Crosshair on centerpoint
/*    dst.drawLine((centerX - 2) * toolManager_->scale(),
                 (centerY) * toolManager_->scale(),
                 (centerX + 2) * toolManager_->scale(),
                 (centerY) * toolManager_->scale(),
                 Color(0x00, 0x00, 0xFF, Color::fullAlphaOpacity),
                 2);
    dst.drawLine((centerX) * toolManager_->scale(),
                 (centerY - 2) * toolManager_->scale(),
                 (centerX) * toolManager_->scale(),
                 (centerY + 2) * toolManager_->scale(),
                 Color(0x00, 0x00, 0xFF, Color::fullAlphaOpacity),
                 2); */
  }
}
  
void GraphicMappingEditorLayer::enterMouse() {
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    toolManager_->setPencilPreviewEnabled(true);
    break;
  default:
    break;
  }
}

void GraphicMappingEditorLayer::exitMouse() {
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    toolManager_->setPencilPreviewEnabled(false);
    break;
  default:
    break;
  }
}

void GraphicMappingEditorLayer::moveMouse(InputEventData eventData) {
  switch (toolManager_->currentTool()) {
  case GraphicsEditorTools::pencil:
    updatePencil(eventData);
    drawPencil(eventData);
    break;
  default:
    break;
  }
}

void GraphicMappingEditorLayer::pressMouse(InputEventData eventData) {
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

void GraphicMappingEditorLayer::releaseMouse(InputEventData eventData) {
  
}

void GraphicMappingEditorLayer::doubleClickMouse(InputEventData eventData) {
  
}
  
int GraphicMappingEditorLayer::nativeWidth() {
  if (!(toolManager_->mappingExists())) {
    return 0;
  }

  Box dimensions = MappingAssembler::computeDimensionsOfMapping(
    toolManager_->mappingCoordinateTable());
  
//  Box dimensions = MappingAssembler::computeRealDimensionsOfMapping(
//    toolManager_->mappingCoordinateTable(),
//    toolManager_->mapping().offsetX(),
//    toolManager_->mapping().offsetY());
  
  return dimensions.w();
}

int GraphicMappingEditorLayer::nativeHeight() {
  if (!(toolManager_->mappingExists())) {
    return 0;
  }

  Box dimensions = MappingAssembler::computeDimensionsOfMapping(
    toolManager_->mappingCoordinateTable());
  
//  Box dimensions = MappingAssembler::computeRealDimensionsOfMapping(
//    toolManager_->mappingCoordinateTable(),
//    toolManager_->mapping().offsetX(),
//    toolManager_->mapping().offsetY());
  
  return dimensions.h();
}

int GraphicMappingEditorLayer::realToNative(int coordinate) {
  return (coordinate / toolManager_->scale());
}

void GraphicMappingEditorLayer::updatePencil(InputEventData eventData) {
  int nativeX = realToNative(eventData.x());
  int nativeY = realToNative(eventData.y());
  
  TileSetPixelIdentifier pos
      = GraphicMappingMath::findTilePositionInMapping(
            toolManager_->mapping(),
            toolManager_->mappingCoordinateTable(),
            toolManager_->mappingTileIndexTable(),
            toolManager_->mappingEntry(),
            nativeX, nativeY);
  
  if (pos.tileNum() < 0) {
    toolManager_->setPencilTileIndex(-1);
  }
  else {
    toolManager_->setPencilTileIndex(pos.tileNum());
    toolManager_->setPencilTileX(pos.x());
    toolManager_->setPencilTileY(pos.y());
  }
}

void GraphicMappingEditorLayer::drawPencil(InputEventData eventData) {
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

void GraphicMappingEditorLayer::drawPencilPreview(Graphic& nativeBuf) {
  if ((toolManager_->pencilPreviewEnabled())
      && (toolManager_->pencilTileIndex() >= 0)
      && (toolManager_->pencilTileIndex() <
            toolManager_->tiles().numTiles())) {
            
    Box dimensions = MappingAssembler::computeDimensionsOfMapping(
      toolManager_->mappingCoordinateTable());
    int centerX = dimensions.x();
    int centerY = dimensions.y();
    
    int targetIndex = toolManager_->pencilTileIndex()
                      - toolManager_->mappingEntry().tileOffset;
  
    for (int i = toolManager_->mappingCoordinateTable().size() - 1;
         i >= 0;
         i--) {
      SpriteMappingCoordinateTableEntry entry
        = toolManager_->mappingCoordinateTable().entry(i);
        
      int index = toolManager_->mappingTileIndexTable().tileIndex(i);
      int x = entry.offsetX() + centerX;
      int y = entry.offsetY() + centerY;
      
      if (targetIndex == index + 1) {
        ++index;
        y += GGTile::height;
      }
      else if (targetIndex != index) {
        continue;
      }
      
      GGColor nativeColor = toolManager_->palette()[
                   toolManager_->currentColorIndex()];
      buffer_.setPixel(x + toolManager_->pencilTileX(),
                 y + toolManager_->pencilTileY(),
                 Color(nativeColor.realR(),
                       nativeColor.realG(),
                       nativeColor.realB(),
                       Color::fullAlphaOpacity));
    }
  }
}


};
