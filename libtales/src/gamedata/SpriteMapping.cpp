#include "gamedata/SpriteMapping.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


SpriteMapping::SpriteMapping()
  : numSprites_(0),
    collisionXLength_(0),
    collisionYLength_(0),
    coordinateTableIndex_(0),
    offsetY_(0),
    offsetX_(0),
    tileIndexTableIndex_(0) { };
  
SpriteMapping::SpriteMapping(
              int numSprites__,
              int collisionXLength__,
              int collisionYLength__,
              int coordinateTableIndex__,
              int offsetY__,
              int offsetX__,
              int tileIndexTableIndex__)
  : numSprites_(numSprites__),
    collisionXLength_(collisionXLength__),
    collisionYLength_(collisionYLength__),
    coordinateTableIndex_(coordinateTableIndex__),
    offsetY_(offsetY__),
    offsetX_(offsetX__),
    tileIndexTableIndex_(tileIndexTableIndex__) { };
    
void SpriteMapping::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint16Size];
  
  ByteConversion::toBytes(numSprites_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint8Size);
  
  ByteConversion::toBytes(collisionXLength_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::int8Size);
  
  ByteConversion::toBytes(collisionYLength_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::int8Size);
  
  ByteConversion::toBytes(coordinateTableIndex_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  ByteConversion::toBytes(offsetY_,
                          buffer,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  data += std::string((char*)buffer, ByteSizes::int16Size);
  
  ByteConversion::toBytes(offsetX_,
                          buffer,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  data += std::string((char*)buffer, ByteSizes::int16Size);
  
  ByteConversion::toBytes(tileIndexTableIndex_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
}

int SpriteMapping::load(const Tbyte* data) {
  int byteCount = 0;
  
  numSprites_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  collisionXLength_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  collisionYLength_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  coordinateTableIndex_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  offsetY_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  byteCount += ByteSizes::int16Size;
  
  offsetX_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  byteCount += ByteSizes::int16Size;
  
  tileIndexTableIndex_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  return byteCount;
}

int SpriteMapping::writeToData(Tbyte* data,
                Taddress coordinateTableAddress,
                Taddress tileIndexTableAddress) {
  int byteCount = 0;
  
  Taddress coordinateTableBankedAddress
    = LoadedROM::directToBankedAddress(coordinateTableAddress);
  Taddress tileIndexTableBankedAddress
    = LoadedROM::directToBankedAddress(tileIndexTableAddress);
  
  ByteConversion::toBytes(numSprites_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  ByteConversion::toBytes(collisionXLength_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  ByteConversion::toBytes(collisionYLength_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  ByteConversion::toBytes(coordinateTableBankedAddress,
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  ByteConversion::toBytes(offsetY_,
                          data + byteCount,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  byteCount += ByteSizes::int16Size;
  
  ByteConversion::toBytes(offsetX_,
                          data + byteCount,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  byteCount += ByteSizes::int16Size;
  
  ByteConversion::toBytes(tileIndexTableBankedAddress,
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  return byteCount;
}

int SpriteMapping::numSprites() const {
  return numSprites_;
}

int SpriteMapping::collisionXLength() const {
  return collisionXLength_;
}

int SpriteMapping::collisionYLength() const {
  return collisionYLength_;
}

int SpriteMapping::coordinateTableIndex() const {
  return coordinateTableIndex_;
}

int SpriteMapping::offsetY() const {
  return offsetY_;
}

int SpriteMapping::offsetX() const {
  return offsetX_;
}

int SpriteMapping::tileIndexTableIndex() const {
  return tileIndexTableIndex_;
}
  
void SpriteMapping::setNumSprites(int numSprites__) {
  numSprites_ = numSprites__;
}

void SpriteMapping::setCollisionXLength(int collisionXLength__) {
  collisionXLength_ = collisionXLength__;
}

void SpriteMapping::setCollisionYLength(int collisionYLength__) {
  collisionYLength_ = collisionYLength__;
}

void SpriteMapping::setCoordinateTableIndex(int coordinateTableIndex__) {
  coordinateTableIndex_ = coordinateTableIndex__;
}

void SpriteMapping::setOffsetY(int offsetY__) {
  offsetY_ = offsetY__;
}

void SpriteMapping::setOffsetX(int offsetX__) {
  offsetX_ = offsetX__;
}

void SpriteMapping::setTileIndexTableIndex(int tileIndexTableIndex__) {
  tileIndexTableIndex_ = tileIndexTableIndex__;
}


};
