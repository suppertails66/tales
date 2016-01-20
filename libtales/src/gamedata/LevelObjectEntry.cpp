#include "gamedata/LevelObjectEntry.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


LevelObjectEntry::LevelObjectEntry()
  : objectTypeID_(ObjectTypeIDs::null),
    xPos_(0),
    yPos_(0),
    unknownFlag0_(false),
    unknownFlag1_(false),
    unknownFlag2_(false),
    unknownFlag3_(false),
    unknownFlag6_(false),
    xDirectionFlag_(right),
    blinkingFlag_(notBlinking),
    invisibilityFlag_(visible),
    spawnParameter_(0),
    leftTileVRAMIndex_(0),
    rightTileVRAMIndex_(0) { };
    
LevelObjectEntry::LevelObjectEntry(
                 ObjectTypeIDs::ObjectTypeID objectTypeID__,
                 int xPos__,
                 int yPos__,
                 XDirectionFlag xDirectionFlag__,
                 BlinkingFlag blinkingFlag__,
                 InvisibilityFlag invisibilityFlag__,
                 Tbyte spawnParameter__,
                 int leftTileVRAMIndex__,
                 int rightTileVRAMIndex__)
  : objectTypeID_(objectTypeID__),
    xPos_(xPos__),
    yPos_(yPos__),
    unknownFlag0_(false),
    unknownFlag1_(false),
    unknownFlag2_(false),
    unknownFlag3_(false),
    unknownFlag6_(false),
    xDirectionFlag_(xDirectionFlag__),
    blinkingFlag_(blinkingFlag__),
    invisibilityFlag_(invisibilityFlag__),
    spawnParameter_(spawnParameter__),
    leftTileVRAMIndex_(leftTileVRAMIndex__),
    rightTileVRAMIndex_(rightTileVRAMIndex__) { };

LevelObjectEntry::LevelObjectEntry(const Tbyte* data)
  : objectTypeID_(ObjectTypeIDs::null),
    xPos_(0),
    yPos_(0),
    unknownFlag0_(false),
    unknownFlag1_(false),
    unknownFlag2_(false),
    unknownFlag3_(false),
    unknownFlag6_(false),
    xDirectionFlag_(right),
    blinkingFlag_(notBlinking),
    invisibilityFlag_(visible),
    spawnParameter_(0),
    leftTileVRAMIndex_(0),
    rightTileVRAMIndex_(0) {
  // Copy parameters from data
  readFromData(data);
}

void LevelObjectEntry::save(std::string& data) {
  Tbyte buffer[dataSize];
  
  writeToData(buffer);
  
  data += std::string((char*)buffer, dataSize);
}

int LevelObjectEntry::load(const Tbyte* data) {
  return readFromData(data);
}

