#include "gamedata/LevelHeader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "gamegear/LoadedROM.h"

using namespace Luncheon;

namespace Tales {


LevelHeader::LevelHeader()
  : tileStructureID_(0),
    mapLayoutID_(0),
    width_(0),
    cameraLeftLimit_(0),
    cameraTopLimit_(0),
    cameraRightLimit_(0),
    cameraBottomLimit_(0),
    yTableID_(0) { };

LevelHeader::LevelHeader(
              int tileStructureID__,
              int mapLayoutID__,
              int width__,
              int cameraLeftLimit__,
              int cameraTopLimit__,
              int cameraRightLimit__,
              int cameraBottomLimit__,
              int yTableID__)
  : tileStructureID_(tileStructureID__),
    mapLayoutID_(mapLayoutID__),
    width_(width__),
    cameraLeftLimit_(cameraLeftLimit__),
    cameraTopLimit_(cameraTopLimit__),
    cameraRightLimit_(cameraRightLimit__),
    cameraBottomLimit_(cameraBottomLimit__),
    yTableID_(yTableID__) { };

int LevelHeader::writeToData(Tbyte* data,
                             Taddress tileStructureAddress,
                             Taddress mapLayoutAddress,
                             Taddress yTableAddress) const {
  // Convert direct addresses to banked
  int tileStructureBank = LoadedROM::directToBankNum(tileStructureAddress);
  Taddress tileStructureBankedAddress = LoadedROM::directToBankedAddress(
      tileStructureAddress);
  int mapLayoutBank = LoadedROM::directToBankNum(mapLayoutAddress);
  Taddress mapLayoutBankedAddress = LoadedROM::directToBankedAddress(
      mapLayoutAddress);
//  yTableBank = LoadedROM::directToBankNum(yTableAddress);
//  yTableBankedAddress = LoadedROM::directToBankedAddress(
//      yTableAddress);
      
  // Write all fields
  
  ByteConversion::toBytes(tileStructureBank,
                          data + 0,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(tileStructureBankedAddress,
                          data + 1,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(mapLayoutBank,
                          data + 3,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(mapLayoutBankedAddress,
                          data + 4,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(width_,
                          data + 6,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // "negative width" (for vertical ejection)
  ByteConversion::toBytes((-width_),
                          data + 8,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  
  // "height of loadable screen area in terms of array length"
  // (for some optimization)
  // loadableAreaMultiplier = height of nametable in metatiles
  ByteConversion::toBytes(width_ * loadableAreaMultiplier,
                          data + 10,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  
  ByteConversion::toBytes(cameraLeftLimit_,
                          data + 12,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(cameraTopLimit_,
                          data + 14,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(cameraRightLimit_,
                          data + 16,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(cameraBottomLimit_,
                          data + 18,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(yTableAddress,
                          data + 20,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);

  return dataSize;
}

void LevelHeader::save(std::string& data) {
  // Write buffer
  char buffer[ByteSizes::uint32Size];
  
  // Write each field to buffer, then to string
  
  ByteConversion::toBytes(tileStructureID_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(mapLayoutID_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(width_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(cameraLeftLimit_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(cameraTopLimit_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(cameraRightLimit_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(cameraBottomLimit_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(yTableID_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
}

int LevelHeader::load(const Tbyte* data) {
  // Count of bytes read
  int byteCount = 0;
  
  // Read each field from data
  
  tileStructureID_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  mapLayoutID_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  width_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  cameraLeftLimit_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  cameraTopLimit_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  cameraRightLimit_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  cameraBottomLimit_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  yTableID_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  return byteCount;
}

int LevelHeader::tileStructureID() const {
  return tileStructureID_;
}

int LevelHeader::mapLayoutID() const {
  return mapLayoutID_;
}

int LevelHeader::width() const {
  return width_;
}

int LevelHeader::cameraLeftLimit() const {
  return cameraLeftLimit_;
}

int LevelHeader::cameraTopLimit() const {
  return cameraTopLimit_;
}

int LevelHeader::cameraRightLimit() const {
  return cameraRightLimit_;
}

int LevelHeader::cameraBottomLimit() const {
  return cameraBottomLimit_;
}

int LevelHeader::yTableID() const {
  return yTableID_;
}

void LevelHeader::setTileStructureID(int tileStructureID__) {
  tileStructureID_ = tileStructureID__;
}

void LevelHeader::setMapLayoutID(int mapLayoutID__) {
  mapLayoutID_ = mapLayoutID__;
}

void LevelHeader::setWidth(int width__) {
  width_ = width__;
}

void LevelHeader::setCameraLeftLimit(int cameraLeftLimit__) {
  cameraLeftLimit_ = cameraLeftLimit__;
}

void LevelHeader::setCameraTopLimit(int cameraTopLimit__) {
  cameraTopLimit_ = cameraTopLimit__;
}

void LevelHeader::setCameraRightLimit(int cameraRightLimit__) {
  cameraRightLimit_ = cameraRightLimit__;
}

void LevelHeader::setCameraBottomLimit(int cameraBottomLimit__) {
  cameraBottomLimit_ = cameraBottomLimit__;
}

void LevelHeader::setYTableID(int yTableID__) {
  yTableID_ = yTableID__;
}


}; 
