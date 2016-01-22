#include "gamedata/TileMap.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <cstdlib>

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
  : format_(format__),
    w_(w__),
	h_(h__),
    lowerLimit_(defaultLowerLimit_),
    upperLimit_(defaultUpperLimit_) {
  readFromData(data, format_, w_, h_, upperByte__);
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
	  tileData_[i][j] = TileReference(ByteConversion::fromBytes(
	                              data + byteCount,
								  ByteSizes::uint16Size,
								  EndiannessTypes::little,
								  SignednessTypes::nosign));
      
	  // Place in array
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
      identifier |= (((unsigned int)(upperByte__)) << ByteSizes::uint8Size);
	  
	  // Place in array
	  tileData_[i][j] = TileReference(identifier);
      
	  byteCount += ByteSizes::uint8Size;
	}
  }
  
  return byteCount;
}

void TileMap::writeToData(Tbyte* data) const {
  
}

void TileMap::save(std::string& data) const {
  
}

int TileMap::load(const Tbyte* data) {
  int byteCount = 0;
  
  
  
  return byteCount;
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
  // Delete column arrays
  for (int i = 0; i < w_; i++) {
    delete tileData_[i];
  }
  
  // Delete container array
  delete tileData_;
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