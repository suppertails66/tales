#include "editors/GraphicsEditor.h"
#include "editors/GraphicToMappings.h"
#include "editors/MappingAssembler.h"
#include "editors/GraphicMappingMath.h"
#include "structs/PngConversion.h"
#include "util/StringConversion.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


GraphicsEditor::GraphicsEditor(
                 EditableLevelGraphicsData& levelGraphicsData__,
                 EditableStandardPalettes& palettes__,
                 EditableSpriteMappings& spriteMappings__,
                 EditorMetadata& metadata__)
  : levelGraphicsData_(levelGraphicsData__),
    palettes_(palettes__),
    spriteMappings_(spriteMappings__),
    metadata_(metadata__),
    editorScene_(levelGraphicsData_,
                 palettes_,
                 spriteMappings_,
                 toolManager_),
    currentPaletteIndex_(0),
    currentGraphicCompressionType_(compressed),
    currentGraphicIndex_(0) {
  changeGraphic(compressed, 0);
}
  
void GraphicsEditor::refresh() {
  
}
  
void GraphicsEditor::drawTileGraphic(Graphic& dst) {
  dst = Graphic(editorScene_.nativeTileLayerWidth()
                  * toolManager_.scale(),
                editorScene_.nativeTileLayerHeight()
                  * toolManager_.scale());

  editorScene_.renderTileLayer(dst,
                               Box(0, 0, editorScene_.nativeTileLayerWidth(),
                                         editorScene_.nativeTileLayerHeight()),
                               toolManager_.scale());
}
  
void GraphicsEditor::drawMappingGraphic(Graphic& dst) {
  dst = Graphic(editorScene_.nativeMappingLayerWidth()
                  * toolManager_.scale(),
                editorScene_.nativeMappingLayerHeight()
                  * toolManager_.scale());

  editorScene_.renderMappingLayer(dst,
                               Box(0, 0,
                                   editorScene_.nativeMappingLayerWidth(),
                                   editorScene_.nativeMappingLayerHeight()),
                               toolManager_.scale());
}

void GraphicsEditor::drawColorPickerGraphic(Graphic& dst) {
  colorPicker_.render(dst,
                       Box(0, 0, colorPicker_.previewWidth(),
                                 colorPicker_.previewHeight()),
                       toolManager_.scale());
}
  
void GraphicsEditor::tileEditorEnterMouse() {
  editorScene_.tileEditorEnterMouse();
}

void GraphicsEditor::tileEditorExitMouse() {
  editorScene_.tileEditorExitMouse();
}

void GraphicsEditor::tileEditorMoveMouse(InputEventData eventData) {
  editorScene_.tileEditorMoveMouse(eventData);
}

void GraphicsEditor::tileEditorPressMouse(InputEventData eventData) {
  editorScene_.tileEditorPressMouse(eventData);
  
  // cheating for dropper tool
  colorPicker_.setPickedIndex(toolManager_.currentColorIndex());
}

void GraphicsEditor::tileEditorReleaseMouse(InputEventData eventData) {
  editorScene_.tileEditorReleaseMouse(eventData);
}

void GraphicsEditor::tileEditorDoubleClickMouse(InputEventData eventData) {
  editorScene_.tileEditorDoubleClickMouse(eventData);
}
  
void GraphicsEditor::mappingEditorEnterMouse() {
  editorScene_.mappingEditorEnterMouse();
}

void GraphicsEditor::mappingEditorExitMouse() {
  editorScene_.mappingEditorExitMouse();
}

void GraphicsEditor::mappingEditorMoveMouse(InputEventData eventData) {
  editorScene_.mappingEditorMoveMouse(eventData);
}

void GraphicsEditor::mappingEditorPressMouse(InputEventData eventData) {
  editorScene_.mappingEditorPressMouse(eventData);
  
  // cheating for dropper tool
  colorPicker_.setPickedIndex(toolManager_.currentColorIndex());
}

void GraphicsEditor::mappingEditorReleaseMouse(InputEventData eventData) {
  editorScene_.mappingEditorReleaseMouse(eventData);
}

void GraphicsEditor::mappingEditorDoubleClickMouse(InputEventData eventData) {
  editorScene_.mappingEditorDoubleClickMouse(eventData);
}
  
void GraphicsEditor::changeTool(GraphicsEditorTools::GraphicsEditorTool tool) {
  toolManager_.changeCurrentTool(tool);
}
  
void GraphicsEditor::colorPickerEnterMouse() {
  colorPicker_.enterMouse();
}

void GraphicsEditor::colorPickerExitMouse() {
  colorPicker_.exitMouse();
}

