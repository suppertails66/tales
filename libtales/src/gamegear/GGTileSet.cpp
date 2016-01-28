#include "gamegear/GGTileSet.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace Luncheon;

namespace Tales {


GGTileSet::GGTileSet()
  : tileSet_(NULL),
    numTiles_(0) {
  
}

GGTileSet::~GGTileSet() {
  delete[] tileSet_;
}

GGTileSet::GGTileSet(const GGTileSet& ggTileSet)
  : tileSet_(new GGTile[ggTileSet.numTiles_]),
    numTiles_(ggTileSet.numTiles_) {
  delete[] tileSet_;
  tileSet_ = new GGTile[ggTileSet.numTiles_];
  
  for (int i = 0; i < ggTileSet.numTiles_; i++) {
    tileSet_[i] = ggTileSet.tileSet_[i];
  }
}

GGTileSet& GGTileSet::operator=(const GGTileSet& ggTileSet) {
  delete[] tileSet_;
  tileSet_ = new GGTile[ggTileSet.numTiles_];
  numTiles_ = ggTileSet.numTiles_;
  
  for (int i = 0; i < ggTileSet.numTiles_; i++) {
    tileSet_[i] = ggTileSet.tileSet_[i];
  }
  
  return *this;
}

GGTileSet::GGTileSet(int numTiles__)
  : tileSet_(new GGTile[numTiles__]),
    numTiles_(numTiles__) { };
    

GGTileSet::GGTileSet(VirtualVDP& vdp,
          int startingTileNum,
          int numTiles__)
  : tileSet_(new GGTile[numTiles__]),
    numTiles_(numTiles__) {
  
  for (int i = 0; i < numTiles_; i++) {
    // Get pointer to raw tile data
    const Tbyte* tileData = vdp.tileRead(startingTileNum + i);
    
    // Convert to GGTile
    GGTile tile(tileData);
    
    // Place in set
    tileSet_[i] = tile;
  }
  
}

int GGTileSet::numTiles() const {
  return numTiles_;
}

void GGTileSet::resize(int newSize) {
  // Return if no change
  if (newSize == numTiles_) {
    return;
  }
  
  // TODO: zero size case
  
  // Create new tile array of new size
  GGTile* newTileSet = new GGTile[newSize];
  
  // Copy as many tiles from old set as possible
  int copySize = numTiles_;
  if (newSize < numTiles_) {
    copySize = newSize;
  }
  
  // Copy needed tiles
  for (int i = 0; i < copySize; i++) {
    newTileSet[i] = tileSet_[i];
  }
  
  // Delete existing tiles
  delete[] tileSet_;
  
  // Set storage pointer to new array
  tileSet_ = newTileSet;
  
  // Update number of tiles
  numTiles_ = newSize;
}

GGTile& GGTileSet::operator[](unsigned int tileNum) {
  // Throw on out-of-range access
  if (tileNum >= (unsigned int)numTiles_) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                           "GGTileSet::operator[](unsigned int) const",
                           tileNum);
  }
  
  return tileSet_[tileNum];
}

const GGTile& GGTileSet::operator[](unsigned int tileNum) const {
  // Throw on out-of-range access
  if (tileNum >= (unsigned int)numTiles_) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                           "GGTileSet::operator[](unsigned int)",
                           tileNum);
  }
  
  return tileSet_[tileNum];
}

void GGTileSet::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write number of tiles
  ByteConversion::toBytes(numTiles_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write each tile
  for (int i = 0; i < numTiles_; i++) {
    tileSet_[i].save(data);
  }
  
}

int GGTileSet::load(const Tbyte* data) {
  // Delete existing tiles
  delete[] tileSet_;
  
  // Count of read bytes
  int byteCount = 0;
  
  // Read number of tiles
  numTiles_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Allocate array
  tileSet_ = new GGTile[numTiles_];
  
  // Read each tile
  for (int i = 0; i < numTiles_; i++) {
    byteCount += tileSet_[i].load(data + byteCount);
  }
  
  // Return count of read bytes
  return byteCount;
}

int GGTileSet::writeNativeUncompressed(Tbyte* data) {
  int byteCount = 0;
 
  for (int i = 0; i < numTiles_; i++) {
    tileSet_[i].toInterleavedPixels(data + byteCount);
    
    byteCount += GGTile::rawInputDataSize;
  }
  
  return byteCount;
}

