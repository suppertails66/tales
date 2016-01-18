#include "editors/VRAMEditorLayeredGraphicScene.h"
#include "structs/GenericGraphicSceneLayer.h"
#include "structs/BitmapGraphicSceneObject.h"
#include "structs/BoxGraphicSceneObject.h"
#include "editors/EditorMetadata.h"

namespace Tales {


const Color VRAMEditorLayeredGraphicScene::selectionBoxColor(
  Color(255, 0, 0, Color::fullAlphaOpacity));
const Color VRAMEditorLayeredGraphicScene::fullGraphicSelectionBoxColor(
  Color(255, 255, 0, Color::fullAlphaOpacity));
const Color VRAMEditorLayeredGraphicScene::leafBoxColor(
  Color(0, 192, 0, Color::fullAlphaOpacity));
const Color VRAMEditorLayeredGraphicScene::smokePuffBoxColor(
  Color(255, 136, 136, Color::fullAlphaOpacity));
const Color VRAMEditorLayeredGraphicScene::waterSplashBoxColor(
  Color(128, 255, 255, Color::fullAlphaOpacity));
    
VRAMEditorLayeredGraphicScene::VRAMEditorLayeredGraphicScene(
                  LevelVRAMEditor& parentEditor__,
                  EditableLevelGraphicsData& levelGraphicsData__,
                  EditableLevelPaletteHeaders& paletteHeaders__,
                  EditableStandardPalettes& palettes__,
                  EditableLeafGraphicsTable& leafGraphicsTable__,
                  EditableSmokePuffGraphicTable& smokePuffGraphicTable__,
                  EditableWaterSplashGraphicTable& waterSplashGraphicTable__)
  : LayeredGraphicScene(),
    parentEditor_(parentEditor__),
    levelGraphicsData_(levelGraphicsData__),
    paletteHeaders_(paletteHeaders__),
    palettes_(palettes__),
    leafGraphicsTable_(leafGraphicsTable__),
    smokePuffGraphicTable_(smokePuffGraphicTable__),
    waterSplashGraphicTable_(waterSplashGraphicTable__),
    g_(nativeWidth(),
       nativeHeight()),
    grid_(8,
          1,
          Color(160, 160, 160, Color::fullAlphaOpacity),
          false),
    gridEnabled_(true),
    areaNum_(1),
    mapNum_(1),
    selectionBoxEnabled_(false),
    selectionBoxX_(0),
    selectionBoxY_(0),
    fullSelectionBoxEnabled_(false),
    fullSelectionBoxGraphicIndex_(0),
    tilePickerPreviewEnabled_(false),
    tilePickerPreviewIndex_(0),
    tilePickerPreviewLength_(0),
    showLeaf_(true),
    showSmokePuff_(true),
    showWaterSplash_(true) { };
  
void VRAMEditorLayeredGraphicScene::render(
                    Graphic& dst,
                    Box srcbox,
                    double scale) {
  // Create empty graphic with white background (TODO: selectable BG color)
  // The normal background color is black, so unused tiles will show up
  // as white
//  Graphic g(nativeWidth(), nativeHeight());
//  g.clear(Color(0, 0, 0, 0));
  g_.clear();
  
  // Get level graphics header containing graphics to render
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  // Look up palette header for this level
  LevelPaletteHeader& levelPaletteHeader
    = paletteHeaders_.headerByIndex(
        paletteHeaders_.indexOfMapNum(areaNum_,
                                      mapNum_));
  
  // Get level palettes
  GGPalette palette0
    = palettes_.palette(levelPaletteHeader.palette0Index());
  GGPalette palette1
    = palettes_.palette(levelPaletteHeader.palette1Index());
  
  // Get map graphic index
  int mapGraphicIndex = levelGraphicsHeader.mapGraphicIndex();
  
  // Get map graphic
  GGTileSet mapGraphic
    = levelGraphicsData_.compressedGraphic(mapGraphicIndex);
  
  // Get index of the start of the map tiles
  int mapTileIndex
    = vramAddressToTileIndex(levelGraphicsHeader.vdpWriteAddress());
    
  // Render map graphic
  renderTiles(g_,
              mapTileIndex,
              mapGraphic,
              palette0,
              Graphic::noTileTrans);
    
  // Get object graphics header index
  int objectGraphicsHeaderIndex
    = levelGraphicsHeader.objectGraphicsHeaderIndex();
    
  // Get object graphics header
  ObjectGraphicsHeader& objectGraphicsHeader
    = levelGraphicsData_.objectGraphicsHeader(objectGraphicsHeaderIndex);
    
  // Iterate over graphics subheaders and add object graphics to render
  for (int i = 0; i < objectGraphicsHeader.size(); i++) {
    ObjectGraphicSubheader& subheader
      = objectGraphicsHeader.subheader(i);
    
    int objectGraphicIndex = subheader.objectGraphicIndex();
    
    // Get graphic
    GGTileSet objectGraphic
      = levelGraphicsData_.compressedGraphic(objectGraphicIndex);
      
    // Flip tiles if horizontal flip flag is set
    if (subheader.substitutionOption()
          == ObjectGraphicSubheader::substitutionEnabled) {
      for (int j = 0; j < objectGraphic.numTiles(); j++) {
        objectGraphic[j].flipHorizontal();
      }
    }
    
    // Get index of the tile
    int tileIndex = vramAddressToTileIndex(subheader.vdpWriteAddress());
    
    // Render object graphic.
    // Use palette 1 (sprite palette) for objects.
    // Technically we "should" use transparency here, but it's possible
    // to overwrite one graphic with another and we don't want to leave
    // scraps of the previous graphic visible when that happens.
    // TODO: add some concept of background color (maybe change color 0
    // in palette?)
    renderTiles(g_,
                tileIndex,
                objectGraphic,
                palette1,
                Graphic::noTileTrans);
    
    // Draw full graphic selection box if enabled and needed
    // (this will be scaled with the graphic, negating the benefits of vector-
    // based drawing!)
    if ((i == fullSelectionBoxGraphicIndex_)
        && fullSelectionBoxEnabled_) {
        
/*      // Draw line on left side of first tile
      int firstXPos = tileIndexToXPos(tileIndex);
      int firstYPos = tileIndexToYPos(tileIndex);
      g.drawLine(firstXPos, firstYPos,
                 firstXPos, firstYPos + GGTile::height,
                 Color(255, 255, 255, Color::fullAlphaOpacity),
                 2,
                 Graphic::noTransUpdate);
        
      // Draw line on right side of last tile
      int lastXPos = tileIndexToXPos(tileIndex + objectGraphic.numTiles());
      int lastYPos = tileIndexToYPos(tileIndex + objectGraphic.numTiles());
      g.drawLine(lastXPos + GGTile::width, lastYPos,
                 lastXPos + GGTile::width, lastYPos + GGTile::height,
                 Color(255, 255, 255, Color::fullAlphaOpacity),
                 2,
                 Graphic::noTransUpdate);
      
      // Box each tile in the graphic
      for (int j = 0; j < objectGraphic.numTiles(); j++) {
        // Calculate position in Graphic
        int xPos = tileIndexToXPos(tileIndex);
        int yPos = tileIndexToYPos(tileIndex);
        
        // Draw lines above and below tile
        g.drawLine(xPos, yPos,
                   xPos + GGTile::width, yPos,
                   Color(255, 255, 255, Color::fullAlphaOpacity),
                   2,
                   Graphic::noTransUpdate);
        g.drawLine(xPos, yPos + GGTile::height,
                   xPos + GGTile::width, yPos + GGTile::height,
                   Color(255, 255, 255, Color::fullAlphaOpacity),
                   2,
                   Graphic::noTransUpdate);
        
        // Move to next tile position
        ++tileIndex;
      } */
      
/*      for (int j = 0; j < objectGraphic.numTiles(); j++) {
        // Calculate position in Graphic
        int xPos = tileIndexToXPos(tileIndex + j);
        int yPos = tileIndexToYPos(tileIndex + j);
        BoxGraphicSceneObject box(Color(255, 0, 255, Color::fullAlphaOpacity),
                                  2,
                                  GGTile::width,
                                  GGTile::height,
                                  xPos,
                                  yPos,
                                  true);
        
        box.render(g,
                   Box(0, 0, dst.w(), dst.h()),
                   1.00);
      } */
    }
  }
    
/*  GenericGraphicSceneLayer graphics;
  Graphic testG(nativeWidth(), nativeHeight());
  renderTiles(testG,
              0,
              mapGraphic,
              palette0,
              Graphic::noTileTrans);
  BitmapGraphicSceneObject* testBitmap
    = new BitmapGraphicSceneObject(testG,
                           0,
                           0,
                           true);
  graphics.addObject(testBitmap);
  graphics.render(g,
                  Box(0, 0, nativeWidth(), nativeHeight()),
                  1.00,
                  1.00); */
                  
/*  GenericGraphicSceneLayer graphics;
  BoxGraphicSceneObject* testBox
    = new BoxGraphicSceneObject(Color(255, 0, 0, 0),
                                3,
                                45,
                                45,
                                20,
                                20,
                                true);
  graphics.addObject(testBox);
  graphics.render(g,
                  Box(0, 0, nativeWidth(), nativeHeight()),
                  3.00,
                  1.00); */
              
  int width = srcbox.w();
  int height = srcbox.h();
  
  // If width or height parameter is zero, replace with maximum
  if (width == 0) {
    width = nativeWidth();
  }
  
  if (height == 0) {
    height = nativeHeight();
  }
              
  // Crop if necessary
  if ((srcbox.x() != 0) || (srcbox.y() != 0)) {
    Graphic tmp(width, height);
    
    // Copy desired portion to temp graphic
    tmp.copy(g_,
             Box(0, 0, width, height),
             Box(srcbox.x(),
                 srcbox.y(),
                 width,
                 height),
             Graphic::noTransUpdate);
             
    // Copy temp graphic to primary
    g_ = tmp;
  }
  
  // Scale graphic if necessary
  if (scale == 1.00) {
    dst = g_;
  }
  else {
//    dst = Graphic(width * scale, height * scale);
    g_.scale(dst,
             Box(0, 0, width * scale, height * scale),
             Graphic::noTransUpdate);
  }
    
  // Draw grid if enabled
  if (gridEnabled_) {
    grid_.render(dst,
                 Box(srcbox.x(),
                     srcbox.y(),
                     width * scale,
                     height * scale),
                 scale);
  }
  
  if (EditorMetadata::areaNumHasVRAMIndices(areaNum_)) {
//    std::cerr << areaNum_ << " " << mapNum_ << std::endl;
    // Draw leaf box if enabled
    if (showLeaf_) {
      boxGenericLength(dst,
                       leafGraphicsTable_.entry(areaNum_),
                       EditableLeafGraphicsTable::numGraphicTiles,
                       leafBoxColor,
                       2,
                       scale);
    }
    
    // Draw water splash box if enabled
    if (showWaterSplash_) {
      boxGenericLength(dst,
                       waterSplashGraphicTable_.entry(areaNum_, mapNum_)
                        .leftTileIndex(),
                       EditableWaterSplashGraphicTable::numGraphicTiles,
                       waterSplashBoxColor,
                       2,
                       scale);
    }
    
    // Draw smoke puff box if enabled
    if (showSmokePuff_) {
      boxGenericLength(dst,
                       smokePuffGraphicTable_.entry(areaNum_, mapNum_)
                        .leftTileIndex(),
                       EditableSmokePuffGraphicTable::numGraphicTiles,
                       smokePuffBoxColor,
                       2,
                       scale);
    }
  }
  
  // Draw full graphic selection box if enabled
  if (fullSelectionBoxEnabled_) {
    ObjectGraphicSubheader& subheader
      = objectGraphicsHeader.subheader(fullSelectionBoxGraphicIndex_);
    
    int tileIndex = vramAddressToTileIndex(subheader.vdpWriteAddress());
    GGTileSet objectGraphic
      = levelGraphicsData_.compressedGraphic(
          subheader.objectGraphicIndex());
    
    // Box each tile in the graphic
    for (int i = 0; i < objectGraphic.numTiles(); i++) {
      // Calculate position in Graphic
      int xPos = tileIndexToXPos(tileIndex);
      int yPos = tileIndexToYPos(tileIndex);
    
      BoxGraphicSceneObject box(fullGraphicSelectionBoxColor,
                                2,
                                GGTile::width * scale,
                                GGTile::height * scale,
                                xPos * scale,
                                yPos * scale,
                                true);
      
      box.render(dst,
                 Box(0, 0, dst.w(), dst.h()),
                 1.00);
      
      // Move to next tile position
      ++tileIndex;
    }
  }
  
  // Draw selection box if enabled
  if (selectionBoxEnabled_) {
    BoxGraphicSceneObject box(selectionBoxColor,
                              3,
                              GGTile::width * scale,
                              GGTile::height * scale,
                              (selectionBoxX_ - srcbox.x())
                                * GGTile::width * scale,
                              (selectionBoxY_ - srcbox.y())
                                * GGTile::height * scale,
                              true);
    
    box.render(dst,
               Box(0, 0, dst.w(), dst.h()),
               1.00);
  }
  
  // Draw tile picker selection box if enabled
  if (tilePickerPreviewEnabled_) {
      boxGenericLength(dst,
                       tilePickerPreviewIndex_,
                       tilePickerPreviewLength_,
                       tilePickerPreviewColor_,
                       2,
                       scale);
  }
}
                      
void VRAMEditorLayeredGraphicScene::refresh() {
  changeMap(areaNum_,
            mapNum_);
}
  
int VRAMEditorLayeredGraphicScene::tileIndexToXPos(int tileIndex) const {
  return (tileIndex % tilesPerRow_) * GGTile::width;
}

int VRAMEditorLayeredGraphicScene::tileIndexToYPos(int tileIndex) const {
  return (tileIndex / tilesPerRow_) * GGTile::height;
}
  
int VRAMEditorLayeredGraphicScene::tilePosToTileIndex(int tileX, int tileY) {
  return (tileY * tilesPerRow()) + tileX;
}
  
bool VRAMEditorLayeredGraphicScene::showLeaf() const {
  return showLeaf_;
}

void VRAMEditorLayeredGraphicScene::setShowLeaf(bool showLeaf__) {
  showLeaf_ = showLeaf__;
}

bool VRAMEditorLayeredGraphicScene::showSmokePuff() const {
  return showSmokePuff_;
}

void VRAMEditorLayeredGraphicScene::setShowSmokePuff(bool showSmokePuff__) {
  showSmokePuff_ = showSmokePuff__;
}

bool VRAMEditorLayeredGraphicScene::showWaterSplash() const {
  return showWaterSplash_;
}

void VRAMEditorLayeredGraphicScene
    ::setShowWaterSplash(bool showWaterSplash__) {
  showWaterSplash_ = showWaterSplash__;
}
                      
void VRAMEditorLayeredGraphicScene
    ::findAndHandleTopGraphicIndex(int tileIndex) {
  // Get level graphics header containing graphics
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  // Get object graphics header index
  int objectGraphicsHeaderIndex
    = levelGraphicsHeader.objectGraphicsHeaderIndex();
    
  // Get object graphics header
  ObjectGraphicsHeader& objectGraphicsHeader
    = levelGraphicsData_.objectGraphicsHeader(objectGraphicsHeaderIndex);
    
  // Search through subheaders backwards (so we find uppermost graphics first)
  for (int i = objectGraphicsHeader.size() - 1; i >= 0; i--) {
//    std::cout << "checking " << i << std::endl;
    ObjectGraphicSubheader& subheader
      = objectGraphicsHeader.subheader(i);
    
    int objectGraphicIndex = subheader.objectGraphicIndex();
    
    // Get graphic
    GGTileSet objectGraphic
      = levelGraphicsData_.compressedGraphic(objectGraphicIndex);
    
    // Get index of the tile
    int firstTileIndex = vramAddressToTileIndex(subheader.vdpWriteAddress());
    
    // Check if one of this graphic's tiles is at the target index
    if ((tileIndex >= firstTileIndex)
        && (tileIndex < firstTileIndex + objectGraphic.numTiles())) {
      
      // Enable full selection box
      fullSelectionBoxEnabled_ = true;
      fullSelectionBoxGraphicIndex_ = i;
      
      // Stop at first match found
//      std::cout << "match index: " << i << std::endl;
      return;
    }
  }
  
  // No match found: disable selector box
//  std::cout << "no match" << std::endl;
  fullSelectionBoxEnabled_ = false;
}
                      
void VRAMEditorLayeredGraphicScene::changeMap(
               int areaNum__,
               int mapNum__) {
  // Disable graphic selection box (otherwise we'll select a completely
  // different or possibly nonexistent graphic on the new map)
  fullSelectionBoxEnabled_ = false;
  
  areaNum_ = areaNum__;
  mapNum_ = mapNum__;
}
                 
bool VRAMEditorLayeredGraphicScene::gridEnabled() const {
  return gridEnabled_;
}

void VRAMEditorLayeredGraphicScene::setGridEnabled(bool gridEnabled__) {
  gridEnabled_ = gridEnabled__;
}
  
bool VRAMEditorLayeredGraphicScene::selectionBoxEnabled() const {
  return selectionBoxEnabled_;
}

int VRAMEditorLayeredGraphicScene::selectionBoxX() const {
  return selectionBoxX_;
}

int VRAMEditorLayeredGraphicScene::selectionBoxY() const {
  return selectionBoxY_;
}

void VRAMEditorLayeredGraphicScene
    ::setSelectionBoxEnabled(bool selectionBoxEnabled__) {
  selectionBoxEnabled_ = selectionBoxEnabled__;
}

void VRAMEditorLayeredGraphicScene
    ::setSelectionBoxX(int selectionBoxX__) {
  selectionBoxX_ = selectionBoxX__;
}

void VRAMEditorLayeredGraphicScene
    ::setSelectionBoxY(int selectionBoxY__) {
  selectionBoxY_ = selectionBoxY__;
}
  
bool VRAMEditorLayeredGraphicScene
    ::fullSelectionBoxEnabled() const {
  return fullSelectionBoxEnabled_;
}

int VRAMEditorLayeredGraphicScene
    ::fullSelectionBoxGraphicIndex() const {
  return fullSelectionBoxGraphicIndex_;
}

void VRAMEditorLayeredGraphicScene
    ::setFullSelectionBoxEnabled(bool fullSelectionBoxEnabled__) {
  fullSelectionBoxEnabled_ = fullSelectionBoxEnabled__;
}

void VRAMEditorLayeredGraphicScene
    ::setFullSelectionBoxGraphicIndex(int fullSelectionBoxGraphicIndex__) {
  fullSelectionBoxGraphicIndex_ = fullSelectionBoxGraphicIndex__;
}
  
bool VRAMEditorLayeredGraphicScene
    ::tilePickerPreviewEnabled() const {
  return tilePickerPreviewEnabled_;
}

int VRAMEditorLayeredGraphicScene
    ::tilePickerPreviewIndex() const {
  return tilePickerPreviewIndex_;
}

int VRAMEditorLayeredGraphicScene
    ::tilePickerPreviewLength() const {
  return tilePickerPreviewLength_;
}

Color VRAMEditorLayeredGraphicScene
    ::tilePickerPreviewColor() const {
  return tilePickerPreviewColor_;
}

void VRAMEditorLayeredGraphicScene
    ::setTilePickerPreviewEnabled(bool tilePickerPreviewEnabled__) {
  tilePickerPreviewEnabled_ = tilePickerPreviewEnabled__;
}

void VRAMEditorLayeredGraphicScene
    ::setTilePickerPreviewIndex(int tilePickerPreviewIndex__) {
  tilePickerPreviewIndex_ = tilePickerPreviewIndex__;
}

void VRAMEditorLayeredGraphicScene
    ::setTilePickerPreviewLength(int tilePickerPreviewLength__) {
  tilePickerPreviewLength_ = tilePickerPreviewLength__;
}

void VRAMEditorLayeredGraphicScene
    ::setTilePickerPreviewColor(Color tilePickerPreviewColor__) {
  tilePickerPreviewColor_ = tilePickerPreviewColor__;
}
  
int VRAMEditorLayeredGraphicScene::vramAddressToTileIndex(int vramAddress) {
  return (vramAddress / vramAddressToTileIndexDivisor);
}
  
void VRAMEditorLayeredGraphicScene::boxGenericLength(
                    Graphic& dst,
                    int baseIndex,
                    int numTiles,
                    Color color,
                    int width,
                    double scale) {
  for (int i = 0; i < numTiles; i++) {
    // Calculate position in Graphic
    int xPos = tileIndexToXPos(baseIndex + i);
    int yPos = tileIndexToYPos(baseIndex + i);
  
    BoxGraphicSceneObject box(color,
                              width,
                              GGTile::width * scale,
                              GGTile::height * scale,
                              xPos * scale,
                              yPos * scale,
                              true);
    
    box.render(dst,
               Box(0, 0, dst.w(), dst.h()),
               1.00);
  }
}

int VRAMEditorLayeredGraphicScene::nativeWidth() const {
  return tilesPerRow_ * GGTile::width;
}

int VRAMEditorLayeredGraphicScene::nativeHeight() const {
  return (numVRAMTiles / tilesPerRow_) * GGTile::height;
}
  
int VRAMEditorLayeredGraphicScene::tilesPerRow() const {
  return tilesPerRow_;
}
  
void VRAMEditorLayeredGraphicScene::renderTiles(
                 Graphic& g,
                 int tileIndex,
                 GGTileSet& tiles,
                 GGPalette& palette,
                 Graphic::TileTransferTransOption tileTransOption) {
  // Render each tile and blit to Graphic
  for (int j = 0; j < tiles.numTiles(); j++) {
    // Render tile
    Graphic tileGraphic(tiles[j],
                        palette,
                        tileTransOption);
                        
    // Calculate position in Graphic
    int xPos = tileIndexToXPos(tileIndex);
    int yPos = tileIndexToYPos(tileIndex);
    
    // Blit if transparency is enabled; copy otherwise
    if (tileTransOption == Graphic::tileTrans) {
      g.blit(tileGraphic,
             Box(xPos, yPos, 0, 0),
             Graphic::noTransUpdate);
    }
    else {
      g.copy(tileGraphic,
             Box(xPos, yPos, 0, 0),
             Graphic::noTransUpdate);
    }
    
    // Move to next tile position
    ++tileIndex;
  }
}


}; 