void GraphicsEditor::colorPickerMoveMouse(InputEventData eventData) {
  colorPicker_.moveMouse(eventData);
}

void GraphicsEditor::colorPickerPressMouse(InputEventData eventData) {
  colorPicker_.pressMouse(eventData);
}

void GraphicsEditor::colorPickerReleaseMouse(InputEventData eventData) {
  colorPicker_.releaseMouse(eventData);
}

void GraphicsEditor::colorPickerDoubleClickMouse(InputEventData eventData) {
  colorPicker_.doubleClickMouse(eventData);
}
  
void GraphicsEditor::setScale(double scale__) {
  toolManager_.setScale(scale__);
}
                     
void GraphicsEditor::setGridEnabled(bool gridEnabled__) {
  toolManager_.setGridEnabled(gridEnabled__);
}
  
void GraphicsEditor::setTransparencyEnabled(bool transparencyEnabled__) {
  if (transparencyEnabled__) {
    toolManager_.setTransOption(Graphic::tileTrans);
  }
  else {
    toolManager_.setTransOption(Graphic::noTileTrans);
  }
}
  
void GraphicsEditor::changeGraphic(GraphicCompressionType compressionType,
                                   int index) {
  currentGraphicCompressionType_ = compressionType;
  currentGraphicIndex_ = index;
  
  switch (compressionType) {
  case uncompressed:
    toolManager_.setTiles(levelGraphicsData_.uncompressedGraphic(index));
    break;
  case compressed:
    toolManager_.setTiles(levelGraphicsData_.compressedGraphic(index));
    break;
  default:
    break;
  }
  
  // look up default palette
  switch (compressionType) {
  case uncompressed:
    setCurrentPaletteIndex(
      uncompressedGraphicPaletteDefault(index));
    break;
  case compressed:
    setCurrentPaletteIndex(
      compressedGraphicPaletteDefault(index));
    break;
  default:
    break;
  }
  
  // do sprite mapping stuff
  GraphicToMappings::CompressionType localType = getLocalType(compressionType);
  
  if (GraphicToMappings::numMappingsForGraphic(localType, index) > 0) {
    // load first mapping if one exists
    changeMapping(0);
  }
  else {
    // if no mapping exists, clear
    toolManager_.clearMapping();
  }
}
  
int GraphicsEditor::numCompressedGraphics() {
  return levelGraphicsData_.compressedGraphicsSize();
}

int GraphicsEditor::numUncompressedGraphics() {
  return levelGraphicsData_.uncompressedGraphicsSize();
}

int GraphicsEditor::numPalettes() {
  return palettes_.size();
}
  
int GraphicsEditor::currentPaletteIndex() {
  return currentPaletteIndex_;
}

void GraphicsEditor::setCurrentPaletteIndex(int index) {
  currentPaletteIndex_ = index;
  
  toolManager_.setPalette(palettes_.palette(index));
  
  colorPicker_.setPalette(palettes_.palette(index));
}
  
int GraphicsEditor::currentColorIndex() {
  return toolManager_.currentColorIndex();
}
  
void GraphicsEditor::setCurrentColorIndex(int index) {
  toolManager_.setCurrentColorIndex(index);
}
  
int GraphicsEditor::colorPickerWidth() {
  return colorPicker_.previewWidth();
}

int GraphicsEditor::colorPickerHeight() {
  return colorPicker_.previewHeight();
}

int GraphicsEditor::colorPickerCurrentIndex() {
  return colorPicker_.pickedIndex();
}
  
int GraphicsEditor::tileEditorWidth() {
  return editorScene_.nativeTileLayerWidth()
            * toolManager_.scale();
}

int GraphicsEditor::tileEditorHeight() {
  return editorScene_.nativeTileLayerHeight()
            * toolManager_.scale();
}
  
int GraphicsEditor::mappingEditorWidth() {
  return editorScene_.nativeMappingLayerWidth()
            * toolManager_.scale();
}

int GraphicsEditor::mappingEditorHeight() {
  return editorScene_.nativeMappingLayerHeight()
            * toolManager_.scale();
}
  
bool GraphicsEditor::mappingExists() {
  return (toolManager_.mappingExists());
}

SpriteMapping& GraphicsEditor::currentMapping() {
  return toolManager_.mapping();
}
  
GGTileSet& GraphicsEditor::currentGraphic() {
  switch (currentGraphicCompressionType_) {
  case uncompressed:
    return levelGraphicsData_.uncompressedGraphic(currentGraphicIndex_);
    break;
  case compressed:
    return levelGraphicsData_.compressedGraphic(currentGraphicIndex_);
    break;
  default:
    break;
  }
}
  