Graphic GGTileSet::toGrayscaleGraphic(int width,
                                      Color backgroundColor,
                                      bool invert) {
  int realHeight = ((numTiles_ / width) + 1) * GGTile::height;
  Graphic output(width * GGTile::width,
                 realHeight);
  output.clear(backgroundColor);
                 
//  std::cout << "real: " << output.w() << " " << output.h() << std::endl;
  
  GGPalette palette;
  for (int i = 0; i < GGPalette::numColorsInPalette; i++) {
    int color = 0;
    if (invert) {
      color = (GGPalette::numColorsInPalette - i) * 16;
    }
    else {
      color = i * 16;
    }
    
    GGColor realColor;
    realColor.setRGB(color, color, color);
    
    palette[i] = realColor;
  }
  
  for (int i = 0; i < numTiles_; i++) {
    int x = ((i % width) * GGTile::width);
    int y = ((i / width) * GGTile::height);
  
    Graphic tile(tileSet_[i],
                 palette,
                 Graphic::tileTrans);
  
/*    Graphic tile(GGTile::width,
                 GGTile::height);
    for (int k = 0; k < GGTile::height; k++) {
      for (int j = 0; j < GGTile::width; j++) {
      
      
        Tbyte colorIndex = tileSet_[i].getPixel(j, k);
        tile.setPixel(j,
                      k,
                      Color(palette[colorIndex].realR(),
                            palette[colorIndex].realG(),
                            palette[colorIndex].realB(),
                            Color::fullAlphaOpacity));
      }
    } */
                 
    output.blit(tile,
                Box(x, y, GGTile::width, GGTile::height),
                Box(0, 0, GGTile::width, GGTile::height));
  }
  
  return output;
}
                             
Graphic GGTileSet::toPalettizedGraphic(
                            int width,
                            const GGPalette& palette,
                            Color backgroundColor,
                            Graphic::TileTransferTransOption transOption) {
  int realHeight = ((numTiles_ / width) + 1) * GGTile::height;
  Graphic output(width * GGTile::width,
                 realHeight);
  drawPalettizedGraphic(output,
                         width,
                         palette,
                         backgroundColor,
                         transOption);
  return output;
}
                               
void GGTileSet::drawPalettizedGraphic(Graphic& output,
                            int width,
                            const GGPalette& palette,
                            Color backgroundColor,
                            Graphic::TileTransferTransOption transOption) {
  output.clear(backgroundColor);
  int realHeight = ((numTiles_ / width) + 1) * GGTile::height;
                 
  for (int i = 0; i < numTiles_; i++) {
    int x = ((i % width) * GGTile::width);
    int y = ((i / width) * GGTile::height);
  
    Graphic tile(tileSet_[i],
                 palette,
                 transOption);
                 
    output.blit(tile,
                Box(x, y, GGTile::width, GGTile::height),
                Box(0, 0, GGTile::width, GGTile::height));
  }
}
                             
TwoDByteArray GGTileSet::toByteArray(int width) {
  int realHeight = ((numTiles_ / width) + 1) * GGTile::height;
  TwoDByteArray output(width * GGTile::width,
                 realHeight);
  output.clear();
  
  for (int i = 0; i < numTiles_; i++) {
    int x = ((i % width) * GGTile::width);
    int y = ((i / width) * GGTile::height);
                 
    tileSet_[i].transferToByteArray(output,
                                    x, y);
  }
  
  return output;
}
                             
void GGTileSet::fromByteArray(TwoDByteArray& src,
                   int width) {
  int tileNum = 0;
  for (int j = 0; j < src.h(); j += GGTile::height) {
    for (int i = 0; i < src.w(); i += GGTile::width) {
      tileFromByteArray(tileNum, src, i, j);
      ++tileNum;
      
      if (tileNum >= numTiles_) {
        break;
      }
    }
    
    if (tileNum >= numTiles_) {
      break;
    }
  }
}

void GGTileSet::tileFromByteArray(int tileNum,
                       TwoDByteArray& src,
                       int x, int y) {
  for (int j = 0; j < GGTile::height; j++) {
    int srcy = (y + j);
    if (srcy >= src.h()) {
      continue;
    }
    
    for (int i = 0; i < GGTile::width; i++) {
      int srcx = (x + i);
      if (srcx >= src.w()) {
        continue;
      }
      
      tileSet_[tileNum].setPixel(i, j,
                                 src.data(srcx, srcy));
    }
  }
}


};
