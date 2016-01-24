#include "gamedata/TileMap.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <cstdlib>
#include <iostream>

using namespace Luncheon;

namespace Tales {


TileMap::TileMap()
  : tileData_(NULL),
	  format_(TileMap::twoBytesPerTile),
	  w_(0),
	  h_(0),
	  lowerLimit_(defaultLowerLimit_),
	  upperLimit_(defaultUpperLimit_) { };

TileMap::TileMap(const Tbyte* data,
	  TileMapFormat format__,
	  int w__,
	  int h__)
  : tileData_(NULL),
	  format_(format__),
	  w_(w__),
	  h_(h__),
	  lowerLimit_(defaultLowerLimit_),
	  upperLimit_(defaultUpperLimit_) {
  readFromData(data, format_, w_, h_);
}

TileMap::TileMap(const Tbyte* data,
	  TileMapFormat format__,
	  int w__,
	  int h__,
	  Tbyte upperByte__)
  : tileData_(NULL),
    format_(format__),
    w_(w__),
	  h_(h__),
    lowerLimit_(defaultLowerLimit_),
    upperLimit_(defaultUpperLimit_) {
  readFromData(data, format_, w_, h_, upperByte__);
}

TileMap::TileMap(const TileMap& t)
  : tileData_(NULL),
    format_(t.format_),
    w_(t.w_),
    h_(t.h_),
    lowerLimit_(t.lowerLimit_),
    upperLimit_(t.upperLimit_) {
  // Copy tile data
  reinitializeTileData(w_, h_);
  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
      tileData_[i][j] = t.tileData_[i][j];
    }
  }
}

TileMap& TileMap::operator=(const TileMap& t) {
  format_ = t.format_;
  w_ = t.w_;
  h_ = t.h_;
  lowerLimit_ = t.lowerLimit_;
  upperLimit_ = t.upperLimit_;
  
  // Copy tile data
  reinitializeTileData(w_, h_);
  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
      tileData_[i][j] = t.tileData_[i][j];
    }
  }
  
  return *this;
}

TileMap::~TileMap() {
  destroyTileData();
}

int TileMap::readFromData(const Tbyte* data,
			   TileMapFormat format__,
			   int w__,
			   int h__) {
  int byteCount = 0;
  
  // Set format data
  format_ = format__;
  w_ = w__;
  h_ = h__;
  
  // Reinitialize tile array
  reinitializeTileData(w_, h_);
  
  // Read tile identifiers
  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
	    // Place in array
	    tileData_[i][j] = TileReference(ByteConversion::fromBytes(
	                                data + byteCount,
								    ByteSizes::uint16Size,
								    EndiannessTypes::little,
								    SignednessTypes::nosign));
        
	    byteCount += ByteSizes::uint16Size;
	  }
  }
  
  return byteCount;
}

int TileMap::readFromData(const Tbyte* data,
			   TileMapFormat format__,
			   int w__,
			   int h__,
			   Tbyte upperByte__) {
  int byteCount = 0;
  
  // Set format data
  format_ = format__;
  w_ = w__;
  h_ = h__;
  
  // Set limits based on upper byte (0 bit = 9th bit of tile num)
  if ((upperByte__ & 0x01) == 0) {
    lowerLimit_ = 0;
    upperLimit_ = 256;
  }
  else {
    lowerLimit_ = 256;
    upperLimit_ = 512;
  }
  
  // Reinitialize tile array
  reinitializeTileData(w_, h_);
  
  // Read tile identifiers
  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
	    // Read low byte of identifier
	    unsigned int identifier = ByteConversion::fromBytes(
	                                data + byteCount,
								                  ByteSizes::uint8Size,
								                  EndiannessTypes::little,
								                  SignednessTypes::nosign);
        
      // Incorporate upper byte
      identifier |= (((unsigned int)(upperByte__)) << 8);
	    
	    // Place in array
	    tileData_[i][j] = TileReference(identifier);
        
	    byteCount += ByteSizes::uint8Size;
	  }
  }
  
  return byteCount;
}

