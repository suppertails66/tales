#include "editors/VRAMCache.h"

namespace Tales {


VRAMCache::VRAMCache()
  : cache_(cacheWidth_,
           cacheHeight_),
    horizontalFlipCache_(cacheWidth_,
                         cacheHeight_),
    verticalFlipCache_(cacheWidth_,
                       cacheHeight_),
    bothFlipCache_(cacheWidth_,
                   cacheHeight_) { };
  
  
void VRAMCache::cacheVRAM(
                 EditableLevelGraphicsData& levelGraphicsData_,
                 EditableLevelPaletteHeaders& paletteHeaders_,
                 EditableStandardPalettes& palettes_,
                 int areaNum_,
                 int mapNum_) {
  cache_.clear();
  horizontalFlipCache_.clear();
  verticalFlipCache_.clear();
  bothFlipCache_.clear();
  
  // Get level graphics header containing graphics to render
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
    int tileIndex = subheader.vdpWriteAddress()
                      / GGTile::rawInputDataSize;
    
    // Render object graphic
    renderAllFlips(
                tileIndex,
                objectGraphic,
                palette1,
                Graphic::tileTrans);
  }
  
  // Get map graphic index
  int mapGraphicIndex = levelGraphicsHeader.mapGraphicIndex();
  
  // Get map graphic
  GGTileSet mapGraphic
    = levelGraphicsData_.compressedGraphic(mapGraphicIndex);
  
  // Get index of the start of the map tiles
  int mapTileIndex
    = levelGraphicsHeader.vdpWriteAddress() / GGTile::rawInputDataSize;
    
  // Render map graphic
  renderAllFlips(
              mapTileIndex,
              mapGraphic,
              palette0,
              Graphic::noTileTrans);
}

void VRAMCache::copyTile(Graphic& dst,
              Box dstbox,
              int tileIndex,
              int flipFlags,
              Graphic::TransBlitOption updateTrans) const {
  const Graphic* srcgrp = &cache_;
  
  if ((flipFlags & flipHorizontal) && (flipFlags & flipVertical)) {
    srcgrp = &bothFlipCache_;
  }
  else if ((flipFlags & flipHorizontal)) {
    srcgrp = &horizontalFlipCache_;
  }
  else if ((flipFlags & flipVertical)) {
    srcgrp = &verticalFlipCache_;
  }
  
  dst.copy(*srcgrp,
           dstbox,
           Box(tileIndex * GGTile::width,
               0,
               GGTile::width,
               GGTile::height),
           updateTrans);
}

void VRAMCache::renderAllFlips(
                    int tileIndex,
                    GGTileSet& tiles,
                    GGPalette& palette,
                    Graphic::TileTransferTransOption tileTransOption) {
  // Render to main cache
  renderTiles(cache_,
              tileIndex,
              tiles,
              palette,
              tileTransOption);
  
  // Create flipped variants
  for (int j = 0; j < tiles.numTiles(); j++) {
    tiles[j].flipHorizontal();
  }
  
  renderTiles(horizontalFlipCache_,
              tileIndex,
              tiles,
              palette,
              tileTransOption);
  
  for (int j = 0; j < tiles.numTiles(); j++) {
    tiles[j].flipHorizontal();
    tiles[j].flipVertical();
  }
  
  renderTiles(verticalFlipCache_,
              tileIndex,
              tiles,
              palette,
              tileTransOption);
  
  for (int j = 0; j < tiles.numTiles(); j++) {
    tiles[j].flipHorizontal();
  }
  
  renderTiles(bothFlipCache_,
              tileIndex,
              tiles,
              palette,
              tileTransOption);
}

void VRAMCache::renderTiles(Graphic& g,
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
    int xPos = tileIndex * GGTile::width;
    int yPos = 0;
    
    // Clear the tiles before writing to them to avoid leaving
    // artifacts from previous contents (due to our program's
    // different concept of transparency from the hardware)
    g.fillRect(xPos, yPos, GGTile::width, GGTile::height,
               Color(0xFF, 0xFF, 0xFF, Color::fullAlphaTransparency),
               Graphic::noTransUpdate);
    
    // Blit if transparency is enabled; copy otherwise
    if (tileTransOption == Graphic::tileTrans) {
      g.blit(tileGraphic,
             Box(xPos, yPos, 0, 0),
             Graphic::transUpdate);
    }
    else {
      g.copy(tileGraphic,
             Box(xPos, yPos, 0, 0),
             Graphic::transUpdate);
    }
    
    // Move to next tile position
    ++tileIndex;
  }
}


};
