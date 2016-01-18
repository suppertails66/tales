#include "gamedata/WarpDestination.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


WarpDestination::WarpDestination()
  : primaryMapDestination_(PrimaryMaps::poloyForest),
    subMapDestination_(1),
    destinationSpawnIndex_(0) {
  // Initialize all levels to not unlocked
  for (int i = 0; i < numUnlockableLevels; i++) {
    levelsUnlocked_[i] = false;
  }
}

WarpDestination::WarpDestination(const Tbyte* data)
  : primaryMapDestination_(PrimaryMaps::poloyForest),
    subMapDestination_(1),
    destinationSpawnIndex_(0) {
  // Initialize all levels to not unlocked
  for (int i = 0; i < numUnlockableLevels; i++) {
    levelsUnlocked_[i] = false;
  }
  
  // Load data
  readFromData(data);
}

WarpDestination::WarpDestination(
                LoadedROM& rom,
                Taddress address)
  : primaryMapDestination_(PrimaryMaps::poloyForest),
    subMapDestination_(1),
    destinationSpawnIndex_(0) {
  // Initialize all levels to not unlocked
  for (int i = 0; i < numUnlockableLevels; i++) {
    levelsUnlocked_[i] = false;
  }
  
  // Load data
  readFromData(rom.directRead(address));
}

int WarpDestination::readFromData(const Tbyte* data) {
  // Read primary map destination
  primaryMapDestination_ = 
    static_cast<PrimaryMaps::PrimaryMap>(
      ByteConversion::fromBytes(data + 0,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign));
  
  // Read submap destination
  subMapDestination_ = ByteConversion::fromBytes(data + 1,
                                     ByteSizes::uint8Size,
                                     EndiannessTypes::little,
                                     SignednessTypes::nosign);
  
  // Read spawn index
  destinationSpawnIndex_ = ByteConversion::fromBytes(data + 2,
                                     ByteSizes::uint8Size,
                                     EndiannessTypes::little,
                                     SignednessTypes::nosign);
  
  // Read levels unlocked bitfield
  int unlocks = ByteConversion::fromBytes(data + 3,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  // Unlock appropriate levels
  for (int i = 0; i < numUnlockableLevels; i++) {
    // Mask to check if unlock bit is set for this level
    int mask = 0x1 << i;
    
    if (unlocks & mask) {
      levelsUnlocked_[i] = true;
    }
  }
  
  return dataSize;
}

void WarpDestination::writeToData(Tbyte* data) {
  // Write primary map destination
  ByteConversion::toBytes(primaryMapDestination_,
                          data + 0,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Write submap destination
  ByteConversion::toBytes(subMapDestination_,
                          data + 1,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Write spawn index
  ByteConversion::toBytes(destinationSpawnIndex_,
                          data + 2,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Generate levels unlocked bitfield
  int unlocks = 0;
  for (int i = 0; i < numUnlockableLevels; i++) {
    if (levelsUnlocked_[i]) {
      // Set bit corresponding to this level
      int mask = 0x1 << i;
      unlocks |= mask;
    }
  }
  
  // Write levels unlocked bitfield
  ByteConversion::toBytes(unlocks,
                          data + 3,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
}

int WarpDestination::load(const Tbyte* data) {
  return readFromData(data);
}

void WarpDestination::save(std::string& data) {
  // Get raw data representation
  Tbyte buffer[dataSize];
  writeToData(buffer);
  
  // Append to string
  data += std::string((char*)buffer, dataSize);
}

bool WarpDestination::levelUnlocked(
    PrimaryMaps::PrimaryMap primaryMapNum) const {
  return levelsUnlocked_[static_cast<int>(primaryMapNum) - 1];
}

void WarpDestination::setLevelUnlocked(
                      PrimaryMaps::PrimaryMap primaryMapNum,
                      bool unlockStatus) {
  levelsUnlocked_[static_cast<int>(primaryMapNum) - 1] = unlockStatus;
}

PrimaryMaps::PrimaryMap WarpDestination::primaryMapDestination() const {
  return primaryMapDestination_;
}

int WarpDestination::subMapDestination() const {
  return subMapDestination_;
}

int WarpDestination::destinationSpawnIndex() const {
  return destinationSpawnIndex_;
}

void WarpDestination::setPrimaryMapDestination(
    PrimaryMaps::PrimaryMap primaryMapDestination__) {
  primaryMapDestination_ = primaryMapDestination__;
}

void WarpDestination::setSubMapDestination(int subMapDestination__) {
  subMapDestination_ = subMapDestination__;
}

void WarpDestination::setDestinationSpawnIndex(int destinationSpawnIndex__) {
  destinationSpawnIndex_ = destinationSpawnIndex__;
}


};
