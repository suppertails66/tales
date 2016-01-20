#include "gamedata/SpriteMappingTileIndexTable.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"

using namespace Luncheon;

namespace Tales {


SpriteMappingTileIndexTable::SpriteMappingTileIndexTable() { };
  
SpriteMappingTileIndexTable::SpriteMappingTileIndexTable(
                            const Tbyte* data,
                            int numSprites) {
  readFromData(data,
               numSprites);
}

void SpriteMappingTileIndexTable::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint16Size];
  
  ByteConversion::toBytes(tileIndices_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::int16Size);
  
  for (int i = 0; i < tileIndices_.size(); i++) {
    ByteConversion::toBytes(tileIndices_[i],
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint8Size);
  }
}

int SpriteMappingTileIndexTable::load(const Tbyte* data) {
  tileIndices_.clear();

  int byteCount = 0;
  
  int numIndices = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::int16Size;
  
  for (int i = 0; i < numIndices; i++) {
    int index = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
                            
    tileIndices_.push_back(index);
  }
  
  return byteCount;
}

int SpriteMappingTileIndexTable::readFromData(const Tbyte* data,
                                              int numSprites) {
  tileIndices_.clear();
  
  int byteCount = 0;
  
  for (int i = 0; i < numSprites; i++) {
    int index = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
                            
    tileIndices_.push_back(index);
  }
  
  return byteCount;
}

int SpriteMappingTileIndexTable::writeToData(Tbyte* data) {
  int byteCount = 0;
  
  for (int i = 0; i < tileIndices_.size(); i++) {
    ByteConversion::toBytes(tileIndices_[i],
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
  }
  
  return byteCount;
}

int SpriteMappingTileIndexTable::size() const {
  return tileIndices_.size();
}

int& SpriteMappingTileIndexTable::tileIndex(int index) {
  if (index >= tileIndices_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "SpriteMappingTileIndexTable"
                                   "::tileIndex(int)",
                                   index);
  }

  return tileIndices_[index];
}

const int& SpriteMappingTileIndexTable::tileIndex(int index) const {
  if (index >= tileIndices_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "SpriteMappingTileIndexTable"
                                   "::tileIndex(int) const",
                                   index);
  }
  
  return tileIndices_[index];
}


};