void GraphicsEditor::changeMapping(int mappingSubIndex) {
  GraphicToMappings::CompressionType localType = getLocalType(
      currentGraphicCompressionType_);
  
  GraphicToMappingEntry entry = GraphicToMappings::graphicMapping(
      localType,
      currentGraphicIndex_,
      mappingSubIndex);
  
  toolManager_.setMapping(
    spriteMappings_.spriteMapping(entry.mappingIndex));
  toolManager_.setMappingCoordinateTable(
    spriteMappings_.coordinateTable(
      toolManager_.mapping().coordinateTableIndex()));
  toolManager_.setMappingTileIndexTable(
    spriteMappings_.tileIndexTable(
      toolManager_.mapping().tileIndexTableIndex()));
  toolManager_.setMappingEntry(entry);
}
      
bool GraphicsEditor::collisionViewEnabled() {
  return toolManager_.collisionViewEnabled();
}

void GraphicsEditor::setCollisionViewEnabled(bool collisionViewEnabled__) {
  toolManager_.setCollisionViewEnabled(collisionViewEnabled__);
}
  
void GraphicsEditor::setCurrentPaletteDefault(int paletteNum) {
  switch (currentGraphicCompressionType_) {
  case uncompressed:
    setUncompressedGraphicPaletteDefault(currentGraphicIndex_, paletteNum);
    break;
  case compressed:
    setCompressedGraphicPaletteDefault(currentGraphicIndex_, paletteNum);
    break;
  default:
    break;
  }
}
  
int GraphicsEditor
    ::compressedGraphicPaletteDefault(int index) {
  return metadata_.compressedGraphicPaletteDefaults()[index].paletteNum();
}

void GraphicsEditor
    ::setCompressedGraphicPaletteDefault(int index, int paletteNum) {
  metadata_.compressedGraphicPaletteDefaults()[index]
      .setPaletteNum(paletteNum);
}

int GraphicsEditor
    ::uncompressedGraphicPaletteDefault(int index) {
  return metadata_.uncompressedGraphicPaletteDefaults()[index].paletteNum();
}

void GraphicsEditor
    ::setUncompressedGraphicPaletteDefault(int index, int paletteNum) {
  metadata_.uncompressedGraphicPaletteDefaults()[index]
      .setPaletteNum(paletteNum);
}
  
void GraphicsEditor::exportAllTiles(const std::string& folderpath,
                      bool transparency) {
  for (int i = 0; i < numCompressedGraphics(); i++) {
    exportTiles(folderpath, compressed, i, transparency);
  }
  
  for (int i = 0; i < numUncompressedGraphics(); i++) {
    exportTiles(folderpath, uncompressed, i, transparency);
  }
}
  
void GraphicsEditor::exportAllMappings(const std::string& folderpath,
                      bool transparency) {
  for (int i = 0; i < numCompressedGraphics(); i++) {
    exportMappingSet(folderpath, compressed, i, transparency);
  }
  
  for (int i = 0; i < numUncompressedGraphics(); i++) {
    exportMappingSet(folderpath, uncompressed, i, transparency);
  }
}
  
void GraphicsEditor::importAllTiles(const std::string& folderpath) {
  for (int i = 0; i < numCompressedGraphics(); i++) {
    importTiles(folderpath, compressed, i);
  }
  
  for (int i = 0; i < numUncompressedGraphics(); i++) {
    importTiles(folderpath, uncompressed, i);
  }
}

void GraphicsEditor::importAllMappings(const std::string& folderpath) {
  for (int i = 0; i < numCompressedGraphics(); i++) {
    importMappingSet(folderpath, compressed, i);
  }
  
  for (int i = 0; i < numUncompressedGraphics(); i++) {
    importMappingSet(folderpath, uncompressed, i);
  }
}
  
void GraphicsEditor::exportTiles(const std::string& folderpath,
                      GraphicCompressionType comp,
                      int graphicIndex,
                      bool transparency) {
  GraphicToMappings::CompressionType localType = getLocalType(comp);
  
  GGTileSet& tiles = getTileSet(comp, graphicIndex);
  GGPalette& palette = getPalette(comp, graphicIndex);
  
  TwoDByteArray data = tiles.toByteArray(exportTilesPerRow_);
  
  PngConversion::twoDArrayToIndexedPngGG(
    folderpath + graphicToFilename(comp, graphicIndex),
    data,
    palette,
    transparency);
}
  
