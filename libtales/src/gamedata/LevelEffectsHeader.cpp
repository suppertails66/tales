#include "gamedata/LevelEffectsHeader.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


LevelEffectsHeader::LevelEffectsHeader() {
  // Initialize to no effects
  for (int i = 0; i < numEffects; i++) {
    effects_[i] = SpecialEffects::none;
  }
}

LevelEffectsHeader::LevelEffectsHeader(const Tbyte* data) {
  // Initialize to no effects
  for (int i = 0; i < numEffects; i++) {
    effects_[i] = SpecialEffects::none;
  }
  
  // Read effects
  readFromData(data);
}

void LevelEffectsHeader::save(std::string& data) {
  // Write each effect number to string
  for (int i = 0; i < numEffects; i++) {
    Tbyte b = static_cast<Tbyte>(effects_[i]);
    data += std::string((char*)(&b), 1);
                        
//    std::cout << (int)(data[data.size() - 1]) << std::endl;
//    std::cout << (int)static_cast<Tbyte>(effects_[i]) << " ";
  }
//  std::cout << std::endl;
}

int LevelEffectsHeader::load(const Tbyte* data) {
  // Read full header from data
  return readFromData(data);
}

int LevelEffectsHeader::writeToData(Tbyte* data) {
  // Write each effect number
  for (int i = 0; i < numEffects; i++) {
    data[i] = static_cast<Tbyte>(effects_[i]);
  }
  
  // Return count of bytes written
  return dataSize;
}

int LevelEffectsHeader::readFromData(const Tbyte* data) {
  // Read each effect
  for (int i = 0; i < numEffects; i++) {
    effects_[i] = static_cast<SpecialEffects::SpecialEffect>(
                      ByteConversion::fromBytes(data + i,
                                                ByteSizes::uint8Size,
                                                EndiannessTypes::little,
                                                SignednessTypes::nosign));
//    std::cout << static_cast<int>(effects_[i]) << " ";
  }
//  std::cout  << std::endl;
  
  // Return count of bytes read
  return dataSize;
}

SpecialEffects::SpecialEffect& LevelEffectsHeader::effect(int index) {
  // Throw if index out of range
  if (static_cast<unsigned int>(index) >= numEffects) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "LevelEffectsHeader::effect(int)",
                                   index);
  }

  return effects_[index];
}

const SpecialEffects::SpecialEffect& LevelEffectsHeader
    ::effect(int index) const {
  // Throw if index out of range
  if (static_cast<unsigned int>(index) >= numEffects) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "LevelEffectsHeader::effect(int) const",
                                   index);
  }
  
  return effects_[index];
}


};
