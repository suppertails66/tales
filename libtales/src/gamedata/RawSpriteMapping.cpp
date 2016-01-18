#include "gamedata/RawSpriteMapping.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


RawSpriteMapping::RawSpriteMapping()
  : numSprites_(0),
    collisionXLength_(0),
    collisionYLength_(0),
    coordinateTableBankedAddress_(0),
    offsetY_(0),
    offsetX_(0),
    tileIndexTableBankedAddress_(0) { };

RawSpriteMapping::RawSpriteMapping(const Tbyte* data)
  : numSprites_(0),
    collisionXLength_(0),
    collisionYLength_(0),
    coordinateTableBankedAddress_(0),
    offsetY_(0),
    offsetX_(0),
    tileIndexTableBankedAddress_(0) {
  
  numSprites_ = ByteConversion::fromBytes(
                              data + 0,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  collisionXLength_ = ByteConversion::fromBytes(
                              data + 1,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  collisionYLength_ = ByteConversion::fromBytes(
                              data + 2,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  coordinateTableBankedAddress_ = ByteConversion::fromBytes(
                              data + 3,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  offsetX_ = ByteConversion::fromBytes(
                              data + 5,
                              ByteSizes::int16Size,
                              EndiannessTypes::little,
                              SignednessTypes::sign);
  
  offsetY_ = ByteConversion::fromBytes(
                              data + 7,
                              ByteSizes::int16Size,
                              EndiannessTypes::little,
                              SignednessTypes::sign);
  
  tileIndexTableBankedAddress_ = ByteConversion::fromBytes(
                              data + 9,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
}

int RawSpriteMapping::numSprites() const {
  return numSprites_;
}

int RawSpriteMapping::collisionXLength() const {
  return collisionXLength_;
}

int RawSpriteMapping::collisionYLength() const {
  return collisionYLength_;
}

Taddress RawSpriteMapping::coordinateTableBankedAddress() const {
  return coordinateTableBankedAddress_;
}

int RawSpriteMapping::offsetY() const {
  return offsetY_;
}

int RawSpriteMapping::offsetX() const {
  return offsetX_;
}

Taddress RawSpriteMapping::tileIndexTableBankedAddress() const {
  return tileIndexTableBankedAddress_;
}


};