int LevelObjectEntry::writeToData(Tbyte* data) {
  
  int byteCount = 0;
  
  // Write object type
  ByteConversion::toBytes(objectTypeID_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Write x-position
  ByteConversion::toBytes(xPos_ + coordinateWriteAdjustment,
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Write y-position
  ByteConversion::toBytes(yPos_ + coordinateWriteAdjustment,
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Write bitflags
  ByteConversion::toBytes(getRawFlags(),
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Write spawn parameter
  ByteConversion::toBytes(spawnParameter_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Write left tile VRAM index
  ByteConversion::toBytes(leftTileVRAMIndex_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Write right tile VRAM index
  ByteConversion::toBytes(rightTileVRAMIndex_,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  return byteCount;
}

int LevelObjectEntry::readFromData(const Tbyte* data) {
  int byteCount = 0;
  
  // Get object type
  objectTypeID_ = static_cast<ObjectTypeIDs::ObjectTypeID>(
    ByteConversion::fromBytes(data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
  );
  byteCount += ByteSizes::uint8Size;
  
  // Get x-position
  xPos_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
    + coordinateReadAdjustment;
  byteCount += ByteSizes::uint16Size;
  
  // Get y-position
  yPos_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
    + coordinateReadAdjustment;
  byteCount += ByteSizes::uint16Size;
  
  // Get raw bitflags byte
  int rawFlagsByte = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Convert raw bitflags to native representation
  setFlags((Tbyte)rawFlagsByte);
  
  // Get spawn parameter byte
  spawnParameter_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Get left tile VRAM index
  leftTileVRAMIndex_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Get right tile VRAM index
  rightTileVRAMIndex_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  return byteCount;
}

ObjectTypeIDs::ObjectTypeID LevelObjectEntry::objectTypeID() const {
  return objectTypeID_;
}

int LevelObjectEntry::xPos() const {
  return xPos_;
}

int LevelObjectEntry::yPos() const {
  return yPos_;
}

LevelObjectEntry::XDirectionFlag
    LevelObjectEntry::xDirectionFlag() const {
  return xDirectionFlag_;
}

LevelObjectEntry::BlinkingFlag
    LevelObjectEntry::blinkingFlag() const {
  return blinkingFlag_;
}

LevelObjectEntry::InvisibilityFlag
    LevelObjectEntry::invisibilityFlag() const {
  return invisibilityFlag_;
}

Tbyte LevelObjectEntry::spawnParameter() const {
  return spawnParameter_;
}

int LevelObjectEntry::leftTileVRAMIndex() const {
  return leftTileVRAMIndex_;
}

int LevelObjectEntry::rightTileVRAMIndex() const {
  return rightTileVRAMIndex_;
}

void LevelObjectEntry::setObjectTypeID(
    ObjectTypeIDs::ObjectTypeID objectTypeID__) {
  objectTypeID_ = objectTypeID__;
}

void LevelObjectEntry::setXPos(int xPos__) {
  xPos_ = xPos__;
}

void LevelObjectEntry::setYPos(int yPos__) {
  yPos_ = yPos__;
}

void LevelObjectEntry::setXDirectionFlag(XDirectionFlag xDirectionFlag__) {
  xDirectionFlag_ = xDirectionFlag__;
}

void LevelObjectEntry::setBlinkingFlag(BlinkingFlag blinkingFlag__) {
  blinkingFlag_ = blinkingFlag__;
}

void LevelObjectEntry::setInvisibilityFlag(
    InvisibilityFlag invisibilityFlag__) {
  invisibilityFlag_ = invisibilityFlag__;
}

void LevelObjectEntry::setSpawnParameter(Tbyte spawnParameter__) {
  spawnParameter_ = spawnParameter__;
}

void LevelObjectEntry::setLeftTileVRAMIndex(int leftTileVRAMIndex__) {
  leftTileVRAMIndex_ = leftTileVRAMIndex__;
}

void LevelObjectEntry::setRightTileVRAMIndex(int rightTileVRAMIndex__) {
  rightTileVRAMIndex_ = rightTileVRAMIndex__;
}

void LevelObjectEntry::setFlags(Tbyte flags) {
  if (flags & unknownFlag0Mask) {
    unknownFlag0_ = true;
  }
  else {
    unknownFlag0_ = false;
  }
  
  if (flags & unknownFlag1Mask) {
    unknownFlag1_ = true;
  }
  else {
    unknownFlag1_ = false;
  }
  
  if (flags & unknownFlag2Mask) {
    unknownFlag2_ = true;
  }
  else {
    unknownFlag2_ = false;
  }
  
  if (flags & unknownFlag3Mask) {
    unknownFlag3_ = true;
  }
  else {
    unknownFlag3_ = false;
  }
  
  if (flags & unknownFlag6Mask) {
    unknownFlag6_ = true;
  }
  else {
    unknownFlag6_ = false;
  }

  // Set x-direction flag
  if (flags & xDirectionMask) {
    xDirectionFlag_ = left;
  }
  else {
    xDirectionFlag_ = right;
  }
  
  // Set blinking flag
  if (flags & blinkingMask) {
    blinkingFlag_ = blinking;
  }
  else {
    blinkingFlag_ = notBlinking;
  }
  
  // Set invisibility flag
  if (flags & invisibilityMask) {
    invisibilityFlag_ = invisible;
  }
  else {
    invisibilityFlag_ = visible;
  }
}

Tbyte LevelObjectEntry::getRawFlags() {
  Tbyte result = 0;
  
  if (unknownFlag0_) {
    result |= unknownFlag0Mask;
  }
  if (unknownFlag1_) {
    result |= unknownFlag1Mask;
  }
  if (unknownFlag2_) {
    result |= unknownFlag2Mask;
  }
  if (unknownFlag3_) {
    result |= unknownFlag3Mask;
  }
  if (unknownFlag6_) {
    result |= unknownFlag6Mask;
  }
  
  // Set x-direction flag
  if (xDirectionFlag_ == left) {
    result |= xDirectionMask;
  }
  
  // Set blinking flag
  if (blinkingFlag_ == blinking) {
    result |= blinkingMask;
  }
  
  // Set invisibility flag
  if (invisibilityFlag_ == invisible) {
    result |= invisibilityMask;
  }
  
  return result;
}


};
