#include "editors/GraphicsEditorToolManager.h"
#include <cstdlib>

namespace Tales {


GraphicsEditorToolManager::GraphicsEditorToolManager()
  : currentTool_(GraphicsEditorTools::pencil),
    scale_(1.00),
    palette_(NULL),
    tiles_(NULL),
    mapping_(NULL),
    mappingCoordinateTable_(NULL),
    mappingTileIndexTable_(NULL),
    mappingEntry_(0, 0, ""),
    gridEnabled_(true),
    collisionViewEnabled_(true),
    transOption_(Graphic::tileTrans),
    currentColorIndex_(0),
    pencilPreviewEnabled_(false),
    pencilTileIndex_(0),
    pencilTileX_(0),
    pencilTileY_(0) { };
  
GraphicsEditorTools::GraphicsEditorTool GraphicsEditorToolManager
    ::currentTool() const {
  return currentTool_;
}

void GraphicsEditorToolManager::changeCurrentTool(
    GraphicsEditorTools::GraphicsEditorTool currentTool__) {
  pencilPreviewEnabled_ = false;
    
  currentTool_ = currentTool__;
}
      
double GraphicsEditorToolManager::scale() {
  return scale_;
}

void GraphicsEditorToolManager::setScale(double scale__) {
  scale_ = scale__;
}

GGPalette& GraphicsEditorToolManager::palette() {
  return *palette_;
}

void GraphicsEditorToolManager::setPalette(GGPalette& palette__) {
  palette_ = &palette__;
}
  
GGTileSet& GraphicsEditorToolManager::tiles() {
  return *tiles_;
}

void GraphicsEditorToolManager::setTiles(GGTileSet& tiles__) {
  tiles_ = &tiles__;
}
  
SpriteMapping& GraphicsEditorToolManager::mapping() {
  return *mapping_;
}

void GraphicsEditorToolManager::setMapping(SpriteMapping& mapping__) {
  mapping_ = &mapping__;
}

SpriteMappingCoordinateTable& GraphicsEditorToolManager
    ::mappingCoordinateTable() {
  return *mappingCoordinateTable_;
}

void GraphicsEditorToolManager
    ::setMappingCoordinateTable(SpriteMappingCoordinateTable&
    mappingCoordinateTable__) {
  mappingCoordinateTable_ = &mappingCoordinateTable__;
}

SpriteMappingTileIndexTable& GraphicsEditorToolManager
    ::mappingTileIndexTable() {
  return *mappingTileIndexTable_;
}

void GraphicsEditorToolManager
    ::setMappingTileIndexTable(SpriteMappingTileIndexTable&
    mappingTileIndexTable__) {
  mappingTileIndexTable_ = &mappingTileIndexTable__;
}
  
GraphicToMappingEntry& GraphicsEditorToolManager
    ::mappingEntry() {
  return mappingEntry_;
}

void GraphicsEditorToolManager
    ::setMappingEntry(GraphicToMappingEntry&
    mappingEntry__) {
  mappingEntry_ = mappingEntry__;
}
      
bool GraphicsEditorToolManager
    ::gridEnabled() {
  return gridEnabled_;
}

void GraphicsEditorToolManager
    ::setGridEnabled(bool gridEnabled__) {
  gridEnabled_ = gridEnabled__;
}
  
Graphic::TileTransferTransOption GraphicsEditorToolManager
    ::transOption() {
  return transOption_;
}

void GraphicsEditorToolManager
    ::setTransOption(Graphic::TileTransferTransOption transOption__) {
  transOption_ = transOption__;
}
  
int GraphicsEditorToolManager
    ::currentColorIndex() {
  return currentColorIndex_;
}

void GraphicsEditorToolManager
    ::setCurrentColorIndex(int currentColorIndex__) {
  currentColorIndex_ = currentColorIndex__;
}
  
bool GraphicsEditorToolManager
    ::pencilPreviewEnabled() {
  return pencilPreviewEnabled_;
}

int GraphicsEditorToolManager
    ::pencilTileIndex() {
  return pencilTileIndex_;
}

int GraphicsEditorToolManager
    ::pencilTileX() {
  return pencilTileX_;
}

int GraphicsEditorToolManager
    ::pencilTileY() {
  return pencilTileY_;
}

void GraphicsEditorToolManager
    ::setPencilPreviewEnabled(bool pencilPreviewEnabled__) {
  pencilPreviewEnabled_ = pencilPreviewEnabled__;
}

void GraphicsEditorToolManager
    ::setPencilTileIndex(int pencilTileIndex__) {
  pencilTileIndex_ = pencilTileIndex__;
}

void GraphicsEditorToolManager
    ::setPencilTileX(int pencilTileX__) {
  pencilTileX_ = pencilTileX__;
}

void GraphicsEditorToolManager
    ::setPencilTileY(int pencilTileY__) {
  pencilTileY_ = pencilTileY__;
}
  
bool GraphicsEditorToolManager
    ::mappingExists() {
  return (mapping_ != NULL);
}

void GraphicsEditorToolManager
    ::clearMapping() {
  mapping_ = NULL;
  mappingCoordinateTable_ = NULL;
  mappingTileIndexTable_ = NULL;
}
      
bool GraphicsEditorToolManager
    ::collisionViewEnabled() {
  return collisionViewEnabled_;
}

void GraphicsEditorToolManager
    ::setCollisionViewEnabled(bool collisionViewEnabled__) {
  collisionViewEnabled_ = collisionViewEnabled__;
}


};
