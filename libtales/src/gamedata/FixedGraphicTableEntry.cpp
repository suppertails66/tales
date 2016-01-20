#include "gamedata/FixedGraphicTableEntry.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


FixedGraphicTableEntry::FixedGraphicTableEntry()
  : leftTileIndex_(0),
    rightTileIndex_(0) { };

FixedGraphicTableEntry::FixedGraphicTableEntry(const Tbyte* data)
  : leftTileIndex_(0),
    rightTileIndex_(0) {
  readFromData(data);
}

void FixedGraphicTableEntry::save(std::string& data) {
  Tbyte buffer[dataSize];
  
  writeToData(buffer);
  
  data += std::string((char*)buffer, dataSize);
}

int FixedGraphicTableEntry::load(const Tbyte* data) {
  return readFromData(data);
}

int FixedGraphicTableEntry::writeToData(Tbyte* data) {
  ByteConversion::toBytes(leftTileIndex_,
                          data + 0,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
                          
  ByteConversion::toBytes(rightTileIndex_,
                          data + 1,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  return dataSize;
}

int FixedGraphicTableEntry::readFromData(const Tbyte* data) {
  int byteCount = 0;
  
  leftTileIndex_ = ByteConversion::fromBytes(data + byteCount,
                                             ByteSizes::uint8Size,
                                             EndiannessTypes::little,
                                             SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  rightTileIndex_ = ByteConversion::fromBytes(data + byteCount,
                                             ByteSizes::uint8Size,
                                             EndiannessTypes::little,
                                             SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  return byteCount;
}
  
int FixedGraphicTableEntry::leftTileIndex() const {
  return leftTileIndex_;
}

int FixedGraphicTableEntry::rightTileIndex() const {
  return rightTileIndex_;
}
  
void FixedGraphicTableEntry::setLeftTileIndex(int leftTileIndex__) {
  leftTileIndex_ = leftTileIndex__;
}

void FixedGraphicTableEntry::setRightTileIndex(int rightTileIndex__) {
  rightTileIndex_ = rightTileIndex__;
}


};
