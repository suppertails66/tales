#include "gamedata/MetatileBehavior.h"
#include "exception/TGenericException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"
#include "gamegear/LoadedROM.h"
#include "gamedata/TailsAdvAddresses.h"
#include "gamedata/MetatileWidthMap.h"
#include "gamedata/MetatileHeightMap.h"
#include <string>

using namespace Luncheon;

namespace Tales {


MetatileBehavior::MetatileBehavior()
  : fullySolid_(false),
    solidOnTop_(false),
    unknownSetting_(false),
    metatileType_(MetatileTypes::nullType),
    slopeSpeedIndex_(0),
    heightMapIndex_(0),
    widthMapIndex_(0),
    terminator_(0) { };

MetatileBehavior::MetatileBehavior(const Tbyte* src)
  : fullySolid_(false),
    solidOnTop_(false),
    unknownSetting_(false),
    metatileType_(MetatileTypes::nullType),
    slopeSpeedIndex_(0),
    heightMapIndex_(0),
    widthMapIndex_(0),
    terminator_(0) {
  readFromData(src);
}

void MetatileBehavior::readFromData(const Tbyte* src) {
  // Get raw behavior byte
  Tbyte rawBehavior = src[0];
  
  // Check bitmasked behaviors
  
  if (rawBehavior & fullySolidMask) {
    fullySolid_ = true;
  }
  
  if (rawBehavior & solidOnTopMask) {
    solidOnTop_ = true;
  }
  
  if (rawBehavior & unknownSettingMask) {
    unknownSetting_ = true;
  }
  
  // Get tile type
  int rawType = (rawBehavior & metatileTypeMask);
  
  // Throw if type is out of valid range
  if (rawType >= MetatileTypes::numMetatileTypes) {
    throw TGenericException(TALES_SRCANDLINE,
                           "MetatileBehavior::readFromData(const Tbyte*)",
                           std::string("Invalid tile type: ")
                           + StringConversion::toString(rawType));
  }
  
  // Cast to type
  metatileType_ = static_cast<MetatileTypes::MetatileType>(rawType);
  
  // Get slope speed index (converting from raw index; each table entry is
  // a 16-bit number, and the game indexes into it using this value as-is, so
  // we divide by 2 to get the actual index number)
  slopeSpeedIndex_ = (src[1]) / 2;
  
  // Get raw height map address
  int heightMapAddr 
    = ByteConversion::fromBytes(src + 2,
                                ByteSizes::uint16Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  
  // Convert to index by dividing by size of each map
  heightMapIndex_ = LoadedROM::toIndex(TailsAdvAddresses::HeightMapTable,
                                       heightMapAddr,
                                       MetatileHeightMap::dataSize);
  
  
  // Get raw width map address
  int widthMapAddr 
    = ByteConversion::fromBytes(src + 4,
                                ByteSizes::uint16Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  
  // Convert to index by dividing by size of each map
  widthMapIndex_ = LoadedROM::toIndex(TailsAdvAddresses::WidthMapTable,
                                      widthMapAddr,
                                      MetatileWidthMap::dataSize);

/*  // Convert width map table start address to banked form
  int widthMapTableBankedAddr
    = LoadedROM::directToBankedAddress(TailsAdvAddresses::WidthMapTable);
    
  // Get the position in the table (in bytes)
  int widthPos = widthMapAddr - widthMapTableBankedAddr;
  
  // Convert to index by dividing by size of each map
  // TODO: use named constant in WidthMap or whatever instead
  widthMapIndex_ = widthPos / 0x10; */
                                
  // Get terminator
  terminator_ = src[6];
}

void MetatileBehavior::writeToData(Tbyte* src) {
  // Write type byte
  src[0] = getTypeByte();
  
  // Write slope speed index
  src[1] = slopeSpeedIndex_ * 2;
  
  // Convert height map index to banked address
  int heightMapAddr
    = LoadedROM::indexToBankedAddr(TailsAdvAddresses::HeightMapTable,
                                   heightMapIndex_,
                                   MetatileHeightMap::dataSize);
  
/*  // Convert height map index to banked address
  int heightMapAddr
    = LoadedROM::directToBankedAddress(TailsAdvAddresses::HeightMapTable)
      + (heightMapIndex_ * 0x10); */
      
  // Write to data
  ByteConversion::toBytes(heightMapAddr,
                          src + 2,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Convert width map index to banked address
  int widthMapAddr
    = LoadedROM::indexToBankedAddr(TailsAdvAddresses::WidthMapTable,
                                   widthMapIndex_,
                                   MetatileWidthMap::dataSize);
      
  // Write to data
  ByteConversion::toBytes(widthMapAddr,
                          src + 4,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Write terminator
  src[6] = terminator_;
}

void MetatileBehavior::setSolidity(
    MetatileSolidities::MetatileSolidity solidity) {
  switch (solidity) {
  case MetatileSolidities::nonsolid:
    fullySolid_ = false;
    solidOnTop_ = false;
    break;
  case MetatileSolidities::solidOnTop:
    fullySolid_ = false;
    solidOnTop_ = true;
    break;
  case MetatileSolidities::fullySolid:
    fullySolid_ = true;
    solidOnTop_ = false;
    break;
  default:
    throw TGenericException(TALES_SRCANDLINE,
                           "MetatileBehavior::changeSolidity("
                           "MetatileSolidities::MetatileSolidity)",
                           std::string("Invalid solidity type: ")
                           + StringConversion::toString(
                            static_cast<int>(solidity)));
    break;
  }
}

MetatileSolidities::MetatileSolidity MetatileBehavior::solidity() const {
  // Prioritize as the game does: fully solid takes priority over
  // solid on top
  if (fullySolid_) {
    return MetatileSolidities::fullySolid;
  }
  else if (solidOnTop_) {
    return MetatileSolidities::solidOnTop;
  }
  else {
    return MetatileSolidities::nonsolid;
  }
}

Tbyte MetatileBehavior::getTypeByte() const {
  Tbyte result = 0;
  
  // Set needed bitfields
  
  if (fullySolid_) {
    result |= fullySolidMask;
  }
  
  if (solidOnTop_) {
    result |= solidOnTopMask;
  }
  
  if (unknownSetting_) {
    result |= unknownSettingMask;
  }
  
  // OR with type value
  result |= static_cast<int>(metatileType_);
  
  return result;
}

bool MetatileBehavior::fullySolid() const {
  return fullySolid_;
}

bool MetatileBehavior::solidOnTop() const {
  return solidOnTop_;
}

bool MetatileBehavior::unknownSetting() const {
  return unknownSetting_;
}

MetatileTypes::MetatileType MetatileBehavior::metatileType() const {
  return metatileType_;
}

int MetatileBehavior::slopeSpeedIndex() const {
  return slopeSpeedIndex_;
}

int MetatileBehavior::heightMapIndex() const {
  return heightMapIndex_;
}

int MetatileBehavior::widthMapIndex() const {
  return widthMapIndex_;
}

Tbyte MetatileBehavior::terminator() const {
  return terminator_;
}

void MetatileBehavior::setFullySolid(bool fullySolid__) {
  fullySolid_ = fullySolid__;
}

void MetatileBehavior::setSolidOnTop(bool solidOnTop__) {
  solidOnTop_ = solidOnTop__;
}

void MetatileBehavior::setUnknownSetting(bool unknownSetting__) {
  unknownSetting_ = unknownSetting__;
}

void MetatileBehavior::setMetatileType(MetatileTypes::MetatileType metatileType__) {
  metatileType_ = metatileType__;
}

void MetatileBehavior::setSlopeSpeedIndex(int slopeSpeedIndex__) {
  slopeSpeedIndex_ = slopeSpeedIndex__;
}

void MetatileBehavior::setHeightMapIndex(int heightMapIndex__) {
  heightMapIndex_ = heightMapIndex__;
}

void MetatileBehavior::setWidthMapIndex(int widthMapIndex__) {
  widthMapIndex_ = widthMapIndex__;
}

void MetatileBehavior::setTerminator(Tbyte terminator__) {
  terminator_ = terminator__;
}


}; 