void GraphicsEditor::exportMappingSet(
                      const std::string& folderpath,
                      GraphicCompressionType comp,
                      int graphicIndex,
                      bool transparency) {
  GraphicToMappings::CompressionType localType = getLocalType(comp);
  
  GGTileSet& tiles = getTileSet(comp, graphicIndex);
  GGPalette& palette = getPalette(comp, graphicIndex);
  
  int numMappings = GraphicToMappings::numMappingsForGraphic(
        localType, graphicIndex);
  
  for (int j = 0; j < numMappings; j++) {
    GraphicToMappingEntry entry = GraphicToMappings::graphicMapping(
          localType,
          graphicIndex,
          j);
    
    SpriteMapping& spriteMapping
        = spriteMappings_.spriteMapping(entry.mappingIndex);
  
    AssembledRawMapping dst;
    MappingAssembler::assembleMappingsRaw(
        dst,
        tiles,
        spriteMapping,
        spriteMappings_.coordinateTable(
            spriteMapping.coordinateTableIndex()),
        spriteMappings_.tileIndexTable(
            spriteMapping.tileIndexTableIndex()),
        ObjectStateInfo::left,
        entry.tileOffset);
    
    PngConversion::twoDArrayToIndexedPngGG(
      folderpath + graphicMappingToFilename(comp, graphicIndex, j),
      dst.data(),
      palette,
      transparency);
  }
}
  
void GraphicsEditor::importTiles(const std::string& folderpath,
                  GraphicCompressionType comp,
                  int graphicIndex) {
  GraphicToMappings::CompressionType localType = getLocalType(comp);
  
  GGTileSet& tiles = getTileSet(comp, graphicIndex);
//  GGPalette& palette = getPalette(comp, graphicIndex);
  
  TwoDByteArray data;
  
  if (!PngConversion::indexedPngToTwoDArrayGG(
    data,
    folderpath + graphicToFilename(comp, graphicIndex))) {
    return;
  }
  
  tiles.fromByteArray(data, exportTilesPerRow_);
}

void GraphicsEditor::importMappingSet(const std::string& folderpath,
                      GraphicCompressionType comp,
                      int graphicIndex) {
  GraphicToMappings::CompressionType localType = getLocalType(comp);
  
  GGTileSet& tiles = getTileSet(comp, graphicIndex);
//  GGPalette& palette = getPalette(comp, graphicIndex);
  
  TwoDByteArray data;
  
  int numMappings = GraphicToMappings::numMappingsForGraphic(
        localType, graphicIndex);
  
  for (int k = 0; k < numMappings; k++) {
    if (!PngConversion::indexedPngToTwoDArrayGG(
        data,
        folderpath + graphicMappingToFilename(comp, graphicIndex, k))) {
//      std::cout << folderpath
//          + graphicMappingToFilename(comp, graphicIndex, k) << std::endl;
      return;
    }
  
    GraphicToMappingEntry entry = GraphicToMappings::graphicMapping(
          localType,
          graphicIndex,
          k);
    
    SpriteMapping& spriteMapping
        = spriteMappings_.spriteMapping(entry.mappingIndex);
    
    for (int j = 0; j < data.h(); j++) {
      for (int i = 0; i < data.w(); i++) {
        TileSetPixelIdentifier pos
            = GraphicMappingMath::findTilePositionInMapping(
                  spriteMapping,
                  spriteMappings_.coordinateTable(
                      spriteMapping.coordinateTableIndex()),
                  spriteMappings_.tileIndexTable(
                      spriteMapping.tileIndexTableIndex()),
                  entry,
                  i, j);
        
        if (pos.tileNum() >= 0) {
          tiles[pos.tileNum()].setPixel(pos.x(), pos.y(), data.data(i, j));
        }
      }
    }
  }
}
                        
GGTileSet& GraphicsEditor::getTileSet(GraphicCompressionType comp,
                      int graphicIndex) {
  switch (comp) {
  case uncompressed:
    return levelGraphicsData_.uncompressedGraphic(
        graphicIndex);
    break;
  case compressed:
  default:
    return levelGraphicsData_.compressedGraphic(
        graphicIndex);
    break;
  }
}

GGPalette& GraphicsEditor::getPalette(GraphicCompressionType comp,
                      int graphicIndex) {
  switch (comp) {
  case uncompressed:
    return palettes_.palette(uncompressedGraphicPaletteDefault(
        graphicIndex));
    break;
  case compressed:
  default:
    return palettes_.palette(compressedGraphicPaletteDefault(
        graphicIndex));
    break;
  }
}
                        
GraphicToMappings::CompressionType GraphicsEditor::getLocalType(
    GraphicCompressionType compressionType) {
  switch (compressionType) {
  case uncompressed:
    return GraphicToMappings::uncompressed;
    break;
  case compressed:
  default:
    return GraphicToMappings::compressed;
    break;
  }
}
  
