#include "gamedata/SpriteMappingCoordinateTable.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


SpriteMappingCoordinateTable::SpriteMappingCoordinateTable() { };

SpriteMappingCoordinateTable::SpriteMappingCoordinateTable(
                             const Tbyte* data,
                             int numSprites) {
  readFromData(data,
               numSprites);
}

void SpriteMappingCoordinateTable::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint16Size];
  
  ByteConversion::toBytes(spriteCoordinates_.size(),
                          buffer,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  data += std::string((char*)buffer, ByteSizes::int16Size);
  
  for (int i = 0; i < spriteCoordinates_.size(); i++) {
    spriteCoordinates_[i].save(data);
  }
}

int SpriteMappingCoordinateTable::load(const Tbyte* data) {
  spriteCoordinates_.clear();
  int byteCount = 0;
  
  int numEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  byteCount += ByteSizes::int16Size;
  
  for (int i = 0; i < numEntries; i++) {
    SpriteMappingCoordinateTableEntry entry;
    byteCount += entry.load(data + byteCount);
    
    spriteCoordinates_.push_back(entry);
  }
  
  return byteCount;
}

int SpriteMappingCoordinateTable::readFromData(const Tbyte* data,
                                               int numSprites) {
  spriteCoordinates_.clear();
  int byteCount = 0;
  
  // Read all sprites
  for (int i = 0; i < numSprites; i++) {
    SpriteMappingCoordinateTableEntry entry(data + byteCount);
    byteCount += SpriteMappingCoordinateTableEntry::dataSize;
    
    spriteCoordinates_.push_back(entry);
  }
  
  return byteCount;
}

int SpriteMappingCoordinateTable::writeToData(Tbyte* data) {
  int byteCount = 0;
  
  for (int i = 0; i < spriteCoordinates_.size(); i++) {
    byteCount += spriteCoordinates_[i].writeToData(data + byteCount);
    
/*    SpriteMappingCoordinateTableEntry entry
      = spriteCoordinates_[i];
    entry.setOffsetX(-entry.offsetX());
    entry.writeToData(data + byteCount
                        + offsetToHorizontalFlip); */
  }
  
  return byteCount;
}
                               
int SpriteMappingCoordinateTable::size() const {
  return spriteCoordinates_.size();
}

SpriteMappingCoordinateTableEntry& SpriteMappingCoordinateTable
    ::entry(int index) {
  if (index >= spriteCoordinates_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "SpriteMappingCoordinateTable"
                                   "::entry(int)",
                                   index);
  }
  
  return spriteCoordinates_[index];
}

const SpriteMappingCoordinateTableEntry& SpriteMappingCoordinateTable
    ::entry(int index) const {
  if (index >= spriteCoordinates_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "SpriteMappingCoordinateTable"
                                   "::entry(int) const",
                                   index);
  }
  
  return spriteCoordinates_[index];
}


};