void TileMap::writeToData(Tbyte* data) const {
  int byteCount = 0;
  switch (format_) {
  case oneBytePerTile:
    for (int j = 0; j < h_; j++) {
      for (int i = 0; i < w_; i++) {
        // Get identifier for this tile
	      unsigned int identifier
	        = tileData_[i][j].toRawIdentifier();
	        
	      // Write low byte to data
	      ByteConversion::toBytes(identifier & 0xFF,
	                              data + byteCount,
	                              ByteSizes::uint8Size,
	                              EndiannessTypes::little,
	                              SignednessTypes::nosign);
        byteCount += ByteSizes::uint8Size;
	    }
    }
    break;
  case twoBytesPerTile:
    for (int j = 0; j < h_; j++) {
      for (int i = 0; i < w_; i++) {
        // Get identifier for this tile
	      unsigned int identifier
	        = tileData_[i][j].toRawIdentifier();
	        
	      // Write to data
	      ByteConversion::toBytes(identifier,
	                              data + byteCount,
	                              ByteSizes::uint16Size,
	                              EndiannessTypes::little,
	                              SignednessTypes::nosign);
        byteCount += ByteSizes::uint16Size;
	    }
    }
    break;
  default:
    break;
  }
}

void TileMap::save(std::string& data) const {
  Tbyte buffer[ByteSizes::uint32Size];

  // Format
  ByteConversion::toBytes(format_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint8Size);

  // w
  ByteConversion::toBytes(w_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);

  // h
  ByteConversion::toBytes(h_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);

  // Lower limit
  ByteConversion::toBytes(lowerLimit_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);

  // Upper limit
  ByteConversion::toBytes(upperLimit_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Tile data
  for (int j = 0; j < h_; j++) {
    for (int i = 0; i < w_; i++) {
      // Get identifier for this tile
      unsigned int identifier
        = tileData_[i][j].toRawIdentifier();
        
      // Write to data
      ByteConversion::toBytes(identifier,
                              buffer,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      data += std::string((char*)buffer, ByteSizes::uint16Size);
    }
  }
}

int TileMap::load(const Tbyte* data) {
  int byteCount = 0;
  
  // Format
  TileMap::TileMapFormat formatTemp_
      = static_cast<TileMap::TileMapFormat>(
                  ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign)
            );
  byteCount += ByteSizes::uint8Size;

  // w
  w_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;

  // h
  h_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;

  // Lower limit
  lowerLimit_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;

  // Upper limit
  upperLimit_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Tile data
  byteCount += readFromData(data + byteCount,
                            twoBytesPerTile,
                            w_,
                            h_);
  // oops
  format_ = formatTemp_;
  
//  if (format_ == oneBytePerTile) {
//    std::cout << "here" << std::endl;
//  }
  
  return byteCount;
}

TileReference& TileMap::tileData(int x, int y) {
  if ((x >= w_)) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "TileMap::tileData(int,int)"
                                   " [x]",
                                   x);
  }
  
  if ((y >= h_)) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "TileMap::tileData(int,int)"
                                   " [y]",
                                   y);
  }
  
  return tileData_[x][y];
}

const TileReference& TileMap::tileData(int x, int y) const {
  if ((x >= w_)) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "TileMap::tileData(int,int)"
                                   " [x]",
                                   x);
  }
  
  if ((y >= h_)) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "TileMap::tileData(int,int)"
                                   " [y]",
                                   y);
  }
  
  return tileData_[x][y];
}

TileMap::TileMapFormat TileMap::format() const {
  return format_;
}

int TileMap::w() const {
  return w_;
}

int TileMap::h() const {
  return h_;
}

int TileMap::lowerLimit() const {
  return lowerLimit_;
}

int TileMap::upperLimit() const {
  return upperLimit_;
}

void TileMap::setFormat(TileMapFormat format__) {
  format_ = format__;
}

void TileMap::setW(int w__) {
  w_ = w__;
}

void TileMap::setH(int h__) {
  h_ = h__;
}

void TileMap::setLowerLimit(int lowerLimit__) {
  lowerLimit_ = lowerLimit__;
}

void TileMap::setUpperLimit(int upperLimit__) {
  upperLimit_ = upperLimit__;
}

void TileMap::destroyTileData() {
  if (tileData_ == NULL) {
    return;
  }
  
  // Delete column arrays
  for (int i = 0; i < w_; i++) {
    delete[] tileData_[i];
  }
  
  // Delete container array
  delete[] tileData_;
}

void TileMap::reinitializeTileData(int w__, int h__) {
  // Destroy existing data
  destroyTileData();
  
  // Initialize column array
  tileData_ = new TileReference*[w_];
  
  // Initialize columns
  for (int i = 0; i < w_; i++) {
    tileData_[i] = new TileReference[h_];
  }
}


};