std::string GraphicsEditor::graphicToFilename(
                      GraphicCompressionType comp,
                      int graphicIndex) {
  std::string filename("grp");
  
  switch (comp) {
  case uncompressed:
    filename += "-uncompr";
    break;
  case compressed:
    filename += "-compr";
    break;
  default:
    break;
  }
  
  filename += "-"
            + StringConversion::toString(graphicIndex)
            + ".png";
  
  return filename;
}
  
std::string GraphicsEditor::graphicMappingToFilename(
                      GraphicCompressionType comp,
                      int graphicIndex,
                      int mappingIndex) {
  std::string filename("grp");
  
  switch (comp) {
  case uncompressed:
    filename += "-uncompr";
    break;
  case compressed:
    filename += "-compr";
    break;
  default:
    break;
  }
  
  filename += "-"
            + StringConversion::toString(graphicIndex)
            + "-mapping-"
            + StringConversion::toString(mappingIndex)
            + ".png";
  
  return filename;
}
  
bool GraphicsEditor::importCurrentGraphic(const std::string& filename) {
  GraphicToMappings::CompressionType localType = getLocalType(
    currentGraphicCompressionType_);
  
  GGTileSet& tiles = currentGraphic();
//  GGPalette& palette = getPalette(comp, graphicIndex);
  
  TwoDByteArray data;
  
  if (!PngConversion::indexedPngToTwoDArrayGG(
                  data,
                  filename)) {
    return false;
  }
  
  tiles.fromByteArray(data, exportTilesPerRow_);
  
  return true;
}

bool GraphicsEditor::exportCurrentGraphic(const std::string& filename,
                                          bool transparency) {
  GraphicToMappings::CompressionType localType = getLocalType(
    currentGraphicCompressionType_);
  
  GGTileSet& tiles = currentGraphic();
  GGPalette& palette = getPalette(currentGraphicCompressionType_,
                                  currentGraphicIndex_);
  
  TwoDByteArray data = tiles.toByteArray(exportTilesPerRow_);
  
  PngConversion::twoDArrayToIndexedPngGG(
    filename,
    data,
    palette,
    transparency);
  
  return true;
}
  
bool GraphicsEditor::importCurrentMapping(const std::string& filename) {
  GraphicToMappings::CompressionType localType = getLocalType(
    currentGraphicCompressionType_);
  
  GGTileSet& tiles = currentGraphic();
//  GGPalette& palette = getPalette(comp, graphicIndex);
  
  TwoDByteArray data;
  
  if (!PngConversion::indexedPngToTwoDArrayGG(
                  data,
                  filename)) {
    return false;
  }

  GraphicToMappingEntry entry
    = toolManager_.mappingEntry();
  
  SpriteMapping& spriteMapping
      = toolManager_.mapping();
  
  for (int j = 0; j < data.h(); j++) {
    for (int i = 0; i < data.w(); i++) {
      TileSetPixelIdentifier pos
          = GraphicMappingMath::findTilePositionInMapping(
                spriteMapping,
                spriteMappings_.coordinateTable(
                    spriteMapping.coordinateTableIndex()),
                spriteMappings_.tileIndexTable(
                    spriteMapping.tileIndexTableIndex()),
                entry,
                i, j);
      
      if (pos.tileNum() >= 0) {
        tiles[pos.tileNum()].setPixel(pos.x(), pos.y(), data.data(i, j));
      }
    }
  }
  
  return true;
}

bool GraphicsEditor::exportCurrentMapping(const std::string& filename,
                                          bool transparency) {
  GraphicToMappings::CompressionType localType = getLocalType(
    currentGraphicCompressionType_);
  
  GGTileSet& tiles = currentGraphic();
  GGPalette& palette = getPalette(currentGraphicCompressionType_,
                                  currentGraphicIndex_);
  
  GraphicToMappingEntry entry
    = toolManager_.mappingEntry();
  
  SpriteMapping& spriteMapping
      = toolManager_.mapping();

  AssembledRawMapping dst;
  MappingAssembler::assembleMappingsRaw(
      dst,
      tiles,
      spriteMapping,
      spriteMappings_.coordinateTable(
          spriteMapping.coordinateTableIndex()),
      spriteMappings_.tileIndexTable(
          spriteMapping.tileIndexTableIndex()),
      ObjectStateInfo::left,
      entry.tileOffset);
  
  PngConversion::twoDArrayToIndexedPngGG(
    filename,
    dst.data(),
    palette,
    transparency);
  
  return true;
}


}; 
